#pragma once
#ifndef _GAF_NODE_H
#define _GAF_NODE_H

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket>

struct gafnode {
	int port;
};

struct gafnode* init_gafnode(int);

#endif