#pragma once
#ifndef _GAF_PACKET_H
#define _GAF_PACKET_H

#include <string.h>

typedef struct {
	char* data;
	size_t len;
} gaf_packet_simple;

typedef struct {
	gaf_packet_simple _packet;
	
} gaf_packet;

#endif