#include "error_utils.h"

#include <iostream>
#include <errno.h>

namespace moneta
{
    namespace error_utils
    {
        // TODO: Replace this with C++ Style String for safety
        void die(const char *msg)
        {
            /*
             * Takes a message after an error and prints the error code
             * and prints a user provided message and aborts
             */
            int err = errno;
            std::cout << '[' << err << "] " << msg << '\n';
            abort();
        }
    }
}
