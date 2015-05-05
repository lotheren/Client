#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "socket_name.h"

int main()
{
    int client_sockfd;
    int len;
    struct sockaddr_un address;
    int result;
    char ch = 'A';

    // Create a socket for the client.
    client_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

    // Name the socket.
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, SOCKET_NAME);
    len = sizeof(address);

    // Connect our socket to the server's socket.
    result = connect(client_sockfd, (struct sockaddr *)&address, len);
    if (result == -1) {
        perror("Error: client1");
        exit(1);
    }

    //  Write 'A' to the socket via sockfd.
    printf("Writing '%c' to the socket.\n", 'A');
    write(client_sockfd, &ch, 1);
    
    // Read what the server sent back.
    read(client_sockfd, &ch, 1);
    printf("Read '%c' from the server.\n", ch);
    
    close(client_sockfd);
    exit(0);
}