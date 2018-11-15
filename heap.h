// Heap.h

// Heap files should implement the heap functions

#ifndef _HEAP_H_INCLUDED
#define _HEAP_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

struct ELEMENT{
	int key;// = NULL;
	
	ELEMENT(int n);
	/*{
		this->key = n;
	}*/
	
};

struct HEAP{
	int capacity;
	int size;
	ELEMENT* H;
	
	
	//This gets removed & put into the .cpp file?
	HEAP(int cap, int siz);
	/*{
		this->capacity = cap;
		this->size = siz;
		H = (ELEMENT*) malloc(sizeof(ELEMENT) * cap);
	}*/
	
	int getCap();
	/*{
		return capacity;
	}*/
	
};

HEAP* Initialize(int n);
/*{
	HEAP* h = new HEAP(n, 0);
	std::cout << h->capacity << std::endl;

	return h;
}*/

void Print_Heap(HEAP* h);
/*{
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
			std::cout << "ELEMENT " << i <<  ": " << h->H[i].key << std::endl;
		}
	}
	return;
}*/

void Max_Heapify(HEAP* heap, int i);
/*{
	std::cout << "\nNew round of Max_Heapify: \n" << std::endl;

	int L = 2*i;
	int R = 2*i + 1;
	int largest = i;
	
	std::cout << "value of i: " << i << "\nvalue of L: " << L << "\nvalue of R: " << R << std::endl;
	std::cout << "H[0]: " << heap->H[0].key << std::endl;
	
	if (L < heap->size && heap->H[L].key > heap->H[i].key)
	{
		std::cout << "\nL: " << L << "\nlargest: " << largest << std::endl;
		largest = L;
		std::cout << "\nL: " << L << "\nlargest: " << largest << std::endl;
	}
	if (R < heap->size && heap->H[R].key > heap->H[largest].key)
	{
		std::cout << "\nR: " << R << "\nlargest: " << largest << std::endl;
		largest = R;
		std::cout << "\nR: " << R << "\nlargest: " << largest << std::endl;
	}
	if (largest != i)
	{
		std::cout << "H[" << i << "] " << heap->H[i].key << std::endl;
		std::cout << "H[" << largest << "] " << heap->H[largest].key << std::endl;
		ELEMENT temp = heap->H[i];
		std::cout << "temp.key: " << temp.key << std::endl;
		heap->H[i] = heap->H[largest];
		heap->H[largest] = temp;
		Max_Heapify(heap, largest);
	}
	std::cout << "H[0]: " << heap->H[0].key << std::endl;
	return;
}*/

void Build_Heap(HEAP* heap, ELEMENT* Array, int n, int flag);
/*{
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
	std::cout << "Heap capacity before Build_Heap: " << heap->capacity << std::endl;
	for (int i = 0; i < n; i++)
	{
		std::cout << "Array[" << i << "] key: " << Array[i].key << std::endl;
		heap->H[i] = ELEMENT(Array[i].key);
		heap->size++;
		std::cout << "Heap[" << i << "] key: " << heap->H[i].key << std::endl;
	}
	std::cout << "Heap capacity after first step of Build_Heap: " << heap->capacity << std::endl;
	if (flag == 2)
	{
		for (int i = n/2; i > -1; i--)
		{
			Max_Heapify(heap, i);
			Print_Heap(heap);
		}		
	}
	
	else 
	{
		for (int i = n/2; i > -1; i--)
		{
			std::cout << "\n\nOuter call to Max_Heapify\n\n" << std::endl;
			Max_Heapify(heap, i);
		}
	}
	std::cout << "Heap capacity after second step of Build_Heap: " << heap->capacity << std::endl;
	if (flag == 1)
	{
		Print_Heap(heap);
	}
	
	return;
}*/

void Heap_Increase_Key(HEAP* heap, int i, int value, int flag);
/*{
	if (value < heap->H[i].key)
	{
		std::cout << heap->H[i].key << std::endl;
		std::cout << "error: new key is smaller than current key" << std::endl;
		return;
	}
	else
	{
		std::cout << "Heap_Increase_Key" << std::endl;
		if (flag == 1) {Print_Heap(heap);}
		heap->H[i].key = value;
		
		while (i > 1 && heap->H[i/2].key < heap->H[i].key)
		{

			int temp = heap->H[i].key;
			heap->H[i].key = heap->H[i/2].key;
			heap->H[i/2].key = temp;
			i = i / 2;
			
		}
		if (flag == 1) {Print_Heap(heap);}
	}
	return;
}*/

void Insert_Key(HEAP* heap, int value, int flag);
/*{

	if (heap->size == heap->capacity)
	{
		std::cout << "resizing" << std::endl;
		
		int c = (int)std::log2(heap->size) + 1;
		
		heap->H = (ELEMENT*)realloc(heap->H, sizeof(ELEMENT) * (std::pow(2,c)));
		heap->capacity = std::pow(2,c);		
	}	
	
	std::cout << "hello I'm insert_key" << std::endl;
	
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

	
	//Heap_Increase_Key(heap, heap->size, value, flag);
	return;
}*/

void Insert(HEAP* heap, int k, int flag);
/*{
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
}*/

ELEMENT Delete_Max(HEAP* heap, int flag);
/*{
	if (heap->size < 1)
	{
		std::cout << "error: heap empty" << std::endl;
		return NULL;
	}
	
	if (flag == 1)
	{
		Print_Heap(heap);
	}
	
	ELEMENT temp = ELEMENT(heap->H[0].key);
	std::cout << heap->H[0].key << std::endl;
	heap->H[0] = heap->H[heap->size - 1];
	std::cout << heap->H[0].key << std::endl;
	delete &(heap->H[heap->size - 1]);
	heap->size--;
	
	Max_Heapify(heap, 0);
	
	if (flag == 1)
	{
		Print_Heap(heap);
	}
	return temp;
;
}*/

char nextCommand(int *i, int *v, int *f, HEAP* heap, FILE* file);
/*{
	//HEAP* heap;
	//HEAP h;
	char c;
	while(1)
	{
		scanf("%c", &c);
		
		// Take care of contingent characters
		if (c == ' ' || c == '\t' || c == '\n')
		{
			continue;
		}
		
		// Stop the program
		if (c == 'S' || c == 's')
		{
			break;
		}
		
		// Create new, empty heap w/ capacity = n
		if (c == 'C' || c == 'c')
		{
			scanf("%d", v);;
			break;
		}
		
		// Read in the array A from HEAPinput.txt
		// && 
		// Build the heap 
		if (c == 'R' || c == 'r')
		{
			scanf("%d", f);
			break;
		}
		
		// Print out the whole heap
		if (c == 'W' || c == 'w')
		{
			break;
		}

		if (c == 'I' || c == 'i')
		{
			scanf("%d", v); scanf("%d", f);
			break;
		}
		
		// Increase key
		if (c == 'K' || c == 'k')
		{
			scanf("%d", i); scanf("%d", v); scanf("%d", f);
			break;
		}

		
		// Delete max and print it's key value
		if (c == 'D' || c == 'd')
		{
			scanf("%d", f);
			break;
		}

		if (c == 'L')
		{
			std::cout << "this works" << std::endl;
			break;
		}

		// Deal with invalid commands
		else
		{
			printf("Invalid Command\n");
			break;
		}
	}
	return c;
}*/

#endif