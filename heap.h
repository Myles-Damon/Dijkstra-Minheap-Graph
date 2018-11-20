// heap.h

// Heap files should implement the heap functions

#ifndef _HEAP_H_INCLUDED
#define _HEAP_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

#include "graph.h"

/*struct ELEMENT{
	int node;
	int key;
	int pi;
	
	ELEMENT(int n);
	ELEMENT(int n, int d, int p);

};*/ //Moved to heap.h???

struct HEAP{
	int capacity;
	int size;
	ELEMENT* H;
	
	HEAP(int cap, int siz);
	
	int getCap();
	
};

HEAP* Initialize(int n);


void Print_Heap(HEAP* h);

void Min_Heapify(GRAPH* g, int i, int n);
void Min_Heapify(HEAP* heap, int i);



void Build_Heap(HEAP* heap, ELEMENT* Array, int n, int flag);


void Heap_Increase_Key(HEAP* heap, int i, int value, int flag);


void Insert_Key(HEAP* heap, int value, int flag);


void Insert(HEAP* heap, int k, int flag);

ELEMENT Delete_Min(GRAPH* g, int flag);
ELEMENT Delete_Min(HEAP* heap, int flag);



char nextCommand(int *i, int *v, int *f, HEAP* heap, FILE* file);


#endif