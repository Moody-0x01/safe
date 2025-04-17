#ifndef SAFE_H
#define SAFE_H
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <assert.h>
# include <ctype.h>

#define VEC_INIT_CAP 100
typedef struct s_sstring {
	char  *items;
	size_t size;
	size_t cap;
} t_sstring;

typedef struct s_sstring_array
{
	t_sstring  *items;
	size_t		size;
	size_t		cap;
} t_sstring_array;

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

void	*sa_append(safe_allocator_t *allocator, size_t nbytes);
void	sa_destroy(safe_allocator_t *global_allocator);
void	sa_destroy_node(safe_allocator_t *allocator, void *ptr);
void	*sa_reappend_node(safe_allocator_t *allocator, void *old_ptr, size_t new_nbytes);
void	sa_print(safe_allocator_t *allocator);

sa_node_t	*sa_new_node(size_t nbytes);
void		sa_release_node(sa_node_t *node);

void	sstring_init(t_sstring *string);
void	sstring_push(t_sstring *string, int c);
void	sstring_push_front(t_sstring *string, int c);
void	sstring_join(t_sstring *string, t_sstring *other);
void	sstring_strip(t_sstring *string);
void	sstring_cstrpush(t_sstring *string, const char *str);
void	sstring_lower(t_sstring *string);
void	sstring_upper(t_sstring *string);
void	t_sstring_array_push_back(t_sstring_array *ssa, t_sstring *string);
void	t_sstring_array_cstrpush_back(t_sstring_array *ssa, const char *cstr);
void	sstring_split(t_sstring_array *array, t_sstring const *s, char c);
void	sstring_split_with_slice(t_sstring_array *array, t_sstring const *s, const char *slice);
void	panicf(const char *fmt, ...);
#endif // SAFE_H
