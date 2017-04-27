// Fényes Balázs
// f.balazs96@gmail.com

#ifndef _GENERIC_TREE_H
#define _GENERIC_TREE_H

///fa, aminek tetszőleges számú leszármazott fája lehet
typedef struct generic_tree{
	///adatra mutató pointer
	void* data;
	///vele egy szinten lévő generic_tree-k
	struct generic_tree* children;
	///alatta lévő generic_tree-k
	struct generic_tree* siblings;
} generic_tree;

///Fa létrehozása egy adattal a gyökérben.
void generic_tree_init(generic_tree** gtptr, void* data);
///Fa és az összes leszármazott felszabadítása.
void generic_tree_free(generic_tree* gt, void (*freefunc)(void*));
///Fa mérete.
int generic_tree_size(generic_tree* gt);
void _gtprint(generic_tree* gt, void (*printfunc)(void*), int depth);
///Fa kiíratása.
void generic_tree_print(generic_tree* gt, void (*printfunc)(void*));
///Új elem beszúrása adott fa alá.
void generic_tree_insert(generic_tree* gt, generic_tree* leaf);

#endif
