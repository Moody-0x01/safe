# include <safe.h>

sa_node_t	*new_sa_node(size_t nbytes)
{
	sa_node_t *node;

	node = calloc(1, sizeof(*node));
	node->data = malloc(nbytes);
	memset(node->data, 0, nbytes);
	node->size = nbytes;;
	return (node);
}

static void	*allocator_station(t_allocator_action a, size_t nbytes, void *ptr)
{
	static safe_allocator_t	global_allocator;
	sa_node_t *node;
	sa_node_t *realoc;
	sa_node_t *next;

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
			if (!ptr || !global_allocator.head)
				return (NULL);
			if (global_allocator.head->data == ptr)
			{
				global_allocator.head = global_allocator.head->next;
				if (!global_allocator.head)
					global_allocator.tail = global_allocator.head;
				global_allocator.count--;
				return (NULL);
			}
			for (node = global_allocator.head; node->next; (node = node->next))
			{
				if (node->next->data == ptr)
					break ;
			}
			if (node->next)
			{
				next = node->next;
				if (next == global_allocator.tail)
					global_allocator.tail = node;
				free(next->data);
				node->next = next->next;
				free(next);
			}
		} break;
		case DESTROY_ALLOCATOR: {
			for (node = global_allocator.head; node;)
			{
				next = node->next;
					free(node->data);
					free(node);
				node = next;
			}
			memset(&global_allocator, 0, sizeof(global_allocator));
		} break;
		case GET_ALLOCATOR: {
			return (&global_allocator);
		} break;
		case DISPLAY_ALLOCATOR: {
			printf("Size of the alloc table: %zu\n", global_allocator.count);
			for (node = global_allocator.head; node;)
			{
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
			safree(ptr);
			return (node->data);
		}
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

void sa_display(void)
{
	allocator_station(DISPLAY_ALLOCATOR, 0, NULL);
}

void sa_destroy(void)
{
	allocator_station(DESTROY_ALLOCATOR, 0, NULL);
}

void *sarealloc(void *ptr, size_t new)
{
	return (allocator_station(REAL_NODE, new, ptr));
}
