// Heap.cpp
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

#include "heap.h"

#pragma GCC diagnostic ignored "-Wpointer-arith"
#pragma GCC diagnostic ignored "-Wconversion-null"

//
ELEMENT::ELEMENT(int n) : key(n) {}
//

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
void Min_Heapify(HEAP* heap, int i)
{


	int L = 2*i;
	int R = 2*i + 1;
	int smallest = i;
	

	
	if (L < heap->size && heap->H[L].key < heap->H[i].key)
	{

		smallest = L;

	}
	if (R < heap->size && heap->H[R].key < heap->H[largest].key)
	{

		smallest = R;

	}
	if (smallest != i)
	{

		ELEMENT temp = heap->H[i];

		heap->H[i] = heap->H[smallest];
		heap->H[smallest] = temp;
		Max_Heapify(heap, smallest);
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






































