#ifndef _SYS_WAIT_H
#define _SYS_WAIT_H

#ifdef __cplusplus
extern "C" {
#endif

#define __NEED_pid_t
#include <alltypes.h>

typedef enum
{
	P_ALL  = 0,
	P_PID  = 1,
	P_PGID = 2
} idtype_t;

pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);

#define WNOHANG    1
#define WUNTRACED  2
#define WCONTINUED 8
#define WNOWAIT    0x1000000

#define WEXITSTATUS(s) (((s) & 0xff00) >> 8)
#define WTERMSIG(s)    ((s) & 0x7f)
#define WSTOPSIG(s)    WEXITSTATUS(s)
#define WCOREDUMP(s)   ((s) & 0x80)
#define WIFEXITED(s)   (!WTERMSIG(s))
#define WIFSIGNALED(s) (((s) & 0xffff) - 1U < 0xffU)
#define WIFSTOPPED(s)  ((short)((((s) & 0xffff) * 0x10001U) >> 8) > 0x7f00)
#define WIFCONTINUED(s) ((s) == 0xffff)

#ifdef __cplusplus
}
#endif

#endif
