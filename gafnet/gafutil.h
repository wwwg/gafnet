#pragma once

#ifndef _GAF_UTIL_H
#define _GAF_UTIL_H

#include "gafpacket.h"

void gafnet_debug(char*);

typedef void (*gafnet_callback_default)(void);
typedef void (*gafnet_callback_onmessage)(gafpacket);

#endif