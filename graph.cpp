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

		std::cout << "Vertices: " << g->V << " Edges: " << g->E << "\n" << std::endl;
		
		///////////////////////////////////////////////////////////
		// NOT DONE! Need to format output to match requirements //
		///////////////////////////////////////////////////////////
		
		// Actually, it's pretty much done
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
		/* DEBUGGING
		for (int i = 0; i < g->V; i++)
		{
			std::cout << "node: " << g->heapOfNodes[i].node << " \nweight: " << g->heapOfNodes[i].key << std::endl;
			std::cout << "position: " << g->nodePositions[g->heapOfNodes[i].node - 1] << std::endl;
		}*/
	}
	return;
}

void Build_Graph(GRAPH* g, int flag) // basically heapify
{
	
	for(int i = 0; i < g->V; i++)
	{
		g->nodePositions[g->heapOfNodes[i].node - 1] = i;
	}
	
	if (flag == 2)
	{
		for (int i = g->V/2; i > -1; i--)
		{
			Min_Heapify(g, i, g->numberOfNodes);
			//DEBUGGINGPrint_Graph(g);
		}		
	}
	
	else 
	{
		for (int i = g->V/2; i > -1; i--)
		{
			Min_Heapify(g, i, g->numberOfNodes);
		}
	}

	/*DEBUGGINGif (flag == 1)
	{
		Print_Graph(g);
	}*/
	
	return;
}

void Dijkstra(GRAPH* g)
{
	// "remove" all of the nodes from the graph and adjust their neighbor's weights
	for (int i = 0; i < g->V; i++)
	{
		findShortestEdge(g, g->heapOfNodes[0].node);
		Delete_Min(g, 1);		
		Build_Graph(g, 1); // heapify		
	}
}

void Initialize_Single_Source(GRAPH* g, int source)
{
	/* DESCRIPTION COMMENT
	
	
	
	*/
	
	// Explicitly set (g->numberOfNodes = g->V) so that when the graph
	// needs to trace another path it can do so without messing up heapify (Build_Graph)
	
	g->numberOfNodes = g->V;
	
	// initialize all nodes (ELEMENTs) to un-relaxed state
	for (int i = 0; i < g->V; i++)
	{
		g->heapOfNodes[i] = ELEMENT(i + 1, INF, NULL);
	}
	for(int i = 0; i < g->V; i++)
	{
		g->nodePositions[g->heapOfNodes[i].node - 1] = i;
	}
	// distance from source to source = 0; source is already u - 1 so I don't need to put "source - 1" in nodePositions[]
	g->heapOfNodes[g->nodePositions[source]].key = 0;	
	/* DEBUGGING
	for(int i = 0; i < g->V; i++)
	{
		std::cout << "node: " << g->heapOfNodes[i].node << " key: " << g->heapOfNodes[i].key << std::endl;
	}
	*/
	
	Build_Graph(g, 0);
	for(int i = 0; i < g->V; i++)
	{
		g->nodePositions[g->heapOfNodes[i].node - 1] = i;
	}
}

GRAPH* Initialize_Graph(int vertices, int edges)
{
	GRAPH* g = new GRAPH(vertices, edges);
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
	/* DESCRIPTION COMMENT
	
	This kinda ended up just being both "find shortest edge" AND "relax"
	I'm gonna leave it this way because I'm running low on time to polish 
	this program before I submit it, but I do know how Dijkstra's works 
	w/ respect to relaxing edges	
	
	*/
	//DEBUGGINGstd::cout << "finding shortest edge from " << g->heapOfNodes[0].node << std::endl;
	LIST* edgeTraversal = g->adj_list[u - 1];
	
	while(edgeTraversal != nullptr)
	{
		for(int i = 0; i < g->V; i++)
		{
			g->nodePositions[g->heapOfNodes[i].node - 1] = i;
		}
		//DEBUGGINGstd::cout << "edge from: " << g->heapOfNodes[0].node << " to: " << g->heapOfNodes[g->nodePositions[edgeTraversal->neighbor - 1]].node << " with weight: " << edgeTraversal->weight << "   " << std::endl;
		if (edgeTraversal->weight + g->heapOfNodes[0].key < g->heapOfNodes[g->nodePositions[edgeTraversal->neighbor - 1]].key)
		{
			g->heapOfNodes[g->nodePositions[edgeTraversal->neighbor - 1]].key = g->heapOfNodes[0].key + edgeTraversal->weight;
			g->heapOfNodes[g->nodePositions[edgeTraversal->neighbor - 1]].pi = u - 1;
		}
		edgeTraversal = edgeTraversal->next;
	}
	
	for(int i = 0; i < g->V; i++)
	{
		g->nodePositions[g->heapOfNodes[i].node - 1] = i;
	}
	
	//std::cout << "did" << std::endl;
	//DEBUGGINGPrint_Graph(g);
	
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



































