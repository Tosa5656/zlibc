#include <stdlib.h>
#include <sys/syscall.h>

#define EXIT_HANDLER_MAX 32

static void (*exit_handlers[EXIT_HANDLER_MAX])(void);
static int exit_handler_count;

static void (*quick_exit_handlers[EXIT_HANDLER_MAX])(void);
static int quick_exit_handler_count;

int atexit(void (*function)(void))
{
	if (function == NULL || exit_handler_count == EXIT_HANDLER_MAX)
	{
		return -1;
	}

	exit_handlers[exit_handler_count] = function;
	exit_handler_count++;

	return 0;
}

int at_quick_exit(void (*function)(void))
{
	if (function == NULL || quick_exit_handler_count == EXIT_HANDLER_MAX)
	{
		return -1;
	}

	quick_exit_handlers[quick_exit_handler_count] = function;
	quick_exit_handler_count++;

	return 0;
}

_Noreturn void _Exit(int status)
{
	__syscall1(SYSCALL_EXIT, status);
	for (;;) {}
}

_Noreturn void exit(int status)
{
	int index;

	for (index = exit_handler_count - 1; index >= 0; index--)
	{
		void (*handler)(void) = exit_handlers[index];

		exit_handlers[index] = NULL;
		if (handler != NULL)
		{
			handler();
		}
	}

	_Exit(status);
}

_Noreturn void quick_exit(int status)
{
	int index;

	for (index = quick_exit_handler_count - 1; index >= 0; index--)
	{
		void (*handler)(void) = quick_exit_handlers[index];

		quick_exit_handlers[index] = NULL;
		if (handler != NULL)
		{
			handler();
		}
	}

	_Exit(status);
}

_Noreturn void abort(void)
{
	_Exit(134);
}
