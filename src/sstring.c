# include <safe.h>

// BULKY TOOODO:
// h.capitalize()    h.expandtabs(     h.isalpha()       h.isnumeric()     h.ljust(          h.removesuffix(   h.rsplit(         h.swapcase()                        
// h.casefold()      h.find(           h.isascii()       h.isprintable()   h.lower()         h.replace(        h.rstrip(         h.title()                           
// h.center(         h.format(         h.isdecimal()     h.isspace()       h.lstrip(         h.rfind(          h.split(          h.translate(                        
// h.count(          h.format_map(     h.isdigit()       h.istitle()       h.maketrans(      h.rindex(         h.splitlines(     h.upper()                           
// h.encode(         h.index(          h.isidentifier()  h.isupper()       h.partition(      h.rjust(          h.startswith(     h.zfill(                            
// h.endswith(       h.isalnum()       h.islower()       h.join(           h.removeprefix(   h.rpartition(     h.strip(                                              
void	sstring_cstrpush(t_sstring *string, const char *str)
{
	while (str && *str)
	{
		sstring_push(string, *str);
		str++;
	}
	string->items[string->size] = 0;
}

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

void	sstring_push_front(t_sstring *string, int c)
{
	if (string->size + 1 >= string->cap)
	{
		if (!string->cap) string->cap = 2;
		else
			string->cap *= 2;
		string->items = sarealloc(string->items, string->cap);
	}
	memmove(string->items + 1, string->items + 0, string->size);
	string->items[0] = c;
	string->size++;
}

void	sstring_join(t_sstring *string, t_sstring *other)
{
	size_t index;

	index = 0;
	while (index < other->size)
	{
		sstring_push(string, other->items[index]);
		index++;
	}
}

void	sstring_strip(t_sstring *string)
{
	int	left  = 0;
	int	right;

	if (!string || !string->size || !string->items)
		return ;
	while (string->size && isspace(string->items[left]))
		left++;
	memmove(string->items, string->items + left, (string->size - left));
	string->size -= left;
	right = string->size - 1;
	while (string->size && isspace(string->items[right]))
		right--;
	string->items[right + 1] = 0;
}

// TODO: capitalize
