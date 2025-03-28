# include <safe.h>

void	sstring_push(t_sstring *string, int c)
{
	if (string->size >= string->cap)
	{
		if (!string->cap) string->cap = 2;
		else
			string->cap *= 2;
		string->items = sarealloc(string->items, string->cap);
	}
	string->items[string->size++] = c;
}

void	string_join(t_sstring *string, t_sstring *other)
{
	size_t index;

	index = 0;
	while (index < other->size)
	{
		sstring_push(string, other->items[index]);
		index++;
	}
}
