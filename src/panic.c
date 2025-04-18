#include <safe.h>

void	panicf(const char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	sadestroy(); // @Cleanup
	exit(1);
}

void	*salloc_check(const void *mem)
{
	if (!mem)
		panicf("Buy Ram\n");
	return ((void *)mem);
}
