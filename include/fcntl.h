#ifndef FCNTL_H
#define FCNTL_H

#define __NEED_off_t
#define __NEED_pid_t
#define __NEED_mode_t

#include <alltypes.h>

struct flock
{
	short l_type;
	short l_whence;
	off_t l_start;
	off_t l_len;
	pid_t l_pid;
};

int creat(const char *filename, mode_t mode);
int fcntl(int fd, int cmd, ...);
int open(const char *filename, int flags, ...);
int openat(int fd, const char *filename, int flags, ...);
//int posix_fadvise(int fd, off_t base, off_t len, int advice);
//int posix_fallocate(int fd, off_t base, off_t len);

#define O_SEARCH   O_PATH
#define O_EXEC     O_PATH
#define O_TTY_INIT 0

#define O_ACCMODE (03|O_SEARCH)
#define O_RDONLY  00
#define O_WRONLY  01
#define O_RDWR    02

#define O_CREAT        00000100
#define O_EXCL         00000200
#define O_NOCTTY       00000400
#define O_TRUNC        00001000
#define O_APPEND       00002000
#define O_NONBLOCK     00004000
#define O_DSYNC        00010000
#define O_SYNC         00040000
#define O_RSYNC        00040000
#define O_DIRECTORY    00200000
#define O_NOFOLLOW     00400000
#define O_CLOEXEC      002000000
#define O_TMPFILE      020200000
#define O_PATH         0010000000
#define O_LARGEFILE    00100000

#define F_DUPFD      0
#define F_GETFD      1
#define F_SETFD      2
#define F_GETFL      3
#define F_SETFL      4
#define F_GETLK      5
#define F_SETLK      6
#define F_SETLKW     7

#define F_OFD_GETLK 36
#define F_OFD_SETLK 37
#define F_OFD_SETLKW 38

#define F_DUPFD_CLOEXEC 1030

#define F_RDLCK 0
#define F_WRLCK 1
#define F_UNLCK 2

#define F_SETOWN    8
#define F_GETOWN    9
#define F_SETSIG    10
#define F_GETSIG    11
#define F_SETOWN_EX 15
#define F_GETOWN_EX 16

#define F_OWNER_TID  0
#define F_OWNER_PID  1
#define F_OWNER_PGRP 2

struct f_owner_ex
{
	int type;
	pid_t pid;
};

#define FD_CLOEXEC 1

#define AT_FDCWD (-100)
#define AT_SYMLINK_NOFOLLOW 0x100
#define AT_REMOVEDIR 0x200
#define AT_SYMLINK_FOLLOW 0x400
#define AT_EACCESS 0x200

#define POSIX_FADV_NORMAL     0
#define POSIX_FADV_RANDOM     1
#define POSIX_FADV_SEQUENTIAL 2
#define POSIX_FADV_WILLNEED   3
#ifndef POSIX_FADV_DONTNEED
#define POSIX_FADV_DONTNEED   4
#define POSIX_FADV_NOREUSE    5
#endif

#undef SEEK_SET
#undef SEEK_CUR
#undef SEEK_END
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#ifndef S_IRUSR
#define S_ISUID 04000
#define S_ISGID 02000
#define S_ISVTX 01000
#define S_IRUSR 0400
#define S_IWUSR 0200
#define S_IXUSR 0100
#define S_IRWXU 0700
#define S_IRGRP 0040
#define S_IWGRP 0020
#define S_IXGRP 0010
#define S_IRWXG 0070
#define S_IROTH 0004
#define S_IWOTH 0002
#define S_IXOTH 0001
#define S_IRWXO 0007
#endif

#endif
