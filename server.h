#include <stdio.h>
#include <string.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <pthread.h> 
#include "packet.h"

#ifndef __SERVER_H__
#define __SERVER_H__

struct send_torrent_msg_t
{
	char * torrent_path;
	connection_info_t client;
};

class server_c
{
public:
	server_c();
	server_c(char * torrent_list_path);
	~server_c();
	void send_torrent_func(void * msg); // new thread
	char * get_torrent_path(string torrent_sha1sum);
	void update_torrent_list(string torrent_sha1sum, char * torrent_path);
	void listen(int port);
private:
	char * folder = "/torrents/";
	char * torrent_list_path;
	std::map<string torrent_sha1sum, char * torrent_path> torrent_list;
	void write_torrent_file(packet_c torrent_packet);
};

#endif