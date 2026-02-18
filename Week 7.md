## structs review
```c
struct foo {
	int a;
	float b;
};

struct foo x, y;

x.a = 12;
x.b = 3.14;

struct foo z = {
	.a=12,
	.b=3.14
};

struct foo *p;

p = &z;

printf("%d\n", z.a);
printf("%d\n", p.a); // WRONG
printf("%d\n", (*p).a); // works but ...
printf("%d\n", p->a); // this works better
```
- if you have a struct, use `.`
- if you have a pointer, use `->`

## Concurrency vs Parallelism

- **Concurrency** is multiple threads that *look like* they are running at the same time 
	- this implies *correctness*
- **Parallelism** is multiple threads that *are* running at the same time
	- when you have a lot of CPU cores 

## Critical Sections and Race Conditions
```c
thread[i] == *(thread + i);
&thread[i] == &(*(thread + i));
&thread[i] == thread + i;
```