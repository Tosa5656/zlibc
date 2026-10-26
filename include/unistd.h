#ifndef _UNISTD_H
#define _UNISTD_H

#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define __NEED_size_t
#define __NEED_ssize_t
#define __NEED_off_t
#define __NEED_pid_t
#define __NEED_uid_t
#define __NEED_gid_t
#define __NEED_useconds_t
#define __NEED_intptr_t

#include <alltypes.h>

int close(int);
int dup(int);
int dup2(int, int);
off_t lseek(int, off_t, int);

ssize_t read(int, void *, size_t);
ssize_t write(int, const void *, size_t);

pid_t getpid(void);
pid_t getppid(void);
pid_t getpgrp(void);

int isatty(int);
int pipe(int [2]);

unsigned alarm(unsigned);
unsigned sleep(unsigned);
int usleep(unsigned);
int pause(void);

int ftruncate(int, off_t);
int truncate(const char *, off_t);

#define _exit __libc_exit
_Noreturn void _exit(int);
_Noreturn void _Exit(int);

#define F_OK 0
#define X_OK 1
#define W_OK 2
#define R_OK 4

int access(const char *, int);
char *getcwd(char *, size_t);
int chdir(const char *);
int rmdir(const char *);
int unlink(const char *);

void *sbrk(intptr_t);
int brk(void *);

#define POSIX_CLOSE_RESTART 0

#endif
