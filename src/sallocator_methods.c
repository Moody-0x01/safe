#include <safe.h>

void	destroy_sa(safe_allocator_t *global_allocator)
{
	sa_node_t	*node;
	sa_node_t	*next;

	node = global_allocator->head;
	while (true)
	{
		if (!node)
			break ;
		next = node->next;
		release_sa_node(node);
		global_allocator->head = next;
		node = next;
	}
	memset(global_allocator, 0, sizeof(*global_allocator));
}

void	destroy_sa_node(safe_allocator_t *allocator, void *ptr)
{
	sa_node_t *node;
	sa_node_t *next;

	if (!ptr || !allocator->head)
		return ;
	node = allocator->head;
	if (allocator->head->data == ptr)
	{
		allocator->head = allocator->head->next;
		if (!allocator->head)
			allocator->tail = allocator->head;
	}
	else 
	{
		while (node->next)
		{
			if (node->next->data == ptr)
				break ;
			node = node->next;
		}
		if (node->next)
		{
			if (node->next == allocator->tail)
				allocator->tail = node;
			next = node->next;
			node->next = node->next->next;
			node = next;
		}
	}
	release_sa_node(node);
	if (allocator->count)
		allocator->count--;
}
