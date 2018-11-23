# Dijkstra-Minheap-Graph

Myles Damon
CSE 310 Project 2
Dijkstra Minheap Graph

This program does all of what the rubric requires.
It was done in C++

It takes in a graph from a text file called "Ginput.txt"
and creates the adjacency-list array. When given a source
node and an end node, it calculates the distance from the 
source node to each node and stores the "parent" node for 
each node for back-tracking (to trace out the path after 
calculating each node's "key" value. Like my last program, 
it is memory-safe.

I used a parallel array of integers to track the locations 
of all of the vertices once they started to get jumbled 
around with each Min_Heapify. This allowed me to not have 
a separate "S" array of "sorted" nodes.


main.cpp includes only a function for freeing up the 
adjacency-list memory, a function for printing the s-t 
path, and the main function.

graph.cpp includes all of the functions for initializing 
the graph, fixing the parallel array, finding the shortest 
edge (which incorporates/is the "relax" step of Dijkstra), 
printing the graph, and the __init__-style "Dijkstra 
function which is the umbrella for calling all of them.

heap.cpp includes all of the old heap functions from the 
last project + some new, graph-ified versions which serve 
to heapify the ELEMENT array of nodes from the larger GRAPH 
struct (instead of from a HEAP struct). Delete_Min() now 
swaps the min element with the last element in the heap and
then decrements a member variable of GRAPH which represents 
the graph's heap-size; This way I don't have to have that 
"S" array but I can still keep track of all of the nodes 
since it updates their index in the parallel position array

util.cpp includes only the function for taking arguments 
from the command line.