#include <stdio.h>
#include <string.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <pthread.h> 

#ifndef __SOCKET_H__
#define __SOCKET_H__

int server_thrd(void *threadarg);

struct thread_data{
   int  thread_id;
   int  client_sock;
};

class socket_lis_c
{
public:
	socket_lis_c();
	~socket_lis_c();
	void set_port(int port_num);
	int socket_setup();	
	int (client_sock) listen_and_accept();
private:
	int port;
	int c, socket_desc;
	struct sockaddr_in client;
};

#endif

