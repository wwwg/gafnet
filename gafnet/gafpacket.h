#pragma once
#ifndef _GAF_PACKET_H
#define _GAF_PACKET_H

#include <string.h>

struct gaf_packet {
	char* data;
	size_t len;
}

#endif