#include <stdio.h>
#include <string.h>    //strlen
#include <sys/socket.h>
#include <unistd.h>    //write
#include <pthread.h> 
#include <sys/stat.h>    
#include <arpa/inet.h> //inet_addr

#ifndef __FILEMANAGE_H__
#define __FILEMANAGE_H__

unsigned long get_file_size(const string & path, const string & filename);

struct connection_info_t
{
	char * ip;
	int port_num;
};

struct peer_t
{
	bool isConnected;
	connection_info_t conInfo;
	char * pieces_status;
};

struct piece_t
{
	std::vector<string> hash;
	std::vector<unsigned long long> file_ptr;
};

class file_c
{
public:
	file_c();
	~file_c();
	file_c(char * file_path);
	unsigned long get_size(void);
	std::vector<? *> cut(void);
	void set_torrent_path(char * torrent_path);
	bool gen_torrent(char * torrent_path, connection_info_t tracker_info);
	void set_tracker(connection_info_t tracker_info);
	void upload_to_server(connection_info_t server_info);
	void update_peer_list_from_tracker(void);
	void download_from_peers(void);
private:
	char * file_path
	char * torrent_path;
	int pieces_num;
	string sha1sum_file;
	struct stat statbuff;
	std::vector<string> sha1sum_list;
	std::vector<peer_t> peer_list;
	std::vector<piece_t> piece_info_list;
	char * pieces_status;
	connection_info_t tracker_info;
	bool get_peer_list_from_tracker(void);
	void download_thread_func(void * peer_connection_info);
};

#endif
