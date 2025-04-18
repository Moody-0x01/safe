#include <safe.h>

int	in(char c, const char *slice)
{
	size_t	i;

	i = 0;
	while (slice[i])
	{
		if (slice[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	sstring_split(t_sstring_array *array, t_sstring const *s, char c)
{
	size_t		cursor;
	t_sstring	str;

	memset(array, 0, sizeof(*array));
	memset(&str, 0, sizeof(str));
	cursor = 0;
	while (cursor < s->size)
	{
		while (cursor < s->size && s->items[cursor] == c)
			cursor++;
		if (str.items && str.cap)
		{
			memset(str.items, 0, str.cap);
			str.size = 0;
		}
		while (cursor < s->size && s->items[cursor] != c)
		{
			sstring_push(&str, s->items[cursor]);
			cursor++;
		}
		t_sstring_array_push_back(array, &str);
	}
}

void	sstring_split_with_slice(t_sstring_array *array, t_sstring const *s, const char *slice)
{
	size_t		cursor;
	t_sstring	str;

	memset(array, 0, sizeof(*array));
	memset(&str, 0, sizeof(str));
	cursor = 0;
	while (cursor < s->size)
	{
		while (cursor < s->size && in(s->items[cursor], slice))
			cursor++;
		if (str.items && str.cap)
		{
			memset(str.items, 0, str.cap);
			str.size = 0;
		}
		while (cursor < s->size && !in(s->items[cursor], slice))
		{
			sstring_push(&str, s->items[cursor]);
			cursor++;
		}
		if (str.size)
			t_sstring_array_push_back(array, &str);
	}
}
