/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astein <astein@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:31:12 by astein            #+#    #+#             */
/*   Updated: 2024/05/01 18:31:39 by astein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/socket.h>		// This header file contains definitions of structures needed for sockets.
#include <netinet/in.h>		// Contains constants and structures needed for internet domain addresses.
#include <unistd.h>			// Provides access to the POSIX operating system API, including system calls like read and write.
#include <string.h>
#include <stdio.h>  		// For perror()
#include <stdlib.h> 		// For exit()
#include <fcntl.h> 			// For fcntl()
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/select.h>

void	startServerButBlockingMode()
{
// Create a Socket
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	// AF_INET: 	Specifies that the network protocol being used is IPv4.
	// SOCK_STREAM:	Indicates that the socket is of type stream, which supports the TCP protocol where data is read in a continuous stream.
	// 0:			Protocol value for IP in this case it is TCP.
	if (server_fd == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Define the Server Address
	struct sockaddr_in address;
	int port = 8181;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
	// AF_INET:		sin_family: Sets the family of the address, which is AF_INET for IPv4.
	// INADDR_ANY:	sin_addr.s_addr: Sets the IP address for the socket. INADDR_ANY binds the socket to all available interfaces.
	// htons:		sin_port: Sets the port for the socket. The htons function converts the port number from host byte order to a port number in network byte order.	

	// Allow Reuse of the Address
	int opt = 1;
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	// Bind the Socket to the Address
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
	{
    	perror("bind failed");
    	exit(EXIT_FAILURE);
	}
	// bind(): Binds the socket to the specified address and port. This step is necessary to specify where exactly your server should listen for incoming connections.
	// Checks if bind() returns less than 0 which would indicate an error.
	

	
	// Listen for Connections
	// listen(): Prepares the socket to accept incoming connections. The second argument (3) specifies the maximum length of the queue of pending connections.	
	if (listen(server_fd, 3) < 0)
	{
    	perror("listen");
    	exit(EXIT_FAILURE);
	}

	// Accept Connections
	int addrlen = sizeof(address);
	int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
	if (new_socket < 0)
	{
    	perror("accept");
    	exit(EXIT_FAILURE);
	}
	// accept(): Blocks the server until a client connects to the server.
	// It returns a new file descriptor specifically for this connection.
	// This new descriptor is used for sending and receiving data through this connection.



	// Read the Message from the Client and Print it
	char buffer[512] = {0};
	int bytes_read = read(new_socket, buffer, 512);
	(void)bytes_read;
	std::cout << "Message from client: " << buffer << std::endl;

	// Send a Message to the Client
	const char *hello = "Hello from server";
	send(new_socket, hello, strlen(hello), 0);
	std::cout << "Hello message sent" << std::endl;

	// Close the Socket
	close(new_socket);
	close(server_fd);

	
}

void 	startServerLoopNotBlocking()
{
    int server_fd, new_socket, client_socket[30], max_clients = 30, activity, i, valread, sd;
    int max_sd;
    struct sockaddr_in address;
    char buffer[1025];  //data buffer of 1K

    //set of socket descriptors
    fd_set readfds;

    //a message
    const char *message = "ECHO Daemon v1.0 \r\n";

    //initialise all client_socket[] to 0 so not checked
    for (i = 0; i < max_clients; i++) {
        client_socket[i] = 0;
    }

    // Create a master socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set master socket to allow multiple connections,
    // this is just a good habit, it will work without this
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // Type of socket created
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8181);

    // Bind the socket to localhost port 8181
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Listener on port 8181 \n");

    // Try to specify maximum of 3 pending connections for the master socket
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // Accept the incoming connection
    int addrlen = sizeof(address);
    puts("Waiting for connections ...");

    while (true) {
        // Clear the socket set
        FD_ZERO(&readfds);

        // Add master socket to set
        FD_SET(server_fd, &readfds);
        max_sd = server_fd;

        // Add child sockets to set
        for (i = 0; i < max_clients; i++) {
            // Socket descriptor
            sd = client_socket[i];

            // If valid socket descriptor then add to read list
            if (sd > 0) {
                FD_SET(sd, &readfds);
            }

            // Highest file descriptor number, need it for the select function
            if (sd > max_sd) {
                max_sd = sd;
            }
        }

        // Wait for an activity on one of the sockets, timeout is NULL,
        // so wait indefinitely
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR)) {
            printf("select error");
        }

        // If something happened on the master socket,
        // then its an incoming connection
        if (FD_ISSET(server_fd, &readfds)) {
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            // Inform user of socket number - used in send and receive commands
            printf("New connection, socket fd is %d, ip is : %s, port : %d\n", new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

            // Send new connection greeting message
			if (send(new_socket, message, strlen(message), 0) != static_cast<ssize_t>(strlen(message))) 
    			perror("send failed");


            puts("Welcome message sent successfully");

            // Add new socket to array of sockets
            for (i = 0; i < max_clients; i++) {
                // If position is empty
                if (client_socket[i] == 0) {
                    client_socket[i] = new_socket;
                    printf("Adding to list of sockets as %d\n", i);
                    break;
                }
            }
        }

        // Else its some IO operation on some other socket
        for (i = 0; i < max_clients; i++) {
            sd = client_socket[i];

            if (FD_ISSET(sd, &readfds)) {
                // Check if it was for closing, and also read the
                // incoming message
                if ((valread = read(sd, buffer, 1024)) == 0) {
                    // Somebody disconnected, get his details and print
                    getpeername(sd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
                    printf("Host disconnected, ip %s, port %d \n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

                    // Close the socket and mark as 0 in list for reuse
                    close(sd);
                    client_socket[i] = 0;
                }

                // Echo back the message that came in
                else {
					printf("Message from client: %s\n", buffer);
                    buffer[valread] = '\0';
                    send(sd, buffer, strlen(buffer), 0);
                }
            }
        }
    }
}

int	main()
{
	// startServerButBlockingMode();
	startServerLoopNotBlocking();
	return 0 ;
}

