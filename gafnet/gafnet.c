
#include "packet.h"
#include "gafnode.h"

gaf_packet gafnet_construct_packet(char* node_id, char* target_str, char* data, unsigned int data_len) {
	gaf_packet packet;

	packet.host_source_len = strlen(node_id);
	packet.host_source = malloc(packet.host_source_len);
	strcpy(packet.host_source, node_id);

	// a node id
	packet.target_out_len = strlen(target_str);
	packet.target_out = (char*)malloc(packet.target_out_len);
	memcpy(packet.target_out, target_str, packet.target_out_len);

	// raw data for packet
	packet.data_len = data_len;
	packet.data = (char*)malloc(packet.data_len);
	memcpy(packet.data, data, data_len);

	// abstract representation of packet created
	return packet;
}
void gafnet_destroy_packet(gaf_packet* p) {
	free(p->host_source);
	free(p->target_out);
	free(p->data);
}