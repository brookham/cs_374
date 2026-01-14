# Paths
- where something is stores on the disk
- what is the directory path that leads to a particular file?
```
foo.txt

/home/brook/src/foo/foo.txt
|--------------------------|
            path
```
- *absolute paths* start with a /
- *relative paths* don't start with a /
- relative paths from where you are now mean the current directory
- every process tracks its own current working directory
- '..' up one, the "parent" directory
- '.' the current directory

# File Descriptors
- number that's assigned to an open file, and you use it when reading and writing
  0 - stdin
  1 - stdout
  2 - stderror
  
# file position and 'lseek()'
- where the next read or write will occur in the file
- we can move it around with 'lseek()'
```
off_t lseek(int fd, off_t offset, int whence);
               ^          ^            ^
       File desc   where in the file  SEEK_SET
```
- you can seek past the end of the file
# Symbolic Links
- symbolic links like shortcuts make new references to files or directories

# File Metadata 