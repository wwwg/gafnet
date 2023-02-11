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

#include "gafpacket.h"
#include "gafutil.h"

/*
	gafnode_client : network implementation of a gaf node
	avalible callbacks:
	on_listen_start
	on_listen_end
	on_client_open
	on_client_close
	on_message(gafpacket packet)
*/

struct gafnode_client {
	//public
	int listen_port;
	size_t peers_count;

	char* hostname;
	size_t hostname_len;

	//callbacks
	gafnet_callback_default on_listen_start;
	gafnet_callback_default on_listen_end;

	//private
	int _peers_sock[GAFNET_MAX_PEERS];
	int _listen_sock;
	struct sockaddr_in _listen_addr;
};

struct gafnode_client* gafnode_init_client(char*, int);
void gafnode_destroy_client(struct gafnode_client*);

void gafnode_set_on_listen_start(struct gafnode_client*, gafnet_callback_default);
void gafnode_set_on_listen_end(struct gafnode_client*, gafnet_callback_default);

// gafnode : abstract representation of node on network

struct gafnode {
	int peer_socket;
};

#endif