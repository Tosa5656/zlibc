#include <stddef.h>
#include <syscall.h>

extern int main(int argc, char **argv, char **envp);

static void inline_exit(int status)
{
	__syscall1(SYSCALL_EXIT, status);
}

void __libc_start_main(int argc, char **argv)
{
	char **envp = argv + argc + 1;

	int result = main(argc, argv, envp);

	inline_exit(result);
}
