#include <stdio.h>
#include <stdlib.h>


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
int main () {

    int network_socket = socket(AF_INET, SOCK_STREAM, 0);

    
    //we have opened a port. Now we have to connect it to the other
    //side. To do that, we are going to use inet library with has some 
    //useful structures.

    struct sockaddr_in server_adress;
    server_adress.sin_family = AF_INET; // this is the family which is IPv4
    server_adress.sin_port = htons(9002); // this is an actual port, but we have to use 
                                          // htons to convert it to an appropritate data type.

    server_adress.sin_addr.s_addr = INADDR_ANY; //sin_addr is itself a structure.

    int connection_status = connect(network_socket, (struct sockaddr*)&server_adress, sizeof(server_adress)); 
    // the conncect function returns an integer. if 0 then we now our connection was successful.
    // we had to cass or server_adress struct to another struct and pass it as a pointer.


    if (connection_status == -1) {  //this function prints a message indicating if it failed or not.
        printf("the connection failed!\n");
    }
    else
    {
        printf("--------connecction established--------\n");
    }
    
    while (1){

    char server_response[256]; //creating a buffer for the response from the server.
    recv(network_socket, &server_response, sizeof(server_response), 0); //we recive a message back from the server
    printf("\033[0;34m"); //sets the color to blue
    printf("<< %s\n", server_response); // printing the message
    printf("\033[0m");// resets the color
    char message_to_server[256];
    printf(">> ");
    fgets(message_to_server, sizeof(message_to_server), stdin);
    //scanf("%s", &message_to_server);
    
    send(network_socket, message_to_server, sizeof(message_to_server), 0); 
    }


    close(network_socket);
    return 0;
}
