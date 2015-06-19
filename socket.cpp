#include <stdio.h>
#include <string.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <pthread.h> 

#include "socket.h"

int socket_setup(skt_out * dataout , skt_in * datain)
{
    int i = 0, rc = 0;
    void *status;
    pthread_t threads;
    struct thread_data td;
	dataout->client_sock , c , read_size;
	struct sockaddr_in server , client;
	int port;

    if (argc < 2)
    {
    	printf("more arguments required!\n");
    	return 1;
    }

    port = atoi(argv[1]);

	    //Create socket
	    dataout->socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	    if (dataout->socket_desc == -1)
	    {
	        printf("Could not create socket");
	    }
	    puts("Socket created");
	     
	    //Prepare the sockaddr_in structure
	    server.sin_family = AF_INET;
	    server.sin_addr.s_addr = INADDR_ANY;
	    server.sin_port = htons( port );
	     
	    //Bind
	    if( bind(dataout->socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	    {
	        //print the error message
	        perror("bind failed. Error");
	        return 1;
	    }
	    puts("bind done");
	    td.thread_id = 0;

	while (1)
    {
	    //Listen
	    listen(dataout->socket_desc , 3);
	     
	    //Accept and incoming connection
	    puts("Waiting for incoming connections...");
	    c = sizeof(struct sockaddr_in);
	     
	    //accept connection from an incoming client
	    dataout->client_sock = accept(dataout->socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
	    if (dataout->client_sock < 0)
	    {
	        perror("accept failed");
	        return 1;
	    }
	    puts("Connection accepted");

		td.thread_id++;
	    td.dataout->client_sock = dataout->client_sock;
	    rc = pthread_create(&threads, NULL, server_thrd, (void *)&td);
    }

    return 0;
}

int server_thrd(void *threadarg)
{
    struct thread_data *my_data;
    int dataout->client_sock , read_size;
    char client_message[2000];
    char file[2000];

    my_data = (struct thread_data *) threadarg;
    dataout->client_sock = my_data->dataout->client_sock;

    memset(client_message, 0, 2000*sizeof(char));
	/*memset(file, 0, 2000*sizeof(char));
    if ((read_size = recv(dataout->client_sock , file , 2000 , 0)) > 0)
    {
    	write(dataout->client_sock , file , strlen(client_message));
    }*/
    //Receive a message from client
    while( (read_size = recv(dataout->client_sock , client_message , 2000 , 0)) > 0 )
    {
        //Send the message back to client
        //memset(client_message,0,2000*sizeof(char));
        write(dataout->client_sock , client_message , strlen(client_message));
        memset(client_message, 0, 2000*sizeof(char));
    }

    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
}
