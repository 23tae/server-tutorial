#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // sockaddr_in, read, write
#include <arpa/inet.h> // htnol, htons, INADDR_ANY, sockaddr_in
#include <sys/socket.h>
#include <stdbool.h>

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
int	init_listening_socket(char *port)
{
	int	listening_socket;
	struct sockaddr_in server_addr;

	listening_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (listening_socket == -1)
		print_error("Error occured in socket");
	init_server_addr(&server_addr, port);

	int reuseaddr = 1;
	if (setsockopt(listening_socket, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr)) < 0)
		print_error("Error occured in bind option");

	// Bind socket and server IP address
	if (bind(listening_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
		print_error("Error occured in bind");

	// Create connection request queue as maximum number 5
	if (listen(listening_socket, 5) == -1)
		print_error("Error occured in listen");
	return (listening_socket);
}

int	connect_socket(int listening_socket)
{
	int connection_socket;
	struct sockaddr_in client_addr;
	socklen_t client_addr_size;

	client_addr_size = sizeof(client_addr);
	printf("Listening port...\n");
	connection_socket = accept(listening_socket, (struct sockaddr *)&client_addr, &client_addr_size);
	if (connection_socket == -1)
		print_error("Error occured in accept");
	printf("Connected to client!\n");
	return (connection_socket);
}

void	listen_message(int connection_socket)
{
    char buffer[1024];
    int num_bytes = 0;
	bool is_first = false;
    
    // Read from the client until the connection is closed
    while ((num_bytes = read(connection_socket, buffer, sizeof(buffer))) > 0)
	{
		if (is_first == false)
		{
			printf("<Received message>\n");
			is_first = true;
		}
        // Process the message received from the client
		printf("%.*s", num_bytes, buffer);
		write(connection_socket, buffer, num_bytes);
    }
}

int	main(int argc, char **argv)
{
	int	listening_socket;
	int	connection_socket;

	if (argc != 2)
		print_error("Usage : ./server <port number>");

	listening_socket = init_listening_socket(argv[1]);
	connection_socket = connect_socket(listening_socket);
	listen_message(connection_socket);
	printf("Socket closed\n");
	close(connection_socket);
	close(listening_socket);
	return (0);
}
