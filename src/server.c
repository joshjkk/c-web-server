#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <arpa/inet.h>
#include <netinet/in.h>

#include "include/server.h"

struct Server init_server(int domain, int protocol, int service, int port, int backlog, u_long interface)
{
    struct Server server;

    server.domain = domain;
    server.protocol = protocol;
    server.service = service;
    server.port = port;
    server.backlog = backlog;

    server.address.sin_family = domain;
    server.address.sin_port = htons(port);
    server.address.sin_addr.s_addr = htonl(interface);

    server.socket = socket(server.domain, server.service, server.protocol);
    if (server.socket == 0)
    {
        perror("Failed to connect to socket.\n");
        exit(1);
    }

    if (bind(server.socket, (struct sockaddr *)&server.address, sizeof(server.address)) < 0)
    {
        perror("Failed to bind the socket.\n");
        exit(1);
    }

    if (listen(server.socket, server.backlog) < 0)
    {
        perror("Failed to listen to the socket.\n");
        exit(1);
    }

    return server;
}

void launch_server(struct Server *server, char *welcome_title)
{
    printf("==== WAITING FOR CONNECTION TO 127.0.0.1 ====\n");

    int address_length = sizeof(server->address);
    int new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&address_length);

    char buffer[25600];
    read(new_socket, buffer, 25600);

    printf("%s\n", buffer);

    char hello[512];
    snprintf(hello, 512, "HTTP/1.1 200 OK\nDate: Mon 27 Jul 2009 12:28:53 GMT\nServer: Apache/2.2.14 (Win32)\nLast-Modified: Wed, 22 Jul 2009 19:15:56 GMT\nContent-Length: 88\nContent-Type: text/html\nConnection: Closed\n\n<html><body><h1>%s</h1></body></html>", welcome_title);

    write(new_socket, hello, strlen(hello));
    close(new_socket);
}
