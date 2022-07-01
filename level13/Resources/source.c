#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>

// Magic hashing function for the flags
char * ft_des(char *param_1)

{
	char cVar1;
	char *pcVar2;
	uint32_t uVar3;
	char *pcVar4;
	uint32_t local_20;
	int local_1c;
	int local_18;
	int local_14;

	pcVar2 = strdup(param_1);
	local_1c = 0;
	local_20 = 0;
	do {
		uVar3 = 0xffffffff;
		pcVar4 = pcVar2;
		do {
			if (uVar3 == 0) break;
			uVar3 = uVar3 - 1;
			cVar1 = *pcVar4;
			++pcVar4;
		} while (cVar1 != '\0');
		if (~uVar3 - 1 <= local_20) {
			return pcVar2;
		}
		if (local_1c == 6) {
			local_1c = 0;
		}
		if ((local_20 & 1) == 0) {
			if ((local_20 & 1) == 0) {
				for (local_14 = 0; local_14 < "0123456"[local_1c]; local_14 = local_14 + 1) {
					pcVar2[local_20] = pcVar2[local_20] + -1;
					if (pcVar2[local_20] == '\x1f') {
						pcVar2[local_20] = '~';
					}
				}
			}
		}
		else {
			for (local_18 = 0; local_18 < "0123456"[local_1c]; local_18 = local_18 + 1) {
				pcVar2[local_20] = pcVar2[local_20] + '\x01';
				if (pcVar2[local_20] == '\x7f') {
					pcVar2[local_20] = ' ';
				}
			}
		}
		local_20 = local_20 + 1;
		local_1c = local_1c + 1;
	} while (1);
}

int main(void)
{
	if (getuid() != 4242) {
		printf("UID %d started us but we we expect %d\n", getuid(), 4242);
		exit(1);
	}
	printf("your token is %s\n", ft_des("boe]!ai0FB@.:|L6l@A?>qJ}I"));
	return (0);
}
