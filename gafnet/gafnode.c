#include "gafnode.h"
#include "gafutil.h"

struct gafnode_client* gafnode_init_client(char* host, int listen_port) {
	// free all of these when destroying the node
	struct gafnode_client* node = malloc(sizeof(struct gafnode_client));
	node->hostname_len = strlen(host);
	node->hostname = malloc(node->hostname_len);
	strncpy(node->hostname, host, node->hostname_len);

	bzero(node, sizeof(struct gafnode_client)); // you never know!
	int _port = GAFNET_DEFAULT_LISTEN; // 6162
	int opt = 1;
	if (listen_port != 0) {
		_port = listen_port;
	}
	node->_listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (node->_listen_sock == 0) {
		gafnet_debug("failed to create init_gafnode_client socket!");
		return (struct gafnode_client*)NULL;
	}
	int opt_set_ret = setsockopt(node->_listen_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));
	if (opt_set_ret > 0) {
		gafnet_debug("failed to set socket option in init_gafnode_client");
		return (struct gafnode_client*)NULL;
	}
	node->_listen_addr.sin_family = AF_INET;
	node->_listen_addr.sin_addr.s_addr = INADDR_ANY;
	node->_listen_addr.sin_port = htons(_port);
	if (bind(node->_listen_sock, (struct sockaddr*)&node->_listen_addr, sizeof(node->_listen_addr)) < 0) {
		gafnet_debug("failed to bind in init_gafnode_client");
		return (struct gafnode_client*)NULL;
	}
	return node;
}

void gafnode_destroy_client(struct gafnode_client* c) {
	free(c->hostname);
	free(c);
}