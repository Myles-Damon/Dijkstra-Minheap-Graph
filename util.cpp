// Util.cpp
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "util.h"
#include "heap.h"

// u == i; v == v; w == f

char nextCommand(int *u, int *v, int *w, HEAP* heap, FILE* file)
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
			//scanf("%d", w); // 'R' Doesn't take a flag in assignment 2
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
			scanf("%d", v); scanf("%d", w);
			break;
		}
		
		// Increase key
		if (c == 'K' || c == 'k')
		{
			scanf("%d", u); scanf("%d", v); scanf("%d", w);
			break;
		}

		// Delete max and print it's key value
		if (c == 'D' || c == 'd')
		{
			scanf("%d", w);
			break;
		}

		if (c == 'L')
		{
			std::cout << "this works" << std::endl;
			break;
		}
		
		if (c == 'P' || c == 'p')
		{
			scanf("%d", u); scanf("%d", v); scanf("%d", w);
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
