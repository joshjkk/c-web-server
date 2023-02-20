#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
// Socket includes
#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

// Server and route includes
#include "include/server.h"
#include "include/routing.h"

int main(int argc, char **argv)
{
    // Create the server object
    struct Server server = init_server(AF_INET, 0, SOCK_STREAM, 80, 10, "127.0.0.1", INADDR_ANY);

    // Add routes to html files
    struct Route *route = init_route("/", "index.html");
    add_route(route, "/about", "about.html");

    // Print the ip of the server
    printf("==== WAITING FOR CONNECTION TO %s ====\n", server.ip);

	// Display all available routes
	printf("\n==== ALL VAILABLE ROUTES ====\n");
	inorder(route);

    int client_socket;

    while (1)
    {
        // Accept client connections
        client_socket = accept(server.socket, NULL, NULL);

        // Read client message
        char client_msg[2560];
        read(client_socket, client_msg, sizeof(client_msg));
        printf("Client message: %s\n", client_msg);

        // Render the webpage
        render_route(route, client_socket, client_msg);
        close(client_socket);
    }

    return 0;
}
