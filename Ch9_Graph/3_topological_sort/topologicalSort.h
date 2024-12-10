#ifndef __TOPOLOGICAL_SORT_H_
#define __TOPOLOGICAL_SORT_H_

#include "graph.h"
#include "single_linked_list.h"

void topologicalSort(Vertex* v, List* list);
void topologicalDFS(Vertex* v, List* list);

#endif