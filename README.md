# Web Server

A barebones web server in C.

## Why?

I love C.

## Build from source

The build is Makefile-based, so make sure you have GNU Make and GCC installed on your system, then run the following command:

``` bash
make
```

## Run from source

Run the following command to start the server, may take a few minutes in between uses:

``` bash
sudo ./webserver.out
```

You will receive the following info in the terminal:

``` bash
==== WAITING FOR CONNECTION TO [address] ====
```

In order to see the web server, open your favourite browser and go to ```[address]```.

The server will then stop and may take a minute or two to use again.

## Example file

``` c
#include <stdio.h>

// *********************
 
#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

// ^^^
// For definitions like AF_INET, SOCK_STREAM, INADDR_ANY and etc.

#include "include/server.h"

int main(int argc, char **argv)
{
    // Create then launch the server object
    struct Server server = init_server(AF_INET, 0, SOCK_STREAM, 80, 10, INADDR_ANY);
    launch_server(&server, "A Web Server in C!!");

    return 0;
}
```

## License

Web Server is licensed under the Apache 2.0 License.
