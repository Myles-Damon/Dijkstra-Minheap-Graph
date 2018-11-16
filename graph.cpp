//graph.cpp

// should implement graph functions

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

#include "heap.h"
#include "util.h"

LIST::LIST(int weight, int neighbor) : weight(weight), neighbor(neighbor) {}

GRAPH::GRAPH(int v, int e) : V(v), E(e), heap ((ELEMENT*) malloc(sizeof(ELEMENT) * V)), adj_list ((LIST**) malloc(sizeof(LIST*) * E)) {}

