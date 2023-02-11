#pragma once
#ifndef _GAF_NODE_H
#define _GAF_NODE_H

#define GAFNET_MAX_PEERS 50
#define GAFNET_DEFAULT_LISTEN 6162

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <string.h>

#include "gafutil.h"

// gafnode : abstract representation of node on network
// struct gafnode;

typedef struct {
	int peer_socket;
	char* hostname;
	size_t hostname_len;
	struct gafnode* peers;
	size_t total_peers;
} gafnode;

/*
	gafnode_client : network implementation of a gaf node
	avalible callbacks:
	on_listen_start
	on_listen_end
	on_client_open
	on_client_close
	on_message(gafpacket packet)
*/

typedef struct {
	//public
	int listen_port;
	size_t peers_count;

	char* hostname;
	size_t hostname_len;

	//callbacks
	gafnet_callback_default on_listen_start;
	gafnet_callback_default on_listen_end;

	//private
	gafnode peers[GAFNET_MAX_PEERS];
	int _listen_sock;
	struct sockaddr_in _listen_addr;
} gafnode_client;

gafnode_client* gafnode_init_client(char*, int);
void gafnode_destroy_client(gafnode_client*);
void gafnode_start_listen(gafnode_client*);

#endif