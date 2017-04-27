// Fényes Balázs
// f.balazs96@gmail.com

/** @file
Egy generikus fa. A fa minden csúcsának tetszőleges számú leszármazottja lehet. Az üres fa értéke NULL.
*/

#include <stdlib.h>
#include "io.h"
#include "generic_tree.h"

void generic_tree_init(generic_tree** gtptr, void* data)
{
	*gtptr = malloc(sizeof(generic_tree));
	(*gtptr)->children = NULL;
	(*gtptr)->siblings = NULL;
	(*gtptr)->data = data;
}

void generic_tree_free(generic_tree* gt, void (*freefunc)(void*))
{
	if(gt==NULL)
		return;
	if(gt->children != NULL)
		generic_tree_free(gt->children, freefunc);
	if(gt->siblings != NULL)
		generic_tree_free(gt->siblings, freefunc);
	if(freefunc)
		freefunc(gt->data);
	free(gt);
}

int generic_tree_size(generic_tree* gt)
{
	if(gt==NULL)
		return 0;
	int n_siblings = gt->siblings != NULL ? generic_tree_size(gt->siblings) + 1 : 0;
	int n_children = gt->children != NULL ? generic_tree_size(gt->children) + 1 : 0;
	return n_siblings + n_children;
}

void generic_tree_print(generic_tree* gt, void (*printfunc)(void*))
{
	_gtprint(gt, printfunc, 0);
}

void _gtprint(generic_tree* gt, void (*printfunc)(void*), int depth)
{
	if(gt==NULL)
		return;
	for(int i = 0; i < depth; i++)
		printfs(RESULT, " ");
	printfunc(gt->data);
	printfs(RESULT, "\n");
	if(gt->children != NULL)
		_gtprint(gt->children, printfunc, depth+1);
	if(gt->siblings != NULL)
		_gtprint(gt->siblings, printfunc, depth);
}

void generic_tree_insert(generic_tree* gt, generic_tree* leaf)
{
	if(gt->children == NULL)
	{
		gt->children = leaf;
	}
	else
	{
		leaf->siblings = gt->children->siblings;
		gt->children->siblings = leaf;
	}
}
