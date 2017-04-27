// Fényes Balázs
// f.balazs96@gmail.com

/**
@file
A gráfalgoritmusokat tartalmazó fájl.
*/

#include <stdbool.h>
#include "data.h"
#include "io.h"
#include "algorithms.h"

///Csak a @c DFS() függvény hívhatja meg.
void DFS_recursive(generic_linkedlist* v_head, generic_tree* gt){
	((vertexdata*)(gt->data))->mark = true;
	for(generic_linkedlist* iterator = ((vertexdata*)(gt->data))->edgelist; iterator; iterator = iterator->next)
	{
		edgedata* vedge = (edgedata*)(iterator->data);
		vertexdata* vptr = vedge->target;
		if(!vptr->mark)
		{
			generic_tree* leaf;
			generic_tree_init(&leaf, vptr);
			generic_tree_insert(gt, leaf);
			DFS_recursive(v_head, leaf); 
		}
	}
}

///A @c vroot gyökérpontból megkeresi a legrövidebb utat a @c vgoal célcsúcsba. Csak akkor használható, ha minden távolság nemnegatív.
bool Dijkstra(generic_linkedlist* v_head, vertexdata* vroot, vertexdata* vgoal, generic_linkedlist** path){
	bool foundpath = false;
	for(generic_linkedlist* iterator = v_head; iterator; iterator = iterator->next)
	{
		vertexdata* vdata = (vertexdata*)(iterator->data);
		vdata->mark = false;
		vdata->dist = INFINITY;
		vdata->from = NULL;
	}
	vroot->dist = 0;
	for(;;){
		vertexdata* min_vertex = NULL;
		int min_dist = INFINITY;
		for(generic_linkedlist* iterator = v_head; iterator; iterator = iterator->next)
		{
			vertexdata* vdata = (vertexdata*)(iterator->data);
			if(!(vdata->mark) && vdata->dist < min_dist)
			{
				min_vertex = vdata;
				min_dist = vdata->dist;
			}
		}
		if(min_vertex == NULL)
		{
			break;
		}
		if(min_vertex == vgoal)
		{
			foundpath = true;
			break;
		}
		min_vertex->mark = true;
		for(generic_linkedlist* iterator = min_vertex->edgelist; iterator; iterator = iterator->next)
		{
			edgedata* vedge = (edgedata*)(iterator->data);
			if(vedge->weight < 0)
			{
				return false;
			}
			vertexdata* vptr = vedge->target;
			if(!vptr->mark)
			{
				int newdist = min_vertex->dist + vedge->weight;
				if(newdist < vptr->dist)
				{
					vptr->dist = newdist;
					vptr->from = min_vertex;
				}
			}
		}
	}
	if(foundpath){
		generic_linkedlist* list = NULL;
		vertexdata* vcurr = vgoal;
		while(vcurr != NULL)
		{
			generic_linkedlist* elm;
			generic_linkedlist_init(&elm, vcurr);
			elm->next = list;
			list = elm;
			vcurr = vcurr->from;
		}
		*path = list;
	}
	return foundpath;
}

///Mélységi bejárás egy adott @c vroot gyökércsúcsból.
generic_tree* DFS(generic_linkedlist* v_head, vertexdata* vroot){
	for(generic_linkedlist* iterator = v_head; iterator; iterator = iterator->next)
	{
		vertexdata* vdata = (vertexdata*)(iterator->data);
		vdata->mark = false;
	}
	generic_tree* gt;
	generic_tree_init(&gt, vroot);
	DFS_recursive(v_head, gt);
	return gt;
}

///Szélességi bejárás egy adott @c vroot gyökércsúcsból.
generic_tree* BFS(generic_linkedlist* v_head, vertexdata* vroot)
{
	for(generic_linkedlist* iterator = v_head; iterator; iterator = iterator->next)
	{
		vertexdata* vdata = (vertexdata*)(iterator->data);
		vdata->mark = false;
	}
	vroot->mark = true;
	generic_tree* gt;
	generic_tree_init(&gt, vroot);
	generic_queue* gq;
	generic_queue_init(&gq, gt);
	do
	{
		generic_tree* current = generic_queue_dequeue(gq);
		for(generic_linkedlist* iterator = ((vertexdata*)(current->data))->edgelist; iterator; iterator = iterator->next)
		{
			edgedata* vedge = (edgedata*)(iterator->data);
			vertexdata* vptr = ((edgedata*)(iterator->data))->target;
			if(!vptr->mark){
				vptr->mark = true;
				generic_tree* leaf;
				generic_tree_init(&leaf, vptr);
				generic_tree_insert(current, leaf);
				generic_queue_enqueue(gq, leaf);
			}
		}
	}while(gq->head != NULL);
	generic_queue_free(&gq);
	return gt;
}

///Egy @c vroot csúcsból megkeresi minden másik csúcsba a legrövidebb utat. A gráf nem tartalmazhat negatív kört.
bool Ford(generic_linkedlist* v_head, vertexdata* vroot, generic_linkedlist** paths_ptr)
{
	for(generic_linkedlist* iterator = v_head; iterator; iterator = iterator->next)
	{
		vertexdata* vdata = (vertexdata*)(iterator->data);
		vdata->from = NULL;
		vdata->dist = INFINITY;
	}
	vroot->dist = 0;
	int n_total = generic_linkedlist_size(v_head);
	int i;
	bool relaxed;
	for(i = 0;i < n_total;i++) // ha nincs neg. kör, akkor max. |V|-1 -szer ismétlődik
	{
        relaxed = false;
		for(generic_linkedlist* v_iterator = v_head; v_iterator; v_iterator = v_iterator->next)
		{
			vertexdata* vdata = (vertexdata*)(v_iterator->data);
			for(generic_linkedlist* e_iterator = vdata->edgelist; e_iterator; e_iterator = e_iterator -> next)
			{
				edgedata* edata = (edgedata*)(e_iterator->data);
				vertexdata* vother = (vertexdata*)(edata->target);
				if(vdata->dist != INFINITY)
				{
					if(vdata->dist + edata->weight < vother->dist)
					{
						vother->dist = vdata->dist + edata->weight;
						vother->from = vdata;
						relaxed = true;
					}
				}
			}
		}
		if(!relaxed)
			break;
	}
	if(i == n_total)
	{
		return false;
	}
	generic_linkedlist* paths = NULL;
	for(generic_linkedlist* iterator = v_head; iterator; iterator = iterator->next)
	{
		vertexdata* vdata = (vertexdata*)(iterator->data);
		generic_linkedlist* path;
		generic_linkedlist_init(&path, vdata);
		while(vdata = vdata->from)
		{
			generic_linkedlist_insert(&path, vdata);
		}
		generic_linkedlist_reverse(&path);
		if(paths)
			generic_linkedlist_insert(&paths, path);
		else
			generic_linkedlist_init(&paths, path);
	}
	generic_linkedlist_reverse(&paths);
	*paths_ptr = paths;
	return true;
}

