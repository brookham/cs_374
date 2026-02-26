## Deadlock
- assuming you have multiple code paths getting the same locks:
	- always acquire the locks in the same order everywhere
	- always release the locks in the opposite order that you acquire them

## Locking data structures
- Easy way: big lock over the whole thing
	- lose some parallelism
	- sometimes its the way it is
	- try to minimize the size of your critical sections
- more complex data structures might get some improvements with multiple locks
- *coarse grained* *fine grained* locking
- database tables
	- more locks
	- more parallelism

## Lock-Free Data Structures
- lock-free queue

```
head                 tail
[1] -> [2] -> [3] -> [4]
```
	