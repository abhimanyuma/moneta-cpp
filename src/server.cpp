
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "error_utils.h"

static void read_connection(int conn_fd)
{
    char read_buffer[64] = {};
    ssize_t n = read(conn_fd, read_buffer, sizeof(read_buffer) - 1);

    if (n < 0)
    {
        std::cout << "Read Function Error";
        return;
    }

    std::cout << "Client Message: " << read_buffer << '\n';
    char write_buffer[] = "world";
    write(conn_fd, write_buffer, strlen(write_buffer));
}

int main()
{

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        moneta::error_utils::die("Invalid Socket");
    }

    int value = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));

    struct sockaddr_in socket_address = {};
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = ntohs(1234);
    socket_address.sin_addr.s_addr = ntohl(0);

    int rv = bind(fd, (const sockaddr *)&socket_address, sizeof(socket_address));
    if (rv)
    {
        moneta::error_utils::die("Invalid Bind");
    }

    rv = listen(fd, SOMAXCONN);
    if (rv)
    {
        moneta::error_utils::die("Unable to listen");
    }

    while (true)
    {
        struct sockaddr_in client_address = {};
        socklen_t socklen = sizeof(client_address);
        int conn_fd = accept(fd, (struct sockaddr *)&client_address, &socklen);
        if (conn_fd < 0)
        {
            continue;
        }

        read_connection(conn_fd);
        close(conn_fd);
    }

    return 0;
}
