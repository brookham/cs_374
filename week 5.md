# Pointers Review

- `void *` points to a specific index in memory but doesn't say anything about the type of what's there
- all pointers of all types point to a specific index in memory 

# Locking
- we have some *shared resources* and we have to make sure that multiple processes don't access it at the same time
- at least one of the processes is *writing* to the resources
- lets block other processes from accessing a *critical section*
	- critical sections should be as small as possible
	- we want to hold the lock for as short a time as possible
```c
printf("doing the test")
lock()
if (withdrawal_amount > account_balance) {
	account_balance -= withdrawal_amoutn;
}
unlock()
```

# POSIX locks
- *Advisory Locks* (what we will use with POSIX locks)
- *Mandatory Locks* (this is what we will use with mutexes and threads)

