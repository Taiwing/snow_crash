#define _GNU_SOURCE

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char **argv, char **env)
{
	gid_t rgid;
	uid_t ruid;
	char *args[5] = {
		"/usr/bin/php", 
		"/home/user/level06/level06.php",
		strdup(""),
		strdup(""),
		NULL
	};

	if (argv[1] != NULL) {
		free(args[2]);
		args[2] = strdup(argv[1]);
		if (argv[2] != NULL) {
			free(args[3]);
			args[3] = strdup(argv[2]);
		}
	}
	rgid = getegid();
	ruid = geteuid();
	setresgid(rgid, rgid, rgid);
	setresuid(ruid, ruid, ruid);
	execve("/usr/bin/php", args, env);
	return (0);
}
