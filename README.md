# C Web Server

A web server in C.

[![Build](https://github.com/joshjkk/c-web-server/actions/workflows/Build.yml/badge.svg)](https://github.com/joshjkk/c-web-server/actions/workflows/Build.yml)

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
sudo ./server.out
```

You will receive the following info in the terminal:

``` bash
==== WAITING FOR CONNECTION TO [address] ====
```

In order to see the web server, open your favourite browser and go to ```[address]```.

### Routes

As of ```v0.2.0```, you can add your own routes to html pages inside the ```templates``` folder.

To see these routes, use the following function inside your main file:

``` c 
add_route(route, "page_address_of_route", "name_of_html_file.html");
```

The routes ```/about``` and ```/``` come already set up, as well as a 404 Page for unknown routes.

#### Stylesheet

The stylesheet for these html can be found inside the ```static``` folder.

## License

Web Server is licensed under the Apache 2.0 License.
