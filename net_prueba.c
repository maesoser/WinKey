/*
    Bind socket to port 8888 on localhost
    compile with gcc [name].c -o [name] -lws2_32
*/
#include<io.h>
#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define TCP_SERVER_PORT 8888

#define ERROR_INIT_WINSOCK 1
#define ERROR_CREATE_SOCKET 2
#define ERROR_BIND_FAILED 3
#define ERROR_ACCEPT_FAILED 4

void write_error(int errorcode);

int main(int argc , char *argv[])
{
    WSADATA wsa;
    SOCKET s , new_socket;
    struct sockaddr_in server , client;
    int c;
    char *message;
  
    //printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        write_error(ERROR_INIT_WINSOCK);
        //printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }
      
    //printf("Initialised.\n");
      
    //Create a socket
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        //printf("Could not create socket : %d" , WSAGetLastError());
        write_error(ERROR_CREATE_SOCKET); 
    }
  
    //printf("Socket created.\n");
      
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( TCP_SERVER_PORT );
      
    //Bind
    if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
    {   
        write_error(ERROR_BIND_FAILED);
        //printf("Bind failed with error code : %d" , WSAGetLastError());
    }
      
    //puts("Bind done");
  
    //Listen to incoming connections
    listen(s , 3);
      
    //Accept and incoming connection
    //puts("Waiting for incoming connections...");
      
    c = sizeof(struct sockaddr_in);
    new_socket = accept(s , (struct sockaddr *)&client, &c);
    if (new_socket == INVALID_SOCKET)
    {
        write_error(ERROR_ACCEPT_FAILED);
        //printf("accept failed with error code : %d" , WSAGetLastError());
    }
      
    //puts("Connection accepted");
  
    //Reply to client
    message = "KL_CLIENT\n";
    send(new_socket , message , strlen(message) , 0);
      
    getchar();
  
    closesocket(s);
    WSACleanup();
      
    return 0;
}

void write_error(int errorcode){
    FILE *file;
        file=fopen("keylog","a+");
        fprintf(file,"\n ---------- ");
        switch(errorcode){
            case ERROR_INIT_WINSOCK:
            fprintf(file,"Failed. Error Code : ");
            break;
            case ERROR_CREATE_SOCKET:
            fprintf(file,"Could not create socket : ");
            break;
            case ERROR_BIND_FAILED:
            fprintf(file,"Bind failed with error code : ");
            break;
            case ERROR_ACCEPT_FAILED:
            fprintf(file,"accept failed with error code : ");
            break;
        }
        //fprintf(file,WSAGetLastError());
        fprintf(file," ----------\n");
        fclose(file);
}