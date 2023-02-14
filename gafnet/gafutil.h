#pragma once

#ifndef _GAF_UTIL_H
#define _GAF_UTIL_H

#ifndef _GAF_PACKET_H
#include "packet.h"
#endif

struct gaf_packet;

void gafnet_debug(char*);
/*
typedef void (*gafnet_callback_default)(void);
typedef void (*gafnet_callback_onmessage)(struct gaf_packet*);

//struct gafnode;
//typedef struct gafnode gafnode;
*/
// /typedef void (*gafnet_callback_onnewpeer)(struct gafnode*);
/*
typedef enum {
	GAFNET_INCOMING = 1,
	GAFNET_OUTGOING = 2
} gafnet_conn_type;
*/
#endif