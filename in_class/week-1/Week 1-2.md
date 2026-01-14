# Standard Input, Output, Error
- files that every process have open for them on default 
```c
#include <unistd.h>

//file descriptors
// 0 - stdin
// 1 - stdout
// 2 - stderr

int main(void)
{
	char buf[128];
	
	ssize_t num_bytes = read(0, buf, 128);
	
	write(1, buf, num_bytes);
}
```

# System Calls
- computing
- user space
  =========== our program makes a "syscall"
- kernel space
- hardware

# The File System
