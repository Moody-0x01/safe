# include <safe.h>
#include <unistd.h>

// typedef struct s_string {
// 	char  *items;
// 	size_t length;
// 	size_t cap;
// } s_string;

int main()
{
	char c;
	t_sstring string = {0};
	t_sstring Tot = {0};
	int eof = 0;

	for (;;)
	{
		write(1, "> ", 2);
		string.size = 0;
		if (string.items)
			memset(string.items, 0, string.cap);
		for (;;)
		{
			if (read(0, &c, 1) <= 0)
			{
				eof = 1;
				break ;
			}
			sstring_push(&string, c);
			if (string.items[string.size - 1] == '\n')
			{
				string.items[string.size - 1] = 0;
				break ;
			}
		}
		if (string.size > 0)
		{
			if (!strcmp(string.items, "quit"))
				break ;
			string_join(&Tot, &string);
		}
		if (eof)
			break ;
	}
	write(1, Tot.items, Tot.size);
	sadisplay();
	sadestroy();
	return (0);
}
