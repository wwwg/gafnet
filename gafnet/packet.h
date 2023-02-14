#pragma once
#ifndef _GAF_PACKET_H
#define _GAF_PACKET_H

#include <string.h>

// typedef struct gafnode_client gafnode_client;
#include "gafnode.h"

#define GAFNET_TOKEN 9847
#define MAX_HOPS 2

typedef struct {
	char* data;
	size_t len;
} gaf_packet_simple;

// simple packet layout

typedef struct {
	gaf_packet_simple _packet;
	// the first 4 bytes are the token, making sure its gafnet
	unsigned int hops;

	unsigned int host_source_len;
	char* host_source;

	unsigned int target_out_len;
	char* target_out;

	unsigned int data_len;
	char* data;
} gaf_packet;

gaf_packet gafnet_construct_packet(char*, char* /* MUST BE A C STRING */, char*, unsigned int);
void gafnet_destroy_packet(gaf_packet*);

#endif