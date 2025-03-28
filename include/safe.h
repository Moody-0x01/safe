#ifndef SAFE_H
#define SAFE_H
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <assert.h>

typedef struct s_string {
	char  *items;
	size_t size;
	size_t cap;
} t_string;

typedef enum s_allocator_action
{
	ALLOCATE_NODE = 0,
	DESTROY_NODE,
	DESTROY_ALLOCATOR,
	GET_ALLOCATOR,
	DISPLAY_ALLOCATOR,
	REAL_NODE
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
void *sarealloc(void *ptr, size_t new);
void safree(void *ptr);
void sa_display(void);
void sa_destroy(void);
void *sarealloc(void *ptr, size_t new);
#endif // SAFE_H
