#include "gafnode.h"

struct gafnode* init_gafnode(int listen_port) {
	gafnode* node = malloc(sizeof(gafnode));
	bzero(node, sizeof(gafnode)); // you never know!
	int _port = GAFNET_DEFAULT_LISTEN;
	if (listen_port != 0) {
		_port = listen_port;
	}
	node->_listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (node->_listen_sock == 0) {
		
	}
}