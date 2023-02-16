
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "error_utils.h"

int main()
{

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        moneta::error_utils::die("Invalid Socket");
    }

    struct sockaddr_in socket_address = {};
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = ntohs(1234);
    socket_address.sin_addr.s_addr = ntohl(0);

    int rv = connect(fd, (const sockaddr *)&socket_address, sizeof(socket_address));
    if (rv)
    {
        moneta::error_utils::die("Unable to connect");
    }

    char message[] = "hello";
    write(fd, message, strlen(message));

    char read_buffer[64] = {};
    ssize_t n = read(fd, read_buffer, sizeof(read_buffer) - 1);
    if (n < 0)
    {
        moneta::error_utils::die("Unable to get response");
    }

    std::cout << "Response from server: " << read_buffer << '\n';
    close(fd);

    return 0;
}
