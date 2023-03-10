#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // sockaddr_in, read, write
#include <arpa/inet.h> // htnol, htons, INADDR_ANY, sockaddr_in
#include <sys/socket.h>

void	print_error(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
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
int	init_socket(char *port)
{
	int	server_sock;
	struct sockaddr_in server_addr;

	server_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (server_sock == -1)
		print_error("Error occured while socket");
	init_server_addr(&server_addr, port);

	// Bind socket and server IP address
	if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
		print_error("Error occured while bind");

	// Create connection request queue as maximum number 5
	if (listen(server_sock, 5) == -1)
		print_error("Error occured while listen");
	return (server_sock);
}

int	socket_connection(int server_sock)
{
	int client_sock;
	struct sockaddr_in client_addr;
	socklen_t client_addr_size;

	client_addr_size = sizeof(client_addr);
	client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_addr_size);
	if (client_sock == -1)
		print_error("Error occured while accept");

	char msg[] = "Server Connected!\n";
	write(client_sock, msg, sizeof(msg));
}

int	main(int argc, char **argv)
{
	int	server_sock;
	int	client_sock;

	if (argc != 2)
		print_error("Usage : ./server <port number>");

	server_sock = init_socket(argv[1]);
	client_sock = socket_connection(server_sock);

	close(client_sock);
	close(server_sock);
	return (0);
}
