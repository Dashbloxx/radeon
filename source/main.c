#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *  Apparently, on my system `SO_REUSEPORT` isn't defined. Let's include `sys/socket.h` just in case if it is defined in your
 *  system...
 */
#define SO_REUSEPORT 15
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "logging.h"

/* Default Minecraft server port... */
#define PORT 25565

/* All strings are to be 4KiB... */
#define BUFFER_SIZE 4096

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *response = "Hello from server!";

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        sendf(LOG_ERROR, "Setting up sockets failed...\n");
        return -1;
    }

    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        sendf(LOG_ERROR, "The function `setsockopt` failed...\n");
        return -1;
    }

    // Bind socket to port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        sendf(LOG_ERROR, "Listening to port %s failed...\n", PORT);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        sendf(LOG_ERROR, "Listening to port %s failed...\n", PORT);
        exit(EXIT_FAILURE);
    }

    // Accept incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        sendf(LOG_ERROR, "Accepting incoming connection failed...\n");
        exit(EXIT_FAILURE);
    }

    // Read data from client
    valread = read(new_socket, buffer, BUFFER_SIZE);
    sendf(LOG_INFO, "Received message: %s\n", buffer);

    // Send response to client
    send(new_socket, response, strlen(response), 0);
    sendf(LOG_INFO, "Response sent\n");

    // Close socket
    close(new_socket);
    close(server_fd);

    return 0;
}