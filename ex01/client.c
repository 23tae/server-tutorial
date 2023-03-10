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
    int num_bytes;
	char send_buffer[1024];
	char receive_buffer[1024];

	memset(send_buffer, 0, sizeof(send_buffer));
	memset(receive_buffer, 0, sizeof(receive_buffer));
	printf("Connected to server!\n");
	while (1)
	{
		printf("Send message : ");
		if (scanf("%s", send_buffer) == -1)
			break;
		if (send(client_socket, send_buffer, strlen(send_buffer), 0) == -1)
			print_error("Error in send");
		if ((num_bytes = read(client_socket, receive_buffer, sizeof(receive_buffer))) < 0)
			print_error("Error in read");
		printf("Receive message : %.*s\n", num_bytes, receive_buffer);
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
	close(client_socket);
	return (0);
}
