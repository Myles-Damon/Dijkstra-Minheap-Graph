//graph.cpp

// should implement graph functions

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

#include "heap.h"
#include "graph.h"
#include "util.h"

#define INF 2147283647

LIST::LIST(int weightIn, int neighborIn) : weight(weightIn), neighbor(neighborIn), next(nullptr) {}
LIST::LIST(int weightIn, int neighborIn, LIST* nextIn) : weight(weightIn), neighbor(neighborIn), next(nextIn) {} // Might need to have "next" be initialized to null and assigned afterwards

GRAPH::GRAPH(int v, int e) : V(v), E(e), numberOfNodes(v), SNS(0), nodePositions ((int*) malloc(sizeof(int) * V)), sortedNodes ((ELEMENT*) malloc(sizeof(ELEMENT) * V)), heapOfNodes ((ELEMENT*) malloc(sizeof(ELEMENT) * V)), adj_list ((LIST**) malloc(sizeof(LIST*) * V)) {}

ADJ_LIST::ADJ_LIST(LIST* headPtr) : head(headPtr) {}

void Print_Graph(GRAPH* g)
{

	if (g->V == 0 || g->V == NULL)
	{
		return;
	}
	else
	{
		std::cout << "Vertices: " << g->V << " Edges: " << g->E << "\n" << std::endl;
		
		///////////////////////////////////////////////////////////
		// NOT DONE! Need to format output to match requirements //
		///////////////////////////////////////////////////////////
		/*for (int i = 0; i < g->V; i++)
		{
			std::cout << "u : " << i << ": " << g->H[i].key << std::endl;
		}*/
	}
	return;
}

void Build_Graph(GRAPH* graph, ELEMENT* Array, int s, int m, int flag)
{
	/* Removed since I won't be re-sizing the graph's array
	// N IS THE SIZE OF ARRAY Array[]
	if (graph->V < n)
	{
		std::cout << "Heap capacity is less than array size. Resizing heap" << std::endl;
		// gets the result of the floor function of log2(n) (floor function == casting float to int)
		// adds 1, and then uses that as the lowest exponent of 
		// 2 which will leave the heap with enough capacity to 
		// take in the new array items once the size of the 
		// heap is changed via realloc()
		
		int c = (int)std::log2(n) + 1;
		
		//graph->heapOfNodes = (ELEMENT*)realloc(heap->H, sizeof(ELEMENT) * (std::pow(2,c)));
		//heap->capacity = std::pow(2,c);
	}
	*/
	/* Unneeded since nodes are initialized with key = INF && the rest of their data is set up through relaxation
	std::cout << "Filling heap with elements from array" << std::endl;

	for (int i = 0; i < n; i++)
	{

		graph->heapOfNodes[i] = ELEMENT(Array[i].key);
		//heap->size++;

	}
	*/
	
	// "n" changed to "V"; Serves the same purpose (IE being the size of the array);
	if (flag == 2)
	{
		for (int i = g->V/2; i > -1; i--)
		{
			Min_Heapify(heap, i);
			Print_Heap(heap);
		}		
	}
	
	else 
	{
		for (int i = g->V/2; i > -1; i--)
		{

			Min_Heapify(heap, i);
		}
	}

	if (flag == 1)
	{
		Print_Heap(heap);
	}
	
	return;
}

void Initialize_Single_Source(GRAPH* g, int source)
{
	// initialize all nodes (ELEMENTs) to un-relaxed state
	for (int i = 0; i < g->V; i++)
	{
		g->heapOfNodes[i] = new ELEMENT(i + 1, INF, NULL);
	}
	heapOfNodes[source]->key = 0; // distance from source to source = 0;
}

GRAPH* Initialize_Graph(int vertices, int edges)
{
	GRAPH* g = new GRAPH(vertices, edges);
	//LIST* nullListPtr = nullptr
	/* need to separately initialize the edges I think*/
	for (int i = 0; i < vertices; i++)
	{
		g->adj_list[i] = nullptr;
	}
	
	return g;
}

int findShortestEdge(GRAPH* g, int u, int v)
{
	int shortestDistance = INF;
	LIST* edgeTraversal = g->adj_list[u];
	while(edgeTraversal != nullptr)
	{
		if (edgeTraversal->neighbor == v && edgeTraversal->weight < shortestDistance)
		{
			shortestDistance = edgeTraversal->weight;	
		}
		edgeTraversal = edgeTraversal->next;
	}
	return edgeTraversal;
}

void Relax(GRAPH* g, int u, int v, int w)
{
	int fSEint = findShortestEdge(g,u,v);
	if (g->heapOfNodes[v]->key > (g->heapOfNodes[u]->key + fSEint))
	{
		// Update the distance variable ("key") for the node
		// && Update it's parent node variable
		g->heapOfNodes[v]->key = g->heapOfNodes[u]->key + fSEint;
		g->heapOfNodes[v]->pi = u;
	}
}



































