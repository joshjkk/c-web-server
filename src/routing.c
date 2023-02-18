#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include "include/routing.h"

struct Route *init_route(char *key, char *value)
{
    struct Route *temp = (struct Route *)malloc(sizeof(struct Route));

    temp->key = key;
    temp->value = value;

    temp->left = temp->right = NULL;

    return temp;
}

struct Route *add_route(struct Route *route, char *key, char *value)
{
    if (route == NULL)
        return init_route(key, value);

    if (key < route->key)
        route->left = add_route(route->left, key, value);

    else if (key > route->key)
        route->right = add_route(route->right, key, value);

    return route;
}

struct Route * search(struct Route *route, char* key)
{
	if (route == NULL)
		return NULL;

	if (strcmp(key, route->key) == 0)
		return route;

	else if (strcmp(key, route->key) > 0)
		return search(route->right, key);

	else if (strcmp(key, route->key) < 0)
		return search(route->left, key);
    
    return route;
}

void inorder(struct Route *route)
{
    if (route != NULL) 
    {
        inorder(route->left);
        printf("%s -> %s \n", route->key, route->value);
        inorder(route->right);
    }
}

void render_route(struct Route *route, int client_socket, char *client_msg)
{
    char *method = "";
    char *url_route = "";

    char *client_http_header = strtok(client_msg, "\n");
        
    printf("\n\n%s\n\n", client_http_header);

    char *header_token = strtok(client_http_header, " ");

    int header_parse_counter = 0;

    while (header_token != NULL)
    {
        switch (header_parse_counter)
        {
            case 0:
                method = header_token;
                break;

            case 1:
                url_route = header_token;
                break;
        }

        header_token = strtok(NULL, " ");
        header_parse_counter++;
    }

    printf("The method is %s\n", method);
    printf("The route is %s\n", url_route);

    char template[256] = "";
		
    if (strstr(url_route, "/static/") != NULL) 
        strcat(template, "static/index.css");

    else 
    {
        struct Route *destination = search(route, url_route);
        strcat(template, "templates/");

        if (destination == NULL) 
            strcat(template, "404.html");
        
        else 
            strcat(template, destination->value);
    }

    char *response_data = NULL;

    FILE *file = fopen(template, "r");

    if (file != NULL)
    {
        fseek(file, 0, SEEK_END);
        long fsize = ftell(file);
        fseek(file, 0, SEEK_SET); 

        response_data = (char*)calloc((fsize + 1), sizeof(char));

        char ch;
        int i = 0;

        while((ch = fgetc(file)) != EOF)
        {
            response_data[i] = ch;
            i++;
        }

        fclose(file);
    }

    char http_header[2560] = "HTTP/1.1 200 OK\r\n\r\n";

    strcat(http_header, response_data);
    strcat(http_header, "\r\n\r\n");

    send(client_socket, http_header, sizeof(http_header), 0);
}
