// Heap.cpp
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

#include "graph.h"
#include "heap.h"

#pragma GCC diagnostic ignored "-Wpointer-arith"
#pragma GCC diagnostic ignored "-Wconversion-null"

/*
ELEMENT::ELEMENT(int n) : key(n) {}
ELEMENT::ELEMENT(int n, int d, int p) : node(n), key(d), pi(p) {}
*/

//
HEAP::HEAP(int cap, int siz) : capacity(cap), size(siz), H ((ELEMENT*) malloc(sizeof(ELEMENT) * cap)) {}
int HEAP::getCap()
{
	return capacity;
}
//

//
HEAP* Initialize(int n)
{
	HEAP* h = new HEAP(n, 0);
	
	return h;
}
/*
GRAPH* Initialize(int vertices, int edges)
{
	GRAPH* g = new GRAPH(vertices, edges);
	
	return g;
}*/
//

//
void Print_Heap(HEAP* h)
{
	std::cout << "capacity: " << h->capacity << std::endl;
	std::cout << "size: " << h->size << "\n" << std::endl;
	if (h->size == 0 || h->size == NULL)
	{
		return;
	}
	else
	{
		for (int i = 0; i < h->size; i++)
		{
			std::cout << "ELEMENT " << i << ": " << h->H[i].key << std::endl;
		}
	}
	return;
}
//

//WIP conversion of Max_Heapify to Min_Heapify;
void Min_Heapify(GRAPH* g, int i, int n)
{

	int L, R, smallest;	
	// n is heap size passed as an argument
	if(!(i < n))
	{
		return;
	}
	/*
	if (n < 3)
	{
		if (n == 2)
		{
			if (g->heapOfNodes[1].key < g->heapOfNodes[0].key)
			{
				ELEMENT temp = g->heapOfNodes[0];
				g->heapOfNodes[0] = g->heapOfNodes[1];
				g->heapOfNodes[1] = temp;
				
				for(int i = 0; i < g->V; i++)
				{
					g->nodePositions[g->heapOfNodes[i].node - 1] = i;
				}
				return;
			}
			return;
		}
		else
		{
			return;
		}
	}
	else if (i == 0)
	{
		
		L = 1;
		R = 2;
		smallest = 0;
	}*/
	else
	{
		L = 2*i;
		R = 2*i + 1;
		smallest = i;
	}
	
	if (L < n && g->heapOfNodes[L].key < g->heapOfNodes[i].key)
	{

		smallest = L;

	}
	if (R < n && g->heapOfNodes[R].key < g->heapOfNodes[smallest].key)
	{

		smallest = R;

	}
	if (smallest != i)
	{
		
		ELEMENT temp = g->heapOfNodes[i];
		g->heapOfNodes[i] = g->heapOfNodes[smallest];
		g->heapOfNodes[smallest] = temp;
		
		for(int i = 0; i < g->V; i++)
		{
			g->nodePositions[g->heapOfNodes[i].node - 1] = i;
		}
		
		Min_Heapify(g, smallest, g->numberOfNodes);
		
	}

	return;
}

void Min_Heapify(HEAP* heap, int i)
{

	// n is heap size passed as an argument instead of accessed via the HEAP*
	int L = 2*i;
	int R = 2*i + 1;
	int smallest = i;
	

	
	if (L < heap->size && heap->H[L].key < heap->H[i].key)
	{

		smallest = L;

	}
	if (R < heap->size && heap->H[R].key < heap->H[smallest].key)
	{

		smallest = R;

	}
	if (smallest != i)
	{
		
		ELEMENT temp = heap->H[i];

		heap->H[i] = heap->H[smallest];
		heap->H[smallest] = temp;
		Min_Heapify(heap, smallest);

		
	}

	return;
}

