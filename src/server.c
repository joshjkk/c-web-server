#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <arpa/inet.h>
#include <netinet/in.h>

#include "include/server.h"

struct Server init_server(int domain, int protocol, int service, int port, int backlog, char *ip, u_long interface)
{
    struct Server server;

    server.domain = domain;
    server.protocol = protocol;
    server.service = service;
    server.port = port;
    server.backlog = backlog;
    server.ip = ip;

    server.address.sin_family = domain;
    server.address.sin_port = htons(port);
    server.address.sin_addr.s_addr = htonl(interface);

    server.socket = socket(server.domain, server.service, server.protocol);
    if (server.socket == 0)
    {
        perror("Failed to connect to socket");
        exit(1);
    }

    if (bind(server.socket, (struct sockaddr *)&server.address, sizeof(server.address)) < 0)
    {
        perror("Failed to bind the socket");
        exit(1);
    }

    if (listen(server.socket, server.backlog) < 0)
    {
        perror("Failed to listen to the socket ");
        exit(1);
    }

    return server;
}

void launch_server(struct Server *server)
{
    printf("==== WAITING FOR CONNECTION TO %s ====\n", server->ip);
}
