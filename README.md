# CakeOS
This is a basic operating system and bootloader for the i386 architecture. 

## Current Features
* FAT16 filesystem with read functionality
* Heap allocation
* Paging
* ELF loader
* Basic shell

## How to Run
To run the OS in its current state, clone the repository and ensure qemu is installed. Next, run the following command in the root folder of the project.
```
qemu-system-i386 -hda ./bin/os.bin
```

Future Features Being Implemented
- [x] Shell
- [ ] Write functionality for the filesystem
- [ ] Dynamic linker
- [ ] TCP/IP stack
- [ ] Shell commands
