#include <stdio.h>

// *********************
 
#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

// ^^^
// For definitions like AF_INET, SOCK_STREAM, INADDR_ANY and etc.

#include "../src/include/server.h"

int main(int argc, char **argv)
{
    // Create then launch the server object
    struct Server server = init_server(AF_INET, 0, SOCK_STREAM, 80, 10, INADDR_ANY);
    launch_server(&server, "A Web Server in C!!");

    return 0;
}
