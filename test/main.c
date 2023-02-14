#include <gafnode.h>
#include <pthread.h>
#include <unistd.h>

#define NODES 3

#define ORIGIN_NODE_PORT 8080
#define ORIGIN_NODE_HOST "127.0.0.1"

gafnode_client* g;

void thread_run(void* arg) {
	int id = (int)arg;
	printf("i am thread #%d\n", id);

	// make client
	gafnode_client* client = gafnode_init_client("default", 8080 + id + 1);

	// rename it
	size_t id_size = sprintf(client->node_id, "gafnodetest_%d", id);
	client->node_id_len = id_size;

	//connect to server
	gafnode* origin_node = create_gafnode_client_peer(client, ORIGIN_NODE_HOST, ORIGIN_NODE_PORT);
	gafnode_connect(origin_node);

	
}

void origin_onlisten() {
	printf("the origin node is listening...\n");
}
void origin_endlisten() {
	printf("gafnode end listen\n");
}
void origin_on_new_peer(gafnode* new_peer) {
	printf("server detected a new peer!\n");
}

int main(int argc, char* argv[]) {
	pthread_t threads[NODES];
	g = gafnode_init_client("origin", ORIGIN_NODE_PORT);

	for (int i = 0; i < NODES; ++i) {
		pthread_create(threads + i, NULL, &thread_run, (void*)i);
	}
	for (int i = 0; i < NODES; ++i) {
		pthread_t t = threads[i];
		pthread_detach(t);
	}
	if (g == 0) {
		printf("failed to mk gafnode\n");
		return 1;
	}
	// set callbacks, easy
	g->on_listen_start = origin_onlisten;
	g->on_listen_end = origin_endlisten;
	g->on_new_peer = origin_on_new_peer;

	gafnode_start_listen(g);

	return 0;
}