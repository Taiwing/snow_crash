#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main()
{
	uid_t uid = getuid();
	uid_t euid = geteuid();

	printf("Exploit me\n");
	printf("uid = %d\neuid = %d\npid = %d\n", uid, euid, getpid());
	return (0);
}
