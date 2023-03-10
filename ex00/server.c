#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // sockaddr_in, read, write
#include <arpa/inet.h> // htnol, htons, INADDR_ANY, sockaddr_in
#include <sys/socket.h>

void	print_error(char *message)
{
	write(2, message, strlen(message));
	write(2, "\n", 1);
	exit(1);
}

/**
 * @brief Initialize server. Set IP address and Port.
 * 
 * @param server_addr server setting
 * @param port port number
 */
void	init_server_addr(struct sockaddr_in *server_addr, char *port)
{
	memset(server_addr, 0, sizeof(*server_addr));
	server_addr->sin_family = AF_INET; // IPv4
	server_addr->sin_addr.s_addr = htonl(INADDR_ANY); // IP address
	server_addr->sin_port = htons(atoi(port)); // Port
}

/**
 * @brief Initialize socket.
 * 
 * @param port port number
 * @return int socket descriptor
 */
int	init_server_socket(char *port)
{
	int	server_socket;
	struct sockaddr_in server_addr;

	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket == -1)
		print_error("Error occured in socket");
	init_server_addr(&server_addr, port);

	// Bind socket and server IP address
	if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
		print_error("Error occured in bind");

	// Create connection request queue as maximum number 5
	if (listen(server_socket, 5) == -1)
		print_error("Error occured in listen");
	return (server_socket);
}

int	connect_socket(int server_socket)
{
	int client_socket;
	char *message;
	struct sockaddr_in client_addr;
	socklen_t client_addr_size;

	client_addr_size = sizeof(client_addr);
	client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_size);
	if (client_socket == -1)
		print_error("Error occured in accept");
	printf("Found client!\n");
	message = "Server connected!\n";
	write(client_socket, message, strlen(message));
}

int	main(int argc, char **argv)
{
	int	server_socket;
	int	client_socket;

	if (argc != 2)
		print_error("Usage : ./server <port number>");

	server_socket = init_server_socket(argv[1]);
	client_socket = connect_socket(server_socket);

	printf("Close connection.\n");
	close(client_socket);
	close(server_socket);
	return (0);
}
