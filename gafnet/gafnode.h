#pragma once
#ifndef _GAF_NODE_H
#define _GAF_NODE_H

struct gafnode {
	int port;
};

struct gafnode* init_gafnode(int);

#endif