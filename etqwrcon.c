#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	char *host;
	char *port;
	char *password;
	char *command;
	char default_port[] = "27733";

	if (argc < 4) {
		fprintf(stderr, "usage: %s address[:port] password command\n", argv[0]);
		return 1;
	}

	host = strtok(argv[1], ":");
	port = strtok(NULL, ":");
	password = argv[2];
	command = argv[3];

	if (!port)
		port = default_port;

	printf("%s:%s\npassword: %s\ncommand: %s\n", host, port, password, command);

	return 0;
}
