#ifndef STDIO_IMPL_H
#define STDIO_IMPL_H

#include <stdio.h>
#include <syscall.h>

#define UNGET 8

#define FLOCK(f) ((void)0)
#define FUNLOCK(f) ((void)(f))

#define F_PERM 1
#define F_NORD 4
#define F_NOWR 8
#define F_EOF 16
#define F_ERR 32
#define F_SVB 64
#define F_APP 128

struct _IO_FILE
{
	unsigned flags;
	unsigned char *rpos, *rend;
	int (*close)(FILE *);
	unsigned char *wend, *wpos;
	unsigned char *mustbezero_1;
	unsigned char *wbase;
	size_t (*read)(FILE *, unsigned char *, size_t);
	size_t (*write)(FILE *, const unsigned char *, size_t);
	off_t (*seek)(FILE *, off_t, int);
	unsigned char *buf;
	size_t buf_size;
	FILE *prev, *next;
	int fd;
	int pipe_pid;
	long lockcount;
	int mode;
	volatile int lock;
	int lbf;
	void *cookie;
	off_t off;
	char *getln_buf;
	void *mustbezero_2;
	unsigned char *shend;
	off_t shlim, shcnt;
	FILE *prev_locked, *next_locked;
	struct __locale_struct *locale;
};

extern FILE *const __stdin_used;
extern FILE *const __stdout_used;
extern FILE *const __stderr_used;

size_t __stdio_read(FILE *, unsigned char *, size_t);
size_t __stdio_write(FILE *, const unsigned char *, size_t);
size_t __stdout_write(FILE *, const unsigned char *, size_t);
off_t __stdio_seek(FILE *, off_t, int);
int __stdio_close(FILE *);

int __toread(FILE *);
int __towrite(FILE *);

void __stdio_exit(void);
void __stdio_exit_needed(void);

int __overflow(FILE *, int);
int __uflow(FILE *);

int __fseeko(FILE *, off_t, int);
int __fseeko_unlocked(FILE *, off_t, int);
off_t __ftello(FILE *);
off_t __ftello_unlocked(FILE *);
size_t __fwritex(const unsigned char *, size_t, FILE *);

FILE *__fdopen(int, const char *);
int __fmodeflags(const char *);

FILE *__ofl_add(FILE *f);
FILE **__ofl_lock(void);

void __shlim(FILE *, off_t);
int __shgetc(FILE *);

#define shcnt(f) ((f)->shcnt + ((f)->rpos - (f)->buf))
#define shlim(f, lim) __shlim((f), (lim))
#define shgetc(f) ((f)->rpos != (f)->shend ? *(f)->rpos++ : __shgetc(f))
#define shunget(f) ((f)->shlim>=0 ? (void)(f)->rpos-- : (void)0)
#define sh_fromstring(f, s) ((f)->buf = (f)->rpos = (void *)(s), (f)->rend = (void *)-1)

unsigned long long __intscan(FILE *, unsigned, int, unsigned long long);
long double __floatscan(FILE *, int, int);

void __randname(char *);

#endif
