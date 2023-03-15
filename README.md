# Server tutorial

# About
## client-server program
- ex00
    - server sends to client a short message.
    - client prints the received message.
- ex01
    - client sends to server what user typed.
    - server prints the received message.
    - server sends it back to client.
    - client prints the received message.
- ex02
    - connect to server using web browser.

# Compile
- Create executables : type `make`
- Delete executables : type `make fclean`
- Rebuild executables : type `make re`

# Usage
1. Run server
    ```shell
    ./server <port_number>
    ```
    - port_number : port that server will open
2. Run client
    ```shell
    ./client 127.0.0.1 <port_number>
    ```
    - port_number : server's port number
