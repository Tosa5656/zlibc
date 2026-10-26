#include "../internal/stdio_impl.h"

void __stdio_exit_needed(void);

FILE *__ofl_add(FILE *f)
{
	FILE **head = __ofl_lock();

	f->next = *head;

	if (*head)
	{
		(*head)->prev = f;
	}

	*head = f;

	return f;
}
