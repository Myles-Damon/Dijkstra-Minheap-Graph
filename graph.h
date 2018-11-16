//graph.h

// 

#ifndef _GRAPH_G_INCLUDED
#define _GRAPH_G_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

struct GRAPH{
	int V;
	int E;
	ELEMENT* heap; //pointer of type ELEMENT; NOT a HEAP struct!
	LIST** adj_list;
};

struct LIST
{
	int weight;
	int neighbor;
	LIST* next;
};