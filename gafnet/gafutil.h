#pragma once
#ifndef _GAF_UTIL_H
#define _GAF_UTIL_H

void gafnet_debug(char* msg) {
	if (GAFNET_DEBUG) {
		printf("gafnet:debug: %s\n", msg);
	}
}

#endif