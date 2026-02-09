#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define LENGTH (sizeof(int) * 2 + 1048576 * 32)

int main(int argc, char *argv[])
{
  struct flock h_lock = {
      .l_type = F_WRLCK,
      .l_whence = SEEK_SET,
      .l_start = 0,
      .l_len = sizeof(int) * 2};

  int fd = open("data.dat", O_RDWR | O_CREAT | O_TRUNC, 0666);
  ftruncate(fd, LENGTH);

  void *data = mmap(NULL, LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  int *header = data;

  header[0] = 0;
  header[1] = 0;

  for (int i = 1; i + 1 < argc; i += 2)
  {
    int count = atoi(argv[i]);
    const char *prefix = argv[i + 1];
    pid_t pid = fork();

    if (pid == 0)
    {
      for (int j = 0; j < count; j++)
      {
        h_lock.l_type = F_WRLCK;
        h_lock.l_start = 0;
        h_lock.l_len = sizeof(int) * 2;
        fcntl(fd, F_SETLKW, &h_lock);

        int record_offset = header[0];
        header[1] += 1;
        header[0] = record_offset + 32;

        h_lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLKW, &h_lock);

        struct flock l_lock = {
            .l_type = F_WRLCK,
            .l_whence = SEEK_SET,
            .l_start = sizeof(int) * 2 + record_offset,
            .l_len = 32};

        char *log_ptr = (char *)data + sizeof(int) * 2 + record_offset;

        l_lock.l_type = F_WRLCK;
        fcntl(fd, F_SETLKW, &l_lock);

        char temp[32];
        snprintf(temp, sizeof(temp), "%s %d", prefix, j);
        strcpy(log_ptr, temp);

        l_lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLKW, &l_lock);
      }
      _exit(0);
    }
  }

  for (int i = 1; i + 1 < argc; i += 2)
    wait(NULL);

  struct flock d_lock = {
      .l_type = F_RDLCK,
      .l_whence = SEEK_SET,
      .l_start = 0,
      .l_len = 0};

  fcntl(fd, F_SETLKW, &d_lock);

  int total = header[1];

  for (int i = 0; i < total; i++)
  {
    char *log = (char *)data + sizeof(int) * 2 + i * 32;
    printf("%d: %s\n", i, log);
  }

  d_lock.l_type = F_UNLCK;
  fcntl(fd, F_SETLKW, &d_lock);

  munmap(data, LENGTH);
  close(fd);
}