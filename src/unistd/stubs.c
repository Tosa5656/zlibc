#include <unistd.h>

int pipe(int fds[2])
{
	(void)fds;
	return -1;
}

unsigned alarm(unsigned seconds)
{
	(void)seconds;
	return 0;
}

int pause(void)
{
	return -1;
}

int access(const char *path, int mode)
{
	(void)path;
	(void)mode;
	return -1;
}

char *getcwd(char *buf, size_t size)
{
	(void)size;
	if (buf == NULL)
	{
		return NULL;
	}
	buf[0] = '/';
	buf[1] = '\0';
	return buf;
}

int chdir(const char *path)
{
	(void)path;
	return -1;
}
