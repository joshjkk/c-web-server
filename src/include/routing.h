#ifndef ROUTING_H
#define ROUTING_H

struct Route
{
    char *key;
    char *value;

    struct Route *left;
    struct Route *right;
};

struct Route *init_route(char *key, char *value);

struct Route *add_route(struct Route *route, char *key, char *value);

struct Route *search(struct Route *route, char *key);

void inorder(struct Route *route);

void render_route(struct Route *route, int client_socket, char *client_msg);

#endif // ROUTING_H
