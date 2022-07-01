#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int	main(int argc, char **argv)
{
  char					*file;
  char					*host;
  int					send_socket;
  char					buffer [4096];
  int					fd;
  ssize_t				rc;
  struct sockaddr_in	sin = { 0 };

  if (argc < 3) {
    printf("%s file host\n\tsends file to host if you have access to it\n",
		*argv);
    exit(1);
  }
  file = argv[1];
  host = argv[2];
  if (access(file, 4)) {
    return (printf("You don\'t have access to %s\n", file));
  }

  printf("Connecting to %s:6969 .. ", host);
  fflush(stdout);
  send_socket = socket(AF_INET, 1, 0);
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = inet_addr(host);
  sin.sin_port = htons(6969);
  if (connect(send_socket, (const struct sockaddr *)&sin, 0x10) < 0) {
    printf("Unable to connect to host %s\n", host);
    exit(1);
  }

  if (write(send_socket, ".*( )*.\n", 8) < 0) {
    printf("Unable to write banner to host %s\n", host);
    exit(1);
  }
  printf("Connected!\nSending file .. ");
  fflush(stdout);
  if ((fd = open(file, 0)) < 0) {
    puts("Damn. Unable to open file");
    exit(1);
  }
  if ((rc = read(fd, buffer, 4096)) < 0) {
    printf("Unable to read from file: %s\n", strerror(errno));
    exit(1);
  }
  write(send_socket, buffer, rc);

  return (puts("wrote file!"));
}
