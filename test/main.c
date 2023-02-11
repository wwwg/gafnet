#include <gafnode.h>

int main(int argc, char* argv[]) {
	gafnode_client* g = gafnode_init_client("testnode", 8080);
	if (g == 0) {
		printf("failed to mk gafnode\n");
		return 1;
	}
	return 0;
}