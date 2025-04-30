# include <safe.h>
#include <unistd.h>

void	simple_shell_test()
{
	char c;
	t_sstring_array strings = {0};
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
			t_sstring_array_push_back(&strings, &string);
		}
		if (eof)
			break ;
	}
	ft_printf("===========(Joined)===========\n");
	write(1, Tot.items, Tot.size);
	ft_printf("===========(======)===========\n");
	ft_printf("===========(Collected)===========\n");
	for (size_t i = 0; i < strings.size; i++)
	{
		write(1, strings.items[i].items, strings.items[i].size);
		ft_printf("\n");
	}
	ft_printf("===========(======)===========\n");
	// sadisplay();
	sadestroy();
}

int main()
{
	// t_sstring	string = {0};
	// (void)_;
	// if (argv[1])
	// {
	// 	t_sstring_array array;
	//
	// 	sstring_cstrpush(&string, argv[1]);
	// 	sstring_split_with_slice(&array, &string, "<|>");
	// 	printf("Split `%s` using <|> \n", string.items);
	// 	for (size_t i = 0; i < array.size; i++)
	// 	{
	// 		printf("[  %zu  ] \n", i);
	// 		printf("%s\n", array.items[i].items);
	// 		// write(1, , array.items[i].size);
	// 	}
	// 	sadestroy();
	// }
	simple_shell_test();
	return (0);
}
