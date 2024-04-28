#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


int main (){

    

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    listen(server_socket, 1); // THE SECOND ARGUMENT TAKES HOW MANY CLIENTS ARE THERE

    

    

    int client_socket = accept(server_socket, NULL, NULL);

    if (client_socket == -1) {  // IF LOOP TO LET THE USER KNOW IF THE FUNCTION IS WORKING
        printf("the connection failed!\n");
    }
    else
    {
        printf("--------connecction established--------\n");
    }
    
    while (1) { // WHILE LOOP TO RECIEVE AND SEND
    char message_to_client[256]; 
    printf(">> ");
    fgets(message_to_client, sizeof(message_to_client), stdin);
    
    
    send(client_socket, message_to_client, sizeof(message_to_client), 0);

    char message_from_client[256]; // BUFFER TO STORE WHAT CLIENT SENT
    recv(client_socket, &message_from_client, sizeof(message_from_client), 0); //STORES THE RECIEVED MESSAGE IN THE BUFFER
    printf("\033[0;31m"); //SET THE TEXT TO RED
    printf("<< %s\n", message_from_client);
    printf("\033[0m"); //RESET THE COLOR
    }

    
    close(client_socket); //CLOSES THE CLIENTS SOCKET
    close(server_socket); //CLOSES THE SERVER SOCKET
    return 0; 
}
