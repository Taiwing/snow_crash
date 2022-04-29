#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main(void)
{
	uid_t uid = getuid();
	uid_t euid = geteuid();

	printf("uid = %d\neuid = %d\npid = %d\n", uid, euid, getpid());
	execve("./test", (char *[2]){ "./test", NULL }, NULL);
	return (0);
}
