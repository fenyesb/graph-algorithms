// Fényes Balázs
// f.balazs96@gmail.com

#ifndef _ALGORITHMS_H
#define _ALGORITHMS_H

#include "data.h"
#include "generics.h"

void DFS_recursive(generic_linkedlist* v_head, generic_tree* gt);
bool Dijkstra(generic_linkedlist* v_head, vertexdata* vroot, vertexdata* vgoal, generic_linkedlist** path);
generic_tree* DFS(generic_linkedlist* v_head, vertexdata* vroot);
generic_tree* BFS(generic_linkedlist* v_head, vertexdata* vroot);
bool Ford(generic_linkedlist* v_head, vertexdata* vroot, generic_linkedlist** paths_ptr);

#endif
