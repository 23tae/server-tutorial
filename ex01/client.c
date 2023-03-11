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

void	send_message(int client_socket)
{
	ssize_t	bytes = 0;
	size_t	len = 0;
    int received_bytes = 0;
	char *send_buffer = NULL;
	char receive_buffer[1024];

	memset(receive_buffer, 0, sizeof(receive_buffer));
	printf("Connected to server!\n");
	while (1)
	{
		printf("Sent message : ");
		if ((bytes = getline(&send_buffer, &len, stdin)) == -1)
			break;
		if (send(client_socket, send_buffer, bytes, 0) == -1)
			print_error("Error in send");
		if ((received_bytes = read(client_socket, receive_buffer, sizeof(receive_buffer))) < 0)
			print_error("Error in read");
		printf("Received message : %.*s", received_bytes, receive_buffer);
	}
}
int	main(int argc, char **argv)
{
	int	client_socket;
	struct sockaddr_in server_addr;

	if (argc != 3)
		print_error("Usage : ./client <IP address> <Port number>");

	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket == -1)
		print_error("Error in socket");
	init_server_addr(&server_addr, argv[1], atoi(argv[2]));
	if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
		print_error("Error in connect");
	send_message(client_socket);
	printf("\nSocket closed\n");
	close(client_socket);
	return (0);
}
