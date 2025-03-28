# include <safe.h>

static void	*allocator_station(t_allocator_action a, size_t nbytes, void *ptr)
{
	static safe_allocator_t	global_allocator;
	sa_node_t *node;
	sa_node_t *realoc;

	switch (a)
	{
		case ALLOCATE_NODE: {
			node = new_sa_node(nbytes);
			if (!global_allocator.head)
			{
				global_allocator.head = node;
				global_allocator.tail = node;
			}
			else {
				global_allocator.tail->next = node;
				global_allocator.tail = node;
			}
			global_allocator.count++;
			return (node->data);
		} break;
		case DESTROY_NODE: {
			destroy_sa_node(&global_allocator, ptr);
		} break;
		case DESTROY_ALLOCATOR: {
			destroy_sa(&global_allocator);
		} break;
		case GET_ALLOCATOR: {
			return (&global_allocator);
		} break;
		case DISPLAY_ALLOCATOR: {
			printf("Size of the alloc table: %zu\n", global_allocator.count);
			node = global_allocator.head;
			while (true)
			{
				if (!node)
					break ;
				assert(node->data);
				printf("Ptr: %p\n", node->data);
				printf("Block size: %zu\n", node->size);
				node = node->next;
			}
		} break;
		case REAL_NODE: {
			if (ptr == NULL)
				return allocator_station(ALLOCATE_NODE, nbytes, NULL);
			allocator_station(ALLOCATE_NODE, nbytes, NULL);
			node = global_allocator.tail;
			realoc = global_allocator.head;
			while (realoc && realoc->data != ptr)
				realoc = realoc->next;
			assert(realoc->data == ptr);
			memcpy(node->data, realoc->data, realoc->size);
			safree(realoc->data);
			return (node->data);
		} break;
		default:
			assert(0 && "What the fuck did u give to this function buddy");
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
