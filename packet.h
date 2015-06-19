#include <stdio.h>
#include <string.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <pthread.h> 

#ifndef __PACKET__
#define __PACKET__

class packet_c
{
public:
	packet_c();
	~packet_c();
	set_type(const char type);
	put_obj(const void * obj);
	make_packet(char * packet_str);
	parse_packet(const char * packet_str);
	char * get_type(void);
	void * get_obj(void);
private:
	char pkt_type;
	int pkt_length;
	char *data;
};

#endif