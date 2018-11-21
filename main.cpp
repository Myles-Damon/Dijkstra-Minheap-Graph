// main.cpp

#include <stdio.h>
#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <cmath>

#include "heap.h"
#include "util.h"
#include "graph.h"

#pragma GCC diagnostic ignored "-Wpointer-arith"
#pragma GCC diagnostic ignored "-Wconversion-null"

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

int main()
{

	printf("hello\n");	
	
	FILE* file = fopen("Ginput.txt", "r");	
	int u, v, w;
	char c = 'P';
	HEAP* heap = nullptr;
	GRAPH* graph = nullptr;
	
	while(c != 'S')
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
				//char buffer[10];
				std::cout << "COMMAND: " << c <</* " " << f << */std::endl;
				//std::cout << "Heap capacity: " << heap->capacity << std::endl;
				/* Stuff for heap, not graph
				// get # of items in array & dynamically create array
				fgets(buffer, 10, file);
				int length = atoi(buffer);
				ELEMENT* A = (ELEMENT*) malloc((length + 1) * sizeof(ELEMENT));
				*/ // END Stuff for heap, not graph
				// fill up array
				int q = 0;
				char flag = w;
				// Read first line and get number of vertices and edges
				fscanf(file, "%i", &v);
				std::cout << "vertices: " << v << std::endl;
				fscanf(file, "%i", &u);
				std::cout << "edges: " << u << std::endl;
				graph = Initialize_Graph(v, u);
				std::cout << "graph initialized" << std::endl;
				
				// Initialize adjacency list
				while (fscanf(file, "%i %i %i", &u, &v, &w) && q < graph->E)
				{
					/*if(graph->adj_list[u] == nullptr)
					{
						std::cout << "it's a null ptr" << std::endl;
					}*/
					//LIST* nullListPtr = nullptr;
					
					// initializes an edge and sets its "next" pointer to the current head
					LIST* newEdge = new LIST(w, v, graph->adj_list[u - 1]);
					// sets the current head to the newly initialized edge, thereby inserting it 
					// into the linked list at the top while preserving the linked list's order
					graph->adj_list[u - 1] = newEdge;
					q++;
				}
				//std::cout << graph->adj_list[0]->neighbor << " " << graph->adj_list[0]->weight << std::endl;
				/*
				while (fgets(buffer, 10, file) && q < (length))
				{
					A[q].key = atoi(buffer);
					std::cout << "A[" << q << "] key: " << A[q].key << std::endl;
					q++;
				}
				
				Build_Heap(heap, A, q, w);
				*/
				
				
				Initialize_Single_Source(graph, 0); // for testing purposes. Should be moved later
				Build_Graph(graph, flag);
				
				
				/*
				if (length < heap->size)
				{
					std::cout << "Warning, number of elements in the file is less than as specified in the beginning of the file" << std::endl;
				}
				*/
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
			}
			else
			{
				std::cout << "Finding the shortest path" << std::endl;
				// find the shortest path;
				/*for (int i = 0; i < graph->V; i++)
				{
					Delete_Min(graph, w);
				}*/
				
				// Need to call Dijkstra, not do whatever the fuck I was doing above...
				Dijkstra(graph);
				std::cout << "Graph sorting complete" << std::endl;
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
		
		free(graph->adj_list);
		
		/*for(int i = 0; i < graph->V; i++)
		{
			free(graph->heapOfNodes[i]);
			free(graph->nodePositions[i]);
		}*/
		
		free(graph->heapOfNodes);
		free(graph->nodePositions);
		
		free(graph);
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