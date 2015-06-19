#include <stdio.h>
#include <string.h>    //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write
#include <pthread.h> 
#include <stdlib>
#include "file_manage.h"
#ifndef __TRACKER_H__
#define __TRACKER_H__

class tracker_c
{
public:
	tracker_c();
	tracker_c(char * peer_list_path);
	~tracker_c();
	list<connection_info_t> get_peer_list(string sha1sum);
	void update_peer_list(string torrent_sha1sum, connection_info_t new_host);
private:
	char * peer_list_path;
	std::map<string, list<connection_info_t>> peer_list_in_mem;
	list<connection_info_t> broadcast_updated_peer_list(string torrent_sha1sum);
};

#endif