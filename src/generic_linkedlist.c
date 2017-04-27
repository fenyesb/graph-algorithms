// Fényes Balázs
// f.balazs96@gmail.com

/** @file
Egy tetszőleges adatot tárolni képes láncolt lista, ami egy irányban láncolt és nem tartalmaz strázsát. A lista végét NULL jelöli. Az üres lista értéke NULL. */

#include <stdlib.h>
#include "io.h"
#include "generic_linkedlist.h"

void generic_linkedlist_init(generic_linkedlist** gllptr, void* data)
{
	*gllptr = malloc(sizeof(generic_linkedlist));
	(*gllptr)->next = NULL;
	(*gllptr)->data = data;
}

void generic_linkedlist_print(generic_linkedlist* gll, void (*printfunc)(void*), const char* separator)
{
	if(gll != NULL)
	{
		printfunc(gll->data);
		printfs(RESULT, "%s", gll->next == NULL ? "\n" : separator);
		generic_linkedlist_print(gll->next, printfunc, separator);
	}
}

void generic_linkedlist_insert(generic_linkedlist** gll, void* data)
{
	generic_linkedlist* element;
	generic_linkedlist_init(&element, data);
	element->next = *gll;
	*gll = element;
}

void generic_linkedlist_reverse(generic_linkedlist** gll)
{
    generic_linkedlist* current = *gll;
    generic_linkedlist* next;
    *gll = NULL;
    while (current != NULL) {
    	next = current->next;
        current->next = *gll;
        *gll = current;
        current = next;
    }
}

int generic_linkedlist_sum(generic_linkedlist* gll, int (*sumfunc)(void*))
{
	return gll != NULL ? sumfunc(gll->data) + generic_linkedlist_sum(gll->next, sumfunc) : 0;
}

int _listsize(void* dataptr)
{
	return 1;
}

int generic_linkedlist_size(generic_linkedlist* gll)
{
	return generic_linkedlist_sum(gll, _listsize);
}

void generic_linkedlist_free(generic_linkedlist** gll, void (*freefunc)(void*))
{
	if(*gll != NULL)
	{
		generic_linkedlist_free(&((*gll)->next), freefunc);
		if(freefunc)
			freefunc((*gll)->data);
		free(*gll);
	}
	gll = NULL;
}

void* generic_linkedlist_get(generic_linkedlist* gll, int index)
{
	return index == 0 ? gll->data : generic_linkedlist_get(gll->next, index-1);
}
