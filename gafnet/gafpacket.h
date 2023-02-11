#pragma once
#ifndef _GAF_PACKET_H
#define _GAF_PACKET_H

#include <string.h>

struct gafnode;

typedef struct {
	char* data;
	size_t len;
} gaf_packet_simple;

typedef struct {
	gaf_packet_simple _packet;
	unsigned int hops;
	gafnode* src;
	gafnode* dest;
} gaf_packet;

#endif