#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc,char **argv,char **envp)
{
  gid_t gid;
  uid_t uid;
  char *logname, *command = NULL;
  
  gid = getegid();
  uid = geteuid();
  setresgid(gid, gid, gid);
  setresuid(uid, uid, uid);
  logname = getenv("LOGNAME");
  asprintf(&command, "/bin/echo %s ", logname);
  return system(command);
}
