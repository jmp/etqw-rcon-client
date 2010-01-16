#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <netdb.h>

#define PACKET_SIZE 512
#define RESPONSE_SIZE 20480
#define SOCKET_TIMEOUT 3

int main(int argc, char* argv[])
{
	char *host;
	char *port;
	char *password;
	char *command;
	char packet[PACKET_SIZE] = {0};
	char default_port[] = "27733";
	struct addrinfo hints;
	struct addrinfo *result;
	struct addrinfo *p;
	struct timeval tv;
	fd_set fds;
	int error;
	int sock;

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

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;

	error = getaddrinfo(host, port, &hints, &result);
	if (error != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(error));
		return 1;
	}

	for (p = result; p != NULL; p = p->ai_next) {
		sock = socket(result->ai_family, result->ai_socktype, 0);
		if (sock == -1) {
			fprintf(stderr, "socket error\n");
			continue;
		}
		break;
	}

	if (p == NULL) {
		fprintf(stderr, "failed to create socket\n");
		return 1;
	}

	FD_ZERO(&fds);
	FD_SET(sock, &fds);
	tv.tv_sec = SOCKET_TIMEOUT;
	tv.tv_usec = 0;

	sprintf(packet, "\xff\xffrcon\xff%s\xff%s\xff", password, command);
	if (sendto(sock, packet, strlen(packet), 0, p->ai_addr, p->ai_addrlen) != -1) {
		int i = 0;
		ssize_t n = 0;
		char response[RESPONSE_SIZE] = {0};

		select(sock + 1, &fds, NULL, NULL, &tv);

		if (!FD_ISSET(sock, &fds))
			fprintf(stderr, "host timed out\n");
		else if ((n = recvfrom(sock, response, RESPONSE_SIZE, 0, NULL, NULL)) < 0)
			fprintf(stderr, "recv error\n");

		for (i = 12; response[i] != 0 && i < n; ++i)
			putchar(response[i]);
	}
	else
		fprintf(stderr, "sendto error\n");

	freeaddrinfo(result);
	close(sock);

	return 0;
}
