CC = gcc
CFLAGS = -Wall -Wextra -Werror

SERVER = server

all: $(SERVER)

$(SERVER): server.c
	@$(CC) $(CFLAGS) -o server server.c
	@echo "$(SERVER) made"

fclean:
	@rm $(SERVER)

re:
	@make -s fclean
	@make -s all
