#include <stdio.h>   // For perror()
#include <fcntl.h>   // For open()
#include <unistd.h>  // For write() and close()

int main(void)
{
    // Integer to hold the file descriptior
    int fd;

    // Try to open the file `foo.txt`.
    //
    // Flags (bitwise-ORd together):
    //
    //   O_WRONLY: open only for writing
    //   O_CREAT:  create the file if it doesn't exist
    //   O_TRUNC:  truncate the file if it does exist
    //
    // 0600: If the file is created, give it these permissions: rw-------
    fd = open("foo.txt", O_RDONLY, 0600);

    if (fd == -1) {
        // If the open fails, print out an error message prepended with
        // "open"
        perror("open");
        return 1;  // Exit with error code 1
    }



    // Write 14 bytes to the file
    write(1, "Hello, world!\n", 14);

    char buf[128];  // 128-byte buffer

    // Read *up to* 128 bytes from stdin (0)
    int bytes_read = read(fd, buf, 128);
    // Close the file when done
    close(fd);
}