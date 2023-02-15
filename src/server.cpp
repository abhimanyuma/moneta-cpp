
#include <iostream>
#include <sys/socket.h>

#include "error_utils.h"

int main()
{

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        moneta::error_utils::die("Invalid Socket");
    }
    return 0;
}
