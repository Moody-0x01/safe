#include <safe.h>

void	t_sstring_array_push_back(t_sstring_array *ssa, t_sstring *string)
{
	t_sstring_array_cstrpush_back(ssa, string->items);
}

void	t_sstring_array_cstrpush_back(t_sstring_array *ssa, const char *cstr)
{
	if (!ssa)
		return ;
	if (ssa->size >= ssa->cap)
	{
		if (!ssa->cap) ssa->cap = 2;
		else
			ssa->cap *= 2;
		ssa->items = sarealloc(ssa->items, (ssa->cap * sizeof(t_sstring)));
	}
	sstring_cstrpush(&ssa->items[ssa->size], cstr);
	ssa->size++;
}
