#ifndef SALLOC_H
#define SALLOC_H
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <assert.h>

typedef enum s_allocator_action
{
	ALLOCATE_NODE = 0,
	DESTROY_NODE,
	DESTROY_ALLOCATOR,
	GET_ALLOCATOR,
	DISPLAY_ALLOCATOR
} t_allocator_action;

typedef struct sa_node_s sa_node_s;

typedef struct sa_node_s
{
	unsigned char	*data;
	size_t			size;
	sa_node_s		*next;
} sa_node_t;

typedef struct safe_allocator_s
{
	sa_node_t	*head;
	sa_node_t	*tail;
	size_t		count;
} safe_allocator_t;

void *salloc(size_t nbytes);
void sa_display(void);
void safree(void *ptr);
void sa_destroy(void);
#endif // SALLOC_H
