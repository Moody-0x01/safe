# include <salloc.h>

int main()
{
	for (int i = 1; i < 100; ++i)
	{
		char *nums = salloc(i * 10);
		memset(nums, '*', (i * 10) - 1);
		printf("BLOCK:\n%s\n", nums);
	}

	sa_display();
	// safree(nums);
	sa_destroy();
	sa_display();

	for (int i = 1; i < 100; ++i)
	{
		char *nums = salloc(i * 10);
		memset(nums, '*', (i * 10) - 1);
		printf("BLOCK:\n%s\n", nums);
	}

	sa_display();
	// safree(nums);
	sa_destroy();
	sa_display();
	return (0);
}
