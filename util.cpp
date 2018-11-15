// Util.cpp
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "util.h"
#include "heap.h"

char nextCommand(int *i, int *v, int *f, HEAP* heap, FILE* file)
{
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
			scanf("%d", v);
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
			//Print_Heap(heap);
			break;
		}

		if (c == 'I' || c == 'i')
		{
			scanf("%d", v); scanf("%d", f);
			//Insert_Key(heap,*i, *v, *f);
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
}
