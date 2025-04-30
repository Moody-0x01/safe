#include <safe.h>

void	panicf(const char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	ft_vfprintf(STDERR_FILENO, fmt, args);
	sadestroy(); // @Cleanup
	exit(1);
}

void	*salloc_check(const void *mem)
{
	if (!mem)
		panicf("Buy Ram\n");
	return ((void *)mem);
}

void	*malloc_checkd(size_t size)
{
	void *mem = malloc(size);
	if (!mem)
		panicf("Buy Ram\n");
	return (mem);
}
