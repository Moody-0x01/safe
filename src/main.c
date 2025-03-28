# include <safe.h>
#include <unistd.h>

// typedef struct s_string {
// 	char  *items;
// 	size_t length;
// 	size_t cap;
// } s_string;

int main()
{
	t_string string = {0};

	for (;;)
	{
		write(1, "> ", 2);
		string.size = 0;
		if (string.items)
			memset(string.items, 0, string.cap);
		for (;;)
		{
			if (string.size >= string.cap)
			{
				if (!string.cap) string.cap = 2;
				else
					string.cap *= 2;
				string.items = sarealloc(string.items, string.cap);
			}
			if (read(0, string.items + string.size, 1) < 0)
				break ;
			if (string.items[string.size] == '\n')
			{
				string.items[string.size] = 0;
				break ;
			}
			string.size++;
		}
		if (!strcmp(string.items, "quit"))
			break ;
		printf("TYPED: `%s`\n", string.items);
	}
	sa_display();
	return (0);
}
