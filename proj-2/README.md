# Procject Overview
the file scanner takes a directory location as an input and goes through the directory, and all sub-directories to get sizes (in bytes) of all regular files in each directory. it then sums the file sizes to get a total size of each directory/sub-directory.

# Function Call Diagram

main()
  ↓
opendir()
  ↓
expand()
  |-readdir()
  |   stat()
  |   opendir()
  |       ↓
  |     expand()
  |       |-readdir()
  |       |   stat()
  |       |- ...
  |        printf()
  |       closedir()
  |
  |-readdir()
  |   stat()
  |   opendir()
  |       ↓
  |     expand()
  |       |-readdir()
  |       |   stat()
  |       |- ...
  |        printf()
  |       closedir()
  |
  |- ...
  printf()
  closedir()
