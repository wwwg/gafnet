#pragma once
#ifndef _GAF_NODE_H
#define _GAF_NODE_H

#define GAFNET_MAX_PEERS 50

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include <string.h>

struct gafnode {
	int port;
	size_t peers_count;

	int _peers_sock[GAFNET_MAX_PEERS];
	int _listen_sock;
};

struct gafnode* init_gafnode(int);

#endif