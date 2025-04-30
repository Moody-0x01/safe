#include <safe.h>

sa_node_t	*sa_new_node(size_t nbytes)
{
	sa_node_t *node;

	node = malloc_checkd(sizeof(*node));
	ft_memset(node, 0, sizeof(*node));
	node->data = malloc_checkd(nbytes);
	ft_memset(node->data, 0, nbytes);
	node->size = nbytes;;
	return (node);
}

void	sa_release_node(sa_node_t *node)
{
	if (node)
	{
		if (node->data)
			free(node->data);
		free(node);
	}
}
