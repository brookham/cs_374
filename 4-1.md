# fork( ) and variables, local and global
- child gets a copy of the data, not shared with the parent.
	- includes globals
- under the hood this works with a mechanism called "copy on write"
```
parent
   V
|------------3---------|
|            -         |
   ^
child
```

# The pipe( ) for interposes communication
```c
int pipe_fd[2];

pipe(pipe_fd);
```

```
- 0 standard input, read
- 1 standard output, write
- pipe_fd[0], read end
- pipe_fd[1], write end
```

# Fork( ) and the system file table
```c
int pfds[2];

pipe(pfds); // call pipe before fork

fork();
```

```
  read   write
pfds[0] pfds[1]
  v        v     user space, parent
- - - - - - - - 
  |--pipe--|     OS kernel
- - - - - - - - 
  ^        ^     user space, child
pfds[0] pfds[1]    
```
we decided the parent is the writer and the child is the reader, child and parent must close the end of the pipe they are not using
```
  read   write
        pfds[1]
  v        v     user space, parent
- - - - - - - - 
  |--pipe--|     OS kernel
- - - - - - - - 
  ^        ^     user space, child
pfds[0]
  read    write    
```

# dup( ) and file descriptors
- duplicates a file descriptor
- ```c
#include <stdio.h>
#include <unistd.h>

	int main(void) 
	{
	  int stdout2 = dup(1);
	  
	  write(1, "hi\n", 4);
	  write(stdout2, "HI!\n", 4);
	  
	  printf("%d\n", stdout2);
	}
	  
	output:
	hi!
	HI!
	3
  ```
  
```c
int main(void)
{
	int fd = open(... O_WRONLY);
	
	close(1);
	dup(fd);
	
//	  |---| 1 and 3 both now point to fd
//	0 1 2 3

//    or

	dup2(fd, 1) // controll of the file descriptor you are duping into instead of                     auto selecting the lowest avaliable one
	
	printd("%d\n", stdout2) // writes to fd 1
}
```