// Fényes Balázs
// f.balazs96@gmail.com

#ifndef _GENERIC_QUEUE_H
#define _GENERIC_QUEUE_H

#include <stdlib.h>
#include "io.h"
#include "generic_linkedlist.h"

///egy FIFO-sor a két végére mutató pointerrel
typedef struct {
	///a sor első eleme
	generic_linkedlist* head;
	///a sor utolsó eleme
	generic_linkedlist* tail;
} generic_queue;

///Új elem beszúrása a sor elejére.
void generic_queue_enqueue(generic_queue* gq, void* data);
///Új sor létrehozása egy elemmel.
void generic_queue_init(generic_queue** gqptr, void* data);
///A sor végén lévő elem törlése.
void* generic_queue_dequeue(generic_queue* gq);
///Az összes elem törlése.
void generic_queue_free(generic_queue** gq);

#endif
