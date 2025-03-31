# include <safe.h>
#include <unistd.h>

void	simple_shell_test()
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
			sstring_join(&Tot, &string);
		}
		if (eof)
			break ;
	}
	write(1, Tot.items, Tot.size);
	sadisplay();
	sadestroy();
}

int main()
{
	// t_sstring	string = {0};
	// (void)_;
	// if (argv[1])
	// {
	// 	sstring_cstrpush(&string, argv[1]);
	// 	printf("|%s|\n", string.items);
	// 	sstring_strip(&string);
	// 	printf("|%s|\n", string.items);
	// }
	//
	//
	simple_shell_test();
	return (0);
}
