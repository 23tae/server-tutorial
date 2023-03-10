CC = gcc
CFLAGS = -Wall -Wextra -Werror

SERVER = server
CLIENT = client

all: $(SERVER) $(CLIENT)

$(SERVER): server.c
	@$(CC) $(CFLAGS) -o server server.c
	@echo "$(SERVER) made"

$(CLIENT): client.c
	@$(CC) $(CFLAGS) -o client client.c
	@echo "$(CLIENT) made"

fclean:
	@rm $(SERVER) $(CLIENT)

re:
	@make -s fclean
	@make -s all
