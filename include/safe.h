#ifndef SAFE_H
#define SAFE_H
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <assert.h>
# include <ctype.h>

typedef struct s_sstring {
	char  *items;
	size_t size;
	size_t cap;
} t_sstring;

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

// TOP LEVEL FUNCTIONS TO USE.
void *salloc(size_t nbytes);
void *sarealloc(void *ptr, size_t new);
void safree(void *ptr);
void sadisplay(void);
void sadestroy(void);

sa_node_t	*new_sa_node(size_t nbytes);
void	*sarealloc(void *ptr, size_t new);
void	destroy_sa(safe_allocator_t *global_allocator);
void	release_sa_node(sa_node_t *node);
void	destroy_sa_node(safe_allocator_t *allocator, void *ptr);

void	sstring_push(t_sstring *string, int c);
void	sstring_push_front(t_sstring *string, int c);
void	sstring_join(t_sstring *string, t_sstring *other);
void	sstring_strip(t_sstring *string);
void	sstring_cstrpush(t_sstring *string, const char *str);
#endif // SAFE_H
