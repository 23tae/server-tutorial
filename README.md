# Server tutorial

# About
## client-server program
- ex00
    - Server sends to client a short message.
    - Client prints the received message.
- ex01
    - Client sends to server what user typed.
    - Server prints the received message.
    - Server sends it back to client.
    - Client prints the received message.
- ex02
    - Connect to server using web browser.
- ex03
    - Perl script which runs web server

# Compile
- Create executables : type `make`
- Delete executables : type `make fclean`
- Rebuild executables : type `make re`

# Usage
## ex00~02
- Run server
    ```shell
    ./server <port_number>
    ```
    - port_number : port that server will open

### ex00~01
- Run client
    ```shell
    ./client 127.0.0.1 <port_number>
    ```
    - port_number : server's port number
- ex00
    - **Server** will send message to **Client** and terminate the program.
- ex01
    - You can send message from **client** to **server**

### ex02
- Open web browser.
- Open url `127.0.0.1:<port_number>`
- Browser will show the message that server sent

## ex03
- Run server
    ```shell
    perl type-o-serve.pl
    ```
- Open browser
- Connect to the following url
    ```
    127.0.0.1:8080
    ```
- Send HTTP response message in shell
    - example
        ```shell
        HTTP/1.1 200 OK
        Content-Length:12

        hello world!
        .
        ```
