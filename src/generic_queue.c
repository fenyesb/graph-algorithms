// Fényes Balázs
// f.balazs96@gmail.com

/** @file
Generikus FIFO-sor. Olyan speciális láncolt lista, ahol az adatokat csak az elejére (head) lehet betenni (enqueue) és a végéről (tail) lehet kivenni (dequeue). A sor üres, ha head vagy tail NULL.
*/

#include <stdlib.h>
#include "io.h"
#include "generic_linkedlist.h"
#include "generic_queue.h"

void generic_queue_enqueue(generic_queue* gq, void* data)
{
	generic_linkedlist* elm;
	generic_linkedlist_init(&elm, data);
	if(gq->head == NULL){
		gq->head = elm;
		gq->tail = elm;
	}else{
		gq->head->next = elm;
		gq->head = elm;
	}
}

void generic_queue_init(generic_queue** gqptr, void* data)
{
	*gqptr = malloc(sizeof(generic_queue));
	(*gqptr)->head = NULL;
	(*gqptr)->tail = NULL;
	generic_queue_enqueue(*gqptr, data);
}

void* generic_queue_dequeue(generic_queue* gq)
{
	generic_linkedlist* elm = gq->tail;
	void* data = elm->data;
	if(gq->tail == gq->head)
		gq->head = NULL;
	gq->tail = gq->tail->next;
	free(elm);
	return data;
}

void generic_queue_free(generic_queue** gq)
{
	while((*gq)->head)
		generic_queue_dequeue(*gq);
	free(*gq);
	*gq = NULL;
}
