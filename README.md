# Simple Memory Allocator

A simple custom memory allocator written in C for learning how dynamic memory management works internally.

Implements basic versions:

- `malloc`
- `calloc`
- `realloc`
- `free`

The allocator uses `sbrk()` to request memory directly from the operating system and manages allocations using custom block headers and a linked list structure.

[Resource - Memory Allocators 101](<https://arjunsreedharan.org/post/148675821737/memory-allocators-101-write-a-simple-memory>)
