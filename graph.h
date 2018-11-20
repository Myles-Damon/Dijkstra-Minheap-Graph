//graph.h

// 

#ifndef _GRAPH_G_INCLUDED
#define _GRAPH_G_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

//#include "heap.h"

struct ELEMENT{
	int node;
	int key;
	int pi;
	
	ELEMENT(int n);
	ELEMENT(int n, int d, int p);

};

struct LIST
{
	// These represent edges
	int weight;
	int neighbor;
	LIST* next;
	
	LIST(int weightIn, int neighborIn);
	LIST(int weightIn, int neighborIn, LIST* nextIn);
};

struct ADJ_LIST{
	LIST* head;
	ADJ_LIST(LIST* head);
};

struct GRAPH{
	int V; // # of vertices
	int E; // # of edges
	int numberOfNodes; // Graph heap size
	int SNS; // sorted_node_size (size of sortedNodes)
	int* nodePositions; // needed in order to keep track of where all those nodes are after I start heapifying shit
	ELEMENT* heapOfNodes; //pointer of type ELEMENT; NOT a HEAP struct!
	//ELEMENT* sortedNodes; // "S" in the Dijkstra algorithm
	LIST** adj_list; // depreciated
	
	GRAPH(int v, int e);
};

void Print_Graph(GRAPH* g);

void Build_Graph(GRAPH* graph,/* int s, int m, */int flag);

GRAPH* Initialize_Graph(int vertices, int edges);

#endif