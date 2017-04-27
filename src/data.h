// Fényes Balázs
// f.balazs96@gmail.com

#ifndef _DATA_H
#define _DATA_H

#include <limits.h>
#include <stdbool.h>

#define INFINITY INT_MAX

///egy él adatait tároló struktúra
typedef struct edgedata{
	///az él súlya
	int weight;
	///melyik csúcsra mutat az él
	struct vertexdata* target;
} edgedata;

///egy csúcs adatait tároló struktúra
typedef struct vertexdata{
	///a csúcs valódi neve
	char* name;
	///a csúcsból kiinduló élek listája
	struct generic_linkedlist* edgelist;
	///az adott algoritmusban meglátogattuk-e már ezt a csúcsot
	bool mark;
	///az adott algoritmus által számított távolság a gyökértől
	int dist;
	///az adott algoritmusban melyik csúcsból jutottunk ide
	struct vertexdata* from;
} vertexdata;

#endif
