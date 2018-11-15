// main.cpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

#include "heap.h"
#include "util.h"

#pragma GCC diagnostic ignored "-Wpointer-arith"
#pragma GCC diagnostic ignored "-Wconversion-null"

int main()
{

	printf("hello\n");	
	
	FILE* file = fopen("HEAPinput.txt", "r");	
	int i, v, f;
	char c = 'P';
	HEAP* heap = nullptr;
	
	while(c != 'S')
	{
		printf("\nInput a command: ");
		c = nextCommand(&i, &v, &f, heap, file);
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
			else if(heap == nullptr)
			{
				std::cout << "Please initialize the heap first" << std::endl;
			}
			else
			{
				char buffer[10];
				std::cout << "COMMAND: " << c << " " << f << std::endl;
				std::cout << "Heap capacity: " << heap->capacity << std::endl;
				
				// get # of items in array & dynamically create array
				fgets(buffer, 10, file);
				int length = atoi(buffer);
				ELEMENT* A = (ELEMENT*) malloc((length + 1) * sizeof(ELEMENT));
				
				// fill up array
				int q = 0;
				while (fgets(buffer, 10, file) && q < (length))
				{
					A[q].key = atoi(buffer);
					std::cout << "A[" << q << "] key: " << A[q].key << std::endl;
					q++;
				}
				Build_Heap(heap, A, q, f);
				
				if (length < heap->size)
				{
					std::cout << "Warning, number of elements in the file is less than as specified in the beginning of the file" << std::endl;
				}
				
			}
		}
		else if (c == 'W' || c == 'w')
		{
			if(heap == nullptr)
			{
				std::cout << "Please initialize the heap first" << std::endl;
			}
			else
			{
				std::cout << "COMMAND: " << c << std::endl;
				Print_Heap(heap);
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
				std::cout << "COMMAND: " << c << " " << v << " " << f << std::endl;
				Insert (heap, v, f);
			}
		}
		else if (c == 'K' || c == 'k')
		{
			if(heap == nullptr)
			{
				std::cout << "Please initialize the heap first" << std::endl;
			}
			else if(i < 0 || i >= heap->size)
			{
				std::cout << "Please give a valid index" << std::endl;
			}
			else
			{
				std::cout << "COMMAND: " << c << " " << i << " " << v << " " << f << std::endl;
				Heap_Increase_Key(heap, i, v, f);
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
				std::cout << "COMMAND: " << c << " " << f << std::endl;
				std::cout << Delete_Max(heap, f).key << std::endl;
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
	
	std::cout << "thanks for coming!" << std::endl;
	return 0;
}