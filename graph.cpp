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

#pragma GCC diagnostic ignored "-Wpointer-arith"
#pragma GCC diagnostic ignored "-Wconversion-null"

ELEMENT::ELEMENT(int n) : key(n) {}
ELEMENT::ELEMENT(int n, int d, int p) : node(n), key(d), pi(p) {}

LIST::LIST(int weightIn, int neighborIn) : weight(weightIn), neighbor(neighborIn), next(nullptr) {}
LIST::LIST(int weightIn, int neighborIn, LIST* nextIn) : weight(weightIn), neighbor(neighborIn), next(nextIn) {} // Might need to have "next" be initialized to null and assigned afterwards

GRAPH::GRAPH(int v, int e) : V(v), E(e), numberOfNodes(v), SNS(0), nodePositions ((int*) malloc(sizeof(int) * V)), heapOfNodes ((ELEMENT*) malloc(sizeof(ELEMENT) * V)), sortedNodes ((ELEMENT*) malloc(sizeof(ELEMENT) * V)), adj_list ((LIST**) malloc(sizeof(LIST*) * V))  {}

ADJ_LIST::ADJ_LIST(LIST* headPtr) : head(headPtr) {}

void Print_Graph(GRAPH* g)
{

	if (g->V == 0 || g->V == NULL)
	{
		return;
	}
	else
	{
		for(int i = 0; i < g->V; i++)
		{
			g->nodePositions[g->heapOfNodes[i].node - 1] = i;
		}
		std::cout << "Vertices: " << g->V << " Edges: " << g->E << "\n" << std::endl;
		
		///////////////////////////////////////////////////////////
		// NOT DONE! Need to format output to match requirements //
		///////////////////////////////////////////////////////////
		for (int i = 0; i < g->V; i++)
		{
			std::cout << i + 1 << ": ";
			LIST* traversal = g->adj_list[i];
			while(traversal != nullptr)
			{
				std::cout << "(" << traversal->neighbor << "," << traversal->weight << "); ";
				traversal = traversal->next;
			}
			std::cout << std::endl;
		}
		
		for (int i = 0; i < g->V; i++)
		{
			std::cout << "node: " << g->heapOfNodes[i].node << " \nweight: " << g->heapOfNodes[i].key << std::endl;
			std::cout << "position: " << g->nodePositions[g->heapOfNodes[i].node] << std::endl;
		}
	}
	return;
}

void Build_Graph(GRAPH* g, int flag) // basically heapify
{
	for(int i = 0; i < g->V; i++)
	{
		g->nodePositions[g->heapOfNodes[i].node - 1] = i;
	}
	// "n" changed to "V"; Serves the same purpose (IE being the size of the array);
	if (flag == 2)
	{
		for (int i = g->V/2; i > -1; i--)
		{
			Min_Heapify(g, i, g->numberOfNodes);
			Print_Graph(g);
		}		
	}
	
	else 
	{
		for (int i = g->V/2; i > -1; i--)
		{
			Min_Heapify(g, i, g->numberOfNodes);
		}
	}

	if (flag == 1)
	{
		Print_Graph(g);
	}
	
	return;
}

void Dijkstra(GRAPH* g)
{
	// "remove" all of the nodes from the graph and adjust their neighbor's weights
	for (int i = 0; i < g->V; i++)
	{
		findShortestEdge(g, g->heapOfNodes[0].node);
		//Min_Heapify(g, 0, g->numberOfNodes);
		Delete_Min(g, 1);		
		Build_Graph(g, 1); // heapify		
	}
}

void Initialize_Single_Source(GRAPH* g, int source)
{
	// initialize all nodes (ELEMENTs) to un-relaxed state
	for (int i = 0; i < g->V; i++)
	{
		g->heapOfNodes[i] =ELEMENT(i + 1, INF, NULL);
	}
	g->heapOfNodes[source].key = 0; // distance from source to source = 0;
	Build_Graph(g, 0);
	for(int i = 0; i < g->V; i++)
	{
		g->nodePositions[g->heapOfNodes[i].node - 1] = i;
	}
}

GRAPH* Initialize_Graph(int vertices, int edges)
{
	GRAPH* g = new GRAPH(vertices, edges);
	//LIST* nullListPtr = nullptr
	/* need to separately initialize the edges I think*/
	// NOPE to the above comment; Do need to add the edges 
	// from the file separately though
	for (int i = 0; i < vertices; i++)
	{
		g->adj_list[i] = nullptr;
		g->nodePositions[i] = i;
	}
	return g;
}

void findShortestEdge(GRAPH* g, int u)
{
	
	std::cout << "finding shortest edge from " << g->heapOfNodes[0].node << std::endl;
	LIST* edgeTraversal = g->adj_list[u - 1];
	
	while(edgeTraversal != nullptr)
	{
		for(int i = 0; i < g->V; i++)
		{
			g->nodePositions[g->heapOfNodes[i].node - 1] = i;
		}
		std::cout << "edge from: " << g->heapOfNodes[0].node << " to: " << g->heapOfNodes[g->nodePositions[edgeTraversal->neighbor - 1]].node << " with weight: " << edgeTraversal->weight << "   " << std::endl;
		if (edgeTraversal->weight + g->heapOfNodes[0].key < g->heapOfNodes[g->nodePositions[edgeTraversal->neighbor - 1]].key)
		{
			//std::cout << g->heapOfNodes[g->nodePositions[edgeTraversal->neighbor - 1]].node << std::endl;
			g->heapOfNodes[g->nodePositions[edgeTraversal->neighbor - 1]].key = g->heapOfNodes[0].key + edgeTraversal->weight;
			g->heapOfNodes[g->nodePositions[edgeTraversal->neighbor - 1]].pi = u - 1;
			//std::cout << g->heapOfNodes[g->nodePositions[edgeTraversal->neighbor - 1]].key << std::endl;
		}
		edgeTraversal = edgeTraversal->next;
	}
	
	for(int i = 0; i < g->V; i++)
	{
		g->nodePositions[g->heapOfNodes[i].node - 1] = i;
	}
	
	//std::cout << "did" << std::endl;
	Print_Graph(g);
	
	return;
}

void Relax(GRAPH* g, int u, int v, int w)
{
	/*
	int fSEint = findShortestEdge(g,u);
	if (g->heapOfNodes[v].key > (g->heapOfNodes[u].key + fSEint))
	{
		// Update the distance variable ("key") for the node
		// && Update it's parent node variable
		g->heapOfNodes[v].key = g->heapOfNodes[u].key + fSEint;
		g->heapOfNodes[v].pi = u;
	}*/
}



































