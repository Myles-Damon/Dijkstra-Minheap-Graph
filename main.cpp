// main.cpp

#include <stdio.h>
#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <cmath>

#include "heap.h"
#include "util.h"
#include "graph.h"

#define INF 2147283647

#pragma GCC diagnostic ignored "-Wpointer-arith"
#pragma GCC diagnostic ignored "-Wconversion-null"

//Used at the end for freeing up memory in a nice, concise way
void deleteList(LIST* lpt)
	{
		if(lpt == nullptr)
		{
			return;
		}
		else
		{
			deleteList(lpt->next);
			free(lpt);
		}
	}
	
void pathRecur(ELEMENT nodeTrav, GRAPH* graph, int u, int v, int z)
{
	
	if (nodeTrav.node != u && z < 100)
	{
		z++;
		nodeTrav = graph->heapOfNodes[graph->nodePositions[nodeTrav.pi]];
		pathRecur(nodeTrav, graph, u, nodeTrav.node, z);
	}
	/*else
	{
		v = nodeTrav.node;
	}*/
	std::cout << v << ", ";
}

int main()
{

	printf("hello\n");	
	
	FILE* file = fopen("Ginput.txt", "r");	
	int u, v, w;
	char c = 'P';
	
	bool rBool = false;
	
	HEAP* heap = nullptr;
	GRAPH* graph = nullptr;
	
	while(c != 'S' && c != 's')
	{
		printf("\nInput a command: ");
		c = nextCommand(&u, &v, &w, heap, file);
		if (c == 'C' || c == 'c')
		{
			if (v < 0)
			{
				std::cout << "Please enter a positive integer when allocating heap space" << std::endl;
			}
			// Yeah, that's right. I even made sure to free up the previous heap if you
			// instantiate a new one.
			if(heap != nullptr)
			{
				free(heap->H);
				free(heap);
				
				heap = Initialize(v);
				std::cout << "COMMAND: " << c << " " << v << std::endl;
				std::cout << "Heap capacity: " << heap->capacity << std::endl;
			}
			else
			{
				heap = Initialize(v);
				std::cout << "COMMAND: " << c << " " << v << std::endl;
				std::cout << "Heap capacity: " << heap->capacity << std::endl;
			}
		}
		else if (c == 'R' || c == 'r')
		{
			if (!file)
			{
				printf("there was a problem opening the file");
			}
			/*else if(heap == nullptr)
			{
				std::cout << "Please initialize the heap first" << std::endl;
			}*/
			else
			{
				
				
				std::cout << "COMMAND: " << c <</* " " << f << */std::endl;
				//std::cout << "Heap capacity: " << heap->capacity << std::endl;
				/* Stuff for heap, not graph
				// get # of items in array & dynamically create array
				char buffer[10];
				fgets(buffer, 10, file);
				int length = atoi(buffer);
				ELEMENT* A = (ELEMENT*) malloc((length + 1) * sizeof(ELEMENT));
				*/ // END Stuff for heap, not graph
				// fill up array
				
				//char flag = w;
				// Read first line and get number of vertices and edges
				
				if (rBool == true)
				{
					// Do nothing. The file has already been scanned
				}
				else
				{
					// Get number of vertices & edges
					// Then, initialize the graph
					fscanf(file, "%i", &v);
					fscanf(file, "%i", &u);

					graph = Initialize_Graph(v, u);
				
					// Initialize adjacency list
					int q = 0;
					while (fscanf(file, "%i %i %i", &u, &v, &w) != EOF && q < graph->E)
					{
					
						// initializes an edge and sets its "next" pointer to the current head
						LIST* newEdge = new LIST(w, v, graph->adj_list[u - 1]);
						// sets the current head to the newly initialized edge, thereby inserting it 
						// into the linked list at the top while preserving the linked list's order
						graph->adj_list[u - 1] = newEdge;
						q++;
					
					}
					if (q != graph->E)
					{
					
						std::cout << "ERROR: The number of edges is less than was specified in the beginning of the file." << std::endl;
						// Need to reset everything to NULL/nullptr and/or free up all the memory so that the other failsafes don't get bypassed
				
					}
					rBool = true; // Set so that you don't read the graph twice
					// (really, it's because I don't want to have to reset fscanf and the file pointer
					q = 0; // soft reset so that you can type 'R' twice if you're so inclined...
				}
				/*DEBUGGINGelse
				{
					
					std::cout << "edges: " << graph->E << std::endl;
					std::cout << "vertices: " << graph->V << std::endl;
					std::cout << "graph initialized" << std::endl;					
					
				}*/

			}
		}
		else if (c == 'W' || c == 'w')
		{
			if(graph == nullptr)
			{
				std::cout << "Please initialize the graph first" << std::endl;
			}
			else
			{
				std::cout << "COMMAND: " << c << std::endl;
				Print_Graph(graph);
			}
		}
		else if (c == 'I' || c == 'i')
		{
			if(heap == nullptr)
			{
				std::cout << "Please initialize the heap first" << std::endl;
			}
			else
			{
				std::cout << "COMMAND: " << c << " " << v << " " << w << std::endl;
				Insert (heap, v, w);
			}
		}
		else if (c == 'P' || c == 'p')
		{
			
			// Find the shortest path from s to t  (u to v);
			
			if(graph == nullptr)
			{
				std::cout << "Please initialize the graph first" << std::endl;
			}
			else if(!(u < graph->V + 1) || !(v < graph->V + 1)) // u = s; v = t;
			{
				std::cout << "Please enter valid nodes" << std::endl;
				
				if(w != 0 && w != 1)
				{
					std::cout << "Error: Invalid flag value" << std::endl;
				}
			}
			else if(w != 0 && w != 1)
			{
				std::cout << "Error: Invalid flag value" << std::endl;
			}
			else
			{
				if (u == v)
				{
					if (w == 0)
					{
						std::cout << "LENGTH: 0" << std::endl;
					}
					else
					{
						std::cout << "PATH: " << u << std::endl;
					}
				}
				else
				{
					
					//I think I need to initialize this at u = 1 and then never call it or 
					//Dijkstra again afterwards and just use the .pi attributes 
					Initialize_Single_Source(graph, u - 1);
					//DEBUGGINGstd::cout << "Finding the shortest path" << std::endl;
					// find the shortest path;
				
					// Need to call Dijkstra, not do whatever the fuck I was doing above...
					Dijkstra(graph);
					
					//DEBUGGINGstd::cout << "Graph sorting complete" << std::endl;
					
					if (w == 0)
					{
						if (graph->heapOfNodes[graph->nodePositions[v - 1]].key == INF)
						{
							std::cout << "Sorry, node " << v << " isn't reachable from node " << u << "." << std::endl;
						}
						else
						{
							std::cout << "Length: " << graph->heapOfNodes[graph->nodePositions[v - 1]].key << std::endl;
						}
					}
					if (w == 1)
					{
						if (graph->heapOfNodes[graph->nodePositions[v - 1]].key == INF)
						{
							std::cout << "Sorry, node " << v << " isn't reachable from node " << u << "." << std::endl;
						}
						else
						{
						
												
						/*std::cout << "PATH: " << v;
						ELEMENT nodeTrav = graph->heapOfNodes[graph->nodePositions[v - 1]];
						int z = 0;
						
						do {
							nodeTrav = graph->heapOfNodes[graph->nodePositions[nodeTrav.pi]];
							std::cout << " <- " << nodeTrav.node;
							
							z++;
						} while (nodeTrav.node != u && z < 50);
						*/
						// could make a recursive function which prints the path left to right
						// as it unspirals...
						
						std::cout << "PATH: ";
						ELEMENT nodeTrav = graph->heapOfNodes[graph->nodePositions[v - 1]];
						int z = 0;
						pathRecur(nodeTrav, graph, u, v, z);
						
						}
					}
				}				
			}

		}
		else if (c == 'K' || c == 'k')
		{
			if(heap == nullptr)
			{
				std::cout << "Please initialize the heap first" << std::endl;
			}
			else if (u < 0 || u >= heap->size)
			{
				std::cout << "Please give a valid index" << std::endl;
			}
			else
			{
				std::cout << "COMMAND: " << c << " " << u << " " << v << " " << w << std::endl;
				Heap_Increase_Key(heap, u, v, w);
			}
		}
		else if (c == 'D' || c == 'd')
		{
			if(heap == nullptr)
			{
				std::cout << "Please initialize the heap first" << std::endl;
			}
			else
			{
				std::cout << "COMMAND: " << c << " " << w << std::endl;
				std::cout << Delete_Min(heap, w).key << std::endl;
			}
		}
	}
	
	fclose(file);
	
	// need to free up memory used in heap object;
	if(heap)
	{
		free(heap->H);
		free(heap);
	}
	
	
	if(graph)
	{
		//Delete all LIST elements
		LIST* lpt;
		for(int i = 0; i < graph->V; i++)
		{
			lpt = graph->adj_list[i];
			deleteList(lpt);
		}
		
		// FLY MY MEMORY! BE...
		free(graph->adj_list);
		free(graph->heapOfNodes);
		free(graph->nodePositions);
		free(graph);
		
		//Memory-freeing to-do list in pseudocode
		//----------------------------------------
		//need to recursively free/delete every LIST element I've created in adj_list
		//deleteList(LIST* lpt){if(LIST*==nullptr){return;}else{deleteList(lpt->next); free(lpt);}}
		//free adj_list itself
		//free every node element in heapOfNodes
		//free the nodePositions memory
		//???
		//Profit
	}
	
	std::cout << "thanks for coming!" << std::endl;
	return 0;
}