void Build_Heap(HEAP* heap, ELEMENT* Array, int n, int flag)
{
	// N IS THE SIZE OF ARRAY Array[]
	if (heap->getCap() < n)
	{
		std::cout << "Heap capacity is less than array size. Resizing heap" << std::endl;
		// gets the result of the floor function of log2(n) (floor function == casting float to int)
		// adds 1, and then uses that as the lowest exponent of 
		// 2 which will leave the heap with enough capacity to 
		// take in the new array items once the size of the 
		// heap is changed via realloc()
		
		int c = (int)std::log2(n) + 1;
		
		heap->H = (ELEMENT*)realloc(heap->H, sizeof(ELEMENT) * (std::pow(2,c)));
		heap->capacity = std::pow(2,c);
	}
	
	std::cout << "Filling heap with elements from array" << std::endl;

	for (int i = 0; i < n; i++)
	{

		heap->H[i] = ELEMENT(Array[i].key);
		heap->size++;

	}

	if (flag == 2)
	{
		for (int i = n/2; i > -1; i--)
		{
			Min_Heapify(heap, i);
			Print_Heap(heap);
		}		
	}
	
	else 
	{
		for (int i = n/2; i > -1; i--)
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

void Heap_Increase_Key(HEAP* heap, int i, int value, int flag)
{
	if (value < heap->H[i].key)
	{

		std::cout << "error: new key is smaller than current key" << std::endl;
		return;
	}
	else
	{

		if (flag == 1) {Print_Heap(heap);}
		heap->H[i].key = value;
		
		while (i > -1 && heap->H[i/2].key < heap->H[i].key)
		{

			int temp = heap->H[i].key;
			heap->H[i].key = heap->H[i/2].key;
			heap->H[i/2].key = temp;
			i = i / 2;
			
		}
		if (flag == 1) {Print_Heap(heap);}
	}
	return;
}

void Insert_Key(HEAP* heap, int value, int flag)
{

	if (heap->size == heap->capacity)
	{
		std::cout << "resizing" << std::endl;
		
		int c = (int)std::log2(heap->size) + 1;
		
		heap->H = (ELEMENT*)realloc(heap->H, sizeof(ELEMENT) * (std::pow(2,c)));
		heap->capacity = std::pow(2,c);		
	}	
	
	
	std::cout << "Inserting key at end of heap" << std::endl;
	if (flag == 1) {Print_Heap(heap);}
	heap->H[heap->size].key = value;
	
	int i = heap->size - 1;
	while (i > -1 && heap->H[i/2].key < heap->H[i].key)
	{

		int temp = heap->H[i].key;
		heap->H[i].key = heap->H[i/2].key;
		heap->H[i/2].key = temp;
		i = i / 2;
		
	}
	if (flag == 1) {Print_Heap(heap);}

	return;
}

void Insert(HEAP* heap, int k, int flag)
{
	if (heap->size == heap->capacity)
	{
		std::cout << "resizing" << std::endl;
		int c = (int)std::log2(heap->size) + 1;
		
		heap->H = (ELEMENT*)realloc(heap->H, sizeof(ELEMENT) * (std::pow(2,c)));
		heap->capacity = std::pow(2,c);	
	}
	
	heap->H[heap->size] = ELEMENT(k);
	heap->size++;
	Insert_Key(heap, k, flag);
}

ELEMENT Delete_Min(HEAP* heap, int flag)
{
	if (heap->size < 1 || heap == nullptr)
	{
		std::cout << "error: heap empty or uninitialized" << std::endl;
		return NULL;
	}
	
	if (flag == 1)
	{
		Print_Heap(heap);
	}
	
	ELEMENT temp = ELEMENT(heap->H[0].key);

	heap->H[0] = heap->H[heap->size - 1];

	delete &(heap->H[heap->size - 1]);
	heap->size--;
	
	Min_Heapify(heap, 0);
	
	if (flag == 1)
	{
		Print_Heap(heap);
	}
	return temp;
}

// Graph-ified version of Delete_Min
void Delete_Min(GRAPH* g, int flag)
{
	// So... I'm thinking I should just set the "node to be removed"
	// as the last node in the heap and then decrease the heap_size
	// variable of GRAPH so that I don't have to create a second 
	// array of ELEMENTS and can do more w/ less code.
	
	// With that said, I'm gonna do that. So this doesn't actually 
	// delete the node, it just puts it at the back and changes
	// the node's position thing in GRAPH.
	
	if (g->heapOfNodes == nullptr || g->V < 1)
	{
		std::cout << "error: graph empty (sorted) or uninitialized" << std::endl;
		return/* NULL*/;
	}
	
	if (flag == 1)
	{
		std::cout << "Printing graph before deletion of min node" << std::endl;
		Print_Graph(g);
		for(int i = 0; i < g->V; i++)
		{
			//g->nodePositions[g->heapOfNodes[i].node - 1] = i;
			std::cout << "node: " << g->heapOfNodes[i].node << " key: " << g->heapOfNodes[i].key << std::endl;
		}
	}
	

	std::cout << "Assigned node numbers" << std::endl;
	
	ELEMENT temp = g->heapOfNodes[0];
	
	std::cout << "Created temporary node" << std::endl;
	

	g->heapOfNodes[0] = g->heapOfNodes[g->numberOfNodes - 1];
	g->heapOfNodes[g->numberOfNodes - 1] = temp;
	
	std::cout << "Finished node swap/deletion" << std::endl;
	
	g->numberOfNodes--;
	
	for(int i = 0; i < g->V; i++)
	{
		g->nodePositions[g->heapOfNodes[i].node - 1] = i;
	}
	for(int i = 0; i < g->V; i++)
	{
		//g->nodePositions[g->heapOfNodes[i].node - 1] = i;
		std::cout << "node: " << g->heapOfNodes[i].node << " key: " << g->heapOfNodes[i].key << std::endl;
	}
	
	if (flag == 1)
	{
		Print_Graph(g);
	}
	return;
	
	// NEED TO ADD TO sortedNodeList in the correct position 
	// IE JUST PUT IT IN THE ARRAY IN THE POSITION WHICH IT'S 
	// NODE ATTRIBUTE SUGGESTS
	
	// OR JUST DO WHAT I ENDED UP DOING, WHICH WAS TO JUST PUT IT AT THE END OF THE LIST 
	// AND THEN CHANGE THE VARIABLE WHICH REPRESENTS THE SIZE OF THE HEAP SO THAT I DON'T 
	// HAVE TO USE MORE THAN ONE ARRAY/HEAP
	
}






































