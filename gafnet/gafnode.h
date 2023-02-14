#pragma once
#ifndef _GAF_NODE_H
#define _GAF_NODE_H

#define GAFNET_MAX_PEERS 50
#define GAFNET_DEFAULT_LISTEN 6162
#define GAFNET_NAME_MAX_LENGTH 20

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <string.h>

#include "gafutil.h"


typedef void (*gafnet_callback_default)(void);
typedef void (*gafnet_callback_onmessage)(struct gaf_packet*);
typedef void (*gafnet_callback_onnewpeer)(struct gafnode*);

typedef enum {
	GAFNET_INCOMING = 1,
	GAFNET_OUTGOING = 2
} gafnet_conn_type;

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

gafnode* _gafnode_init_peer_from(char*, int);
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

	// OUTGOING
	gafnode* client_peers[GAFNET_MAX_PEERS];
	int active_client_peers_count;

	// INCOMING
	gafnode* server_peers[GAFNET_MAX_PEERS];
	int active_server_peers_count;

	// private

	int _listen_sock;
	struct sockaddr_in _listen_addr;
	int _listen_addr_len;
} gafnode_client;

gafnode_client* gafnode_init_client(char*, int);
void _gafnode_client_add_peer(gafnode_client* c, gafnode* node);
void gafnode_destroy_client(gafnode_client*);
void gafnode_start_listen(gafnode_client*);
gafnode* gafnode_connect(gafnode*);
gafnode* create_gafnode_client_peer(gafnode_client* c, char* ip, int port);
gafnode* _gafnode_create_server_client_peer(int);


#endif