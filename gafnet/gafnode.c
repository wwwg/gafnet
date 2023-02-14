#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <string.h>

#include "gafnode.h"
#include "gafpacket.h"

// gafnode abstract peer struct

gafnode* gafnode_create_peer_from(gafnode_client*, client, char* ip, int port) {
	// create the node
	gafnode* node = malloc(sizeof(gafnode));
	bzero(node, sizeof(gafnode));
	// 
	size_t _dest_addr_len = strlen(ip);
	node->_dest_addr = malloc(_dest_addr_len);
	strncpy(node->_dest_addr, ip, _dest_addr_len);

	node->_dest_port = port;

	node->_peer_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (node->_peer_socket < 0) {
		//socket mk error
		gafnet_debug("failed to create socket in create_peer_from");
		gafnode_destroy(node);
		return (gafnode*)NULL;
	}

	// server address
	node->_dest_addr_s.sin_family = AF_INET;
	node->_dest_addr_s.sin_port = htons(port);
	// validate it
	if (inet_pton(AF_INET, node->_dest_addr, &node->_dest_addr_s.sin_addr) <= 0) {
		gafnet_debug("invalid address in create_peer_from");
		gafnode_destroy(node);
		return (gafnode*)NULL;
	}
	return node;
}
void gafnode_destroy(gafnode* node) {
	free(node->_dest_addr);
	free(node);
}

// gafnode client

int gafnode_connect_to(gafnode_client client, gafnode* node) {
	if (node->_peer_fd = connect(node->_peer_socket, (struct sockaddr*)&node->_dest_addr_s, sizeof(node->_dest_addr_s)) < 0) {
		// connection failed
		gafnet_debug("gafnode could not connect in gafnode_connect_to");
		return 1;
	}
	if ()
	return 0;
}

gafnode_client* gafnode_init_client(char* host, int listen_port) {
	// free all of these when destroying the node
	gafnode_client* node = malloc(sizeof(gafnode_client));
	bzero(node, sizeof(gafnode_client)); // you never know!

	node->node_id_len = strlen(host);
	node->node_id = malloc(node->node_id_len);
	strncpy(node->node_id, host, node->node_id_len);
	for (int i = 0; i < GAFNET_MAX_PEERS; i += 1) {
		node->_client_peers[i] = (void*)0;
	}

	int _port = GAFNET_DEFAULT_LISTEN; // 6162
	int opt = 1;
	if (listen_port != 0) {
		_port = listen_port;
	}
	node->_listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (node->_listen_sock == 0) {
		gafnet_debug("failed to create init_gafnode_client socket!");
		return (gafnode_client*)NULL;
	}
	int opt_set_ret = setsockopt(node->_listen_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));
	if (opt_set_ret > 0) {
		gafnet_debug("failed to set socket option in init_gafnode_client");
		return (gafnode_client*)NULL;
	}
	node->_listen_addr.sin_family = AF_INET;
	node->_listen_addr.sin_addr.s_addr = INADDR_ANY;
	node->_listen_addr.sin_port = htons(_port);
	if (bind(node->_listen_sock, (const struct sockaddr*)&node->_listen_addr, sizeof(node->_listen_addr)) < 0) {
		gafnet_debug("failed to bind in init_gafnode_client");
		return (gafnode_client*)NULL;
	}
	return node;
}
void gafnode_start_listen(gafnode_client* c) {
	if (listen(c->_listen_sock, GAFNET_MAX_PEERS) < 0) {
		// listen fail
		gafnet_debug("failed to listen in gafnode listen");
		if (c->on_listen_end != 0) {
			c->on_listen_end();
		}
	}
	if (c->on_listen_start != 0) {
		c->on_listen_start();
	}
	// from here on out listen for connections?
	while (1) {
		//
	}
}

void gafnode_destroy_client(gafnode_client* c) {
	free(c->node_id);
	free(c);
}