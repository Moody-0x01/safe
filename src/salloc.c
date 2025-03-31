# include <safe.h>

static void	*allocator_station(t_allocator_action a, size_t nbytes, void *ptr)
{
	static safe_allocator_t	global_allocator;

	switch (a)
	{
		case ALLOCATE_NODE: {
			return (sa_append(&global_allocator, nbytes));
		} break;
		case DESTROY_NODE: {
			sa_destroy_node(&global_allocator, ptr);
		} break;
		case DESTROY_ALLOCATOR: {
			sa_destroy(&global_allocator);
		} break;
		case GET_ALLOCATOR: {
			return (&global_allocator);
		} break;
		case DISPLAY_ALLOCATOR: {
			sa_print(&global_allocator);
		} break;
		case REAL_NODE: {
			return (sa_reappend_node(&global_allocator, ptr, nbytes));
		} break;
		default:
			panicf("allocator_station: invalid action\n");
	}
	return (NULL);
}

void	*salloc(size_t nbytes)
{
	return allocator_station(ALLOCATE_NODE, nbytes, NULL);
}

void	safree(void *ptr)
{
	allocator_station(DESTROY_NODE, 0, ptr);
}

void sadisplay(void)
{
	allocator_station(DISPLAY_ALLOCATOR, 0, NULL);
}

void sadestroy(void)
{
	allocator_station(DESTROY_ALLOCATOR, 0, NULL);
}

void *sarealloc(void *ptr, size_t new)
{
	return (allocator_station(REAL_NODE, new, ptr));
}
