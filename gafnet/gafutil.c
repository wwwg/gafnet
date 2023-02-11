#include "gafutil.h"
#include <stdio.h>

void gafnet_debug(char* msg) {
	if (GAFNET_DEBUG) {
		printf("gafnet:debug: %s\n", msg);
	}
}