#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

struct Server 
{
    int socket;
    int domain;
    int protocol;
    int service;
    int port;
    int backlog;
    char *ip;
    u_long interface;

    struct sockaddr_in address;

};

struct Server init_server(int domain, int protocol, int service, int port, int backlog, char *ip, u_long interface);

void launch_server(struct Server *server);

#endif // SERVER_H
