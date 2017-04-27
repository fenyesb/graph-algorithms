// Fényes Balázs
// f.balazs96@gmail.com

#ifndef _GENERIC_LINKEDLIST_H
#define _GENERIC_LINKEDLIST_H

#include <stdlib.h>
#include "io.h"

///a láncolt lista egy eleme
typedef struct generic_linkedlist{
	///a láncolt lista következő eleme
	struct generic_linkedlist* next;
	///az adatra mutató pointer
	void* data;
} generic_linkedlist;

///Új lista létrehozása egy elemmel.
void generic_linkedlist_init(generic_linkedlist** gllptr, void* data);
///A lista elemeinek kiírása.
void generic_linkedlist_print(generic_linkedlist* gll, void (*printfunc)(void*), const char* separator);
///Új elem beszúrása.
void generic_linkedlist_insert(generic_linkedlist** gll, void* element);
///A lista megfordítása.
void generic_linkedlist_reverse(generic_linkedlist** gll);
///A listaelemek összegzése valamilyen függvény szerint.
int generic_linkedlist_sum(generic_linkedlist* gll, int (*sumfunc)(void*));
int _listsize(void* dataptr);
///A lista mérete.
int generic_linkedlist_size(generic_linkedlist* gll);
///A lista és listaelemek törlése.
void generic_linkedlist_free(generic_linkedlist** gll, void (*freefunc)(void*));
///Adott indexű elem kiolvasása.
void* generic_linkedlist_get(generic_linkedlist* gll, int index);

#endif
