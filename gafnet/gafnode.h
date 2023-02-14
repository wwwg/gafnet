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
	//public

	char* node_id;
	size_t node_id_len;

	struct gafnode* peers;
	size_t total_peers;

	gafnet_conn_type conn_type;

	//private
	char* _dest_addr;
	int _dest_port;
	struct sockaddr_in _dest_addr_s;
	int _peer_socket;
	int _peer_fd;
} gafnode;

gafnode* gafnode_create_peer_from(char*, int);
void gafnode_destroy(gafnode*);

/*
	gafnode_client : network implementation of a gaf node
	avalible callbacks:
	on_listen_start
	on_listen_end
	on_client_open
	on_client_close
	on_incoming_message(gafpacket packet)
	on_outgoing_message(gafpacket packet)
	on_new_peer(gafnode* node)
*/

typedef struct {
	//public
	int listen_port;
	size_t peers_count;

	char* node_id;
	size_t node_id_len;

	//callbacks
	gafnet_callback_default on_listen_start;
	gafnet_callback_default on_listen_end;
	gafnet_callback_onnewpeer on_new_peer;

	//private
	gafnode* _client_peers[GAFNET_MAX_PEERS];
	gafnode* _server_peers[GAFNET_MAX_PEERS];
	int _outgoing_conns;
	int _incoming_conns;

	int _listen_sock;
	struct sockaddr_in _listen_addr;
} gafnode_client;

gafnode_client* gafnode_init_client(char*, int);
void gafnode_destroy_client(gafnode_client*);
void gafnode_start_listen(gafnode_client*);
int gafnode_connect_to(gafnode*);


#endif