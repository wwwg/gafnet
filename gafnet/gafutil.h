#pragma once

#ifndef _GAF_UTIL_H
#define _GAF_UTIL_H

#ifndef _GAF_PACKET_H
struct gafpacket;
typedef struct gafpacket gafpacket;
#endif

void gafnet_debug(char*);

typedef void (*gafnet_callback_default)(void);
typedef void (*gafnet_callback_onmessage)(gafpacket*);

#ifndef _GAF_NODE_H
struct gafnode;
typedef struct gafnode gafnode;
#endif

typedef void (*gafnet_callback_onnewpeer)(struct gafnode*);

typedef enum {
	GAFNET_INCOMING = 1,
	GAFNET_OUTGOING = 2
} gafnet_conn_type;

#endif