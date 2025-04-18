#include <safe.h>

void	sa_destroy(safe_allocator_t *global_allocator)
{
	sa_node_t	*node;
	sa_node_t	*next;

	node = global_allocator->head;
	while (true)
	{
		if (!node)
			break ;
		next = node->next;
		sa_release_node(node);
		global_allocator->head = next;
		node = next;
	}
	ft_memset(global_allocator, 0, sizeof(*global_allocator));
}

void	sa_destroy_node(safe_allocator_t *allocator, void *ptr)
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
	sa_release_node(node);
	if (allocator->count)
		allocator->count--;
}

void	*sa_append(safe_allocator_t *allocator, size_t nbytes)
{
	sa_node_t *node;

	node = sa_new_node(nbytes);
	if (!allocator->head)
	{
		allocator->head = node;
		allocator->tail = node;
	}
	else {
		allocator->tail->next = node;
		allocator->tail = node;
	}
	allocator->count++;
	return (node->data);
}

void	*sa_reappend_node(safe_allocator_t *allocator, void *old_ptr, size_t new_nbytes)
{
	sa_node_t *target_to_be_removed;
	sa_node_t *node;

	if (old_ptr == NULL)
		return (sa_append(allocator, new_nbytes));
	sa_append(allocator, new_nbytes);
	node = allocator->tail;
	target_to_be_removed = allocator->head;
	while (target_to_be_removed && target_to_be_removed->data != old_ptr)
		target_to_be_removed = target_to_be_removed->next;
	if (!target_to_be_removed)
	{
		panicf("realloc: [Invalid pointer][Which: %p]\n"
			"Possible reasons:\n"
			"    - Allocd with malloc\n"
			"    - Already freed\n", old_ptr);
	}
	if (new_nbytes < target_to_be_removed->size)
		node->data = ft_memcpy(node->data, old_ptr, new_nbytes);
	else
		node->data = ft_memcpy(node->data, old_ptr, target_to_be_removed->size);
	sa_destroy_node(allocator, old_ptr);
	return (node->data);
}

void	sa_print(safe_allocator_t *allocator)
{
	sa_node_t *node;

	printf("SIZE OF THE SALLOC TABLE: %zu\n", allocator->count);
	node = allocator->head;
	while (true)
	{
		if (!node)
			break ;
		assert(node->data);
		printf("Ptr:        %p\n", node->data);
		printf("Block size: %zu\n", node->size);
		node = node->next;
	}
}
