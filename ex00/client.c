#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void	print_error(char *message)
{
	write(2, message, strlen(message));
	write(2, "\n", 1);
	exit(1);
}

void	init_server_addr(struct sockaddr_in *server_addr, char *ip_addr, int port)
{
	memset(server_addr, 0, sizeof(*server_addr));
	server_addr->sin_family = AF_INET;
	server_addr->sin_addr.s_addr = inet_addr(ip_addr);
	server_addr->sin_port = htons(port);
}

int	main(int argc, char **argv)
{
	int	connection_socket;
	struct sockaddr_in server_addr;
	char buffer[1024];

	if (argc != 3)
		print_error("Usage : ./client <IP address> <Port number>");
	memset(buffer, 0, sizeof(buffer));

	connection_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (connection_socket == -1)
		print_error("Error in socket");

	init_server_addr(&server_addr, argv[1], atoi(argv[2]));

	if (connect(connection_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
		print_error("Error in connect");

	if (read(connection_socket, buffer, sizeof(buffer)) == -1)
		print_error("Error in read");
	printf("Server : %s\n", buffer);
	close(connection_socket);
	return (0);
}
