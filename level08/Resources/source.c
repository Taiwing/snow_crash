#include <err.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int	main(int argc, char **argv, char **envp)
{
	int		fd;
	ssize_t	rc;
	char	buf[1024];

	if (argc == 1) {
		printf("%s [file to read]\n", *argv);
		exit(1);
	}
	if (strstr(argv[1], "token") != NULL) {
		printf("You may not access '%s'\n", argv[1]);
		exit(1);
	}
	if ((fd = open(argv[1], 0)) < 0) {
		err(1, "Unable to open %s", argv[1]);
	}
	if ((rc = read(fd, buf, 1024)) < 0) {
		err(1, "Unable to read fd %d", fd);
	}
	return write(1, buf, rc);
}
