#include <gafnode.h>
#include <pthread.h>
#include <unistd.h>

#define NODES 3

gafnode_client* g;

void thread_run(void* arg) {
	int id = (int)arg;
	printf("i am thread #%d\n", id);
}

void origin_onlisten() {
	printf("gafnode start listen\n");
}
void origin_endlisten() {
	printf("gafnode end listen\n");
}

int main(int argc, char* argv[]) {
	pthread_t threads[NODES];
	for (int i = 0; i < NODES; ++i) {
		pthread_create(threads + i, NULL, &thread_run, (void*)i);
	}
	for (int i = 0; i < NODES; ++i) {
		pthread_t t = threads[i];
		pthread_detach(t);
	}
	g = gafnode_init_client("origin", 8080);
	if (g == 0) {
		printf("failed to mk gafnode\n");
		return 1;
	}
	g->on_listen_start = origin_onlisten;
	g->on_listen_end = origin_endlisten;

	gafnode_start_listen(g);

	return 0;
}