# Server tutorial

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
    ./client <ip_address> <port_number>
    ```

    - ip_address
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
    - port_number : server's port number
