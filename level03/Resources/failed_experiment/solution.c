#define _POSIX_C_SOURCE 1

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/prctl.h>

int main(int argc, char **argv)
{
	unsigned int	debugger_pid, self;
	//char			*sub_argv[] = { "/home/user/level03/level03", NULL };
	char			*sub_argv[] = { "./sub", NULL };

	if (argc < 2)
	{
		fprintf(stderr, "usage: %s <debugger_pid>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	debugger_pid = (unsigned int)atoi(argv[1]);
	self = getpid();
	prctl(PR_SET_PTRACER, debugger_pid, 0, 0, 0);
	printf("authorized debugging process %u to attach to self (%u)\n",
		debugger_pid, self);
	printf("waiting ...\n");
	kill(self, SIGSTOP);
	printf("executing '%s' command\n", sub_argv[0]);
	if (execve(sub_argv[0], sub_argv, NULL) < 0)
		fprintf(stderr, "%s: execve: %s", argv[0], strerror(errno));
	return (EXIT_FAILURE);
}
