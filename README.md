# Server tutorial

# Compile
- create executables : type `make`
- delete executables : type `make fclean`
- delete and create executables : type `make re`

# Usage
1. You should know your current IP address
    - for Linux
        ```shell
        hostname -i
        ```
    - for macOS
        - ethernet
            ```shell
            ipconfig getifaddr en0
            ```
        - Wi-Fi
            ```shell
            ipconfig getifaddr en1
            ```
2. run server (port number you want)
    ```shell
    ./server <port_number>
    ```
3. run client
    ```shell
    ./client <IP_address> <port_number>
    ```
    - IP address of step 1
    - Port number of step 2
