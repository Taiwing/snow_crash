#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "%s: missing argument\n", argv[0]);
		return (EXIT_FAILURE);
	}

	char *arg = argv[1];
	for (int i = 0; arg[i]; ++i)
		putchar(arg[i] - i);
	return (EXIT_SUCCESS);
}
