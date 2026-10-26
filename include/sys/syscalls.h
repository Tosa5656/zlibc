#ifndef SYSCALLS_H
#define SYSCALLS_H

#define SYSCALL_READ      0
#define SYSCALL_WRITE     1
#define SYSCALL_OPEN      2
#define SYSCALL_CLOSE     3
#define SYSCALL_SEEK      8
#define SYSCALL_BRK       12
#define SYSCALL_DUP       32
#define SYSCALL_NAONSLEEP 35
#define SYSCALL_GETPID    39
#define SYSCALL_EXIT      60
#define SYSCALL_FCNTL     72
#define SYSCALL_MKDIR     83
#define SYSCALL_RMDIR     84
#define SYSCALL_UNLINK    87
#define SYSCALL_GETPPID   110
#define SYSCALL_OPENAT    257

#define SYSCALL_MAX SYSCALL_OPENAT

#endif
