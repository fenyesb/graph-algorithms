// Fényes Balázs
// f.balazs96@gmail.com

/** @file
Ez a fájl tartalmazza a főprogramot.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <ctype.h>

#include "io.h"
#include "generics.h"
#include "data.h"
#include "algorithms.h"

//az alábbiak függvénypointerként kerülnek átadásra

void vertexnameprint(void* dataptr)
{
	printfs(RESULT, "%s", ((vertexdata*)dataptr)->name);
}

void vertexprint(void* dataptr)
{
	vertexdata* vert = (vertexdata*)dataptr;
	printfs(RESULT, "%s(", vert->name);
	if(vert->dist == INFINITY)
		printfs(RESULT, "INFINITY)");
	else
		printfs(RESULT, "%d)", vert->dist);
}

void elistfree(void* dataptr)
{
	edgedata* edata = (edgedata*)dataptr;
	free(edata);
}

void vlistfree(void* dataptr)
{
	vertexdata* vdata = (vertexdata*)dataptr;
	free(vdata->name);
	generic_linkedlist_free(&(vdata->edgelist), elistfree);
	free(vdata);
}

int countedges(void* dataptr)
{
	return generic_linkedlist_size(((vertexdata*)dataptr)->edgelist);
}

void pathprint(void* dataptr)
{
	generic_linkedlist_print((generic_linkedlist*)dataptr, vertexprint, " <-- ");
}

void pathlistfree(void* dataptr)
{
	generic_linkedlist_free(dataptr, NULL);
	free(dataptr);
}

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "hu-HU");
	FILE* fv;
	FILE* fe;
	int directed = -1;
	for(int i = 0; i<argc;i++)
	{
		if(argv[i][0]=='-'&&i+1<argc)
		{
			switch(argv[i++][1]){
				case 'v':
					fv = fopen(argv[i],"r");
					break;
				case 'e':
					fe = fopen(argv[i],"r");
					break;
				case 'd':
					directed = argv[i][0]-'0';
					break;
				default:
					printfs(ERROR,"Ismeretlen parancssori argumentum: %s\n", argv[i-1]);
					return 0;
					break;
			}
		}
	}
	if(!(fe&&fv))
	{
		printfs(ERROR,"Hibás bemeneti fajlok!\n");
		return 0;
	}
	if(!(directed == 0 || directed == 1))
	{
		printfs(ERROR,"Meg kell adnia, hogy a gráf rendezett-e!\n");
		return 0;
	}
	generic_linkedlist* v_head = NULL;
	char buf[BUFLEN];
	while(fscanf(fv,"%s",buf)!=EOF){
		vertexdata* vdata = malloc(sizeof(vertexdata));
		vdata->name = malloc(BUFLEN);
		strcpy(vdata->name, buf);
		vdata->edgelist = NULL;
		generic_linkedlist_insert(&v_head, vdata);
	}
	fclose(fv);
	generic_linkedlist_reverse(&v_head);
	int from, to, weight;
	while(fscanf(fe, "%d%d%d", &from, &to, &weight)!=EOF)
	{
		for(int i = 0; i < (directed ? 1 : 2); i++)
		{
			edgedata* edata = malloc(sizeof(edgedata));
			edata->weight = weight;
			edata->target = (vertexdata*)generic_linkedlist_get(v_head, i == 0 ? to : from);
			vertexdata* parent = (vertexdata*)generic_linkedlist_get(v_head, i == 0 ? from : to);
			generic_linkedlist_insert(&(parent->edgelist), edata);
		}
	}
	for(;;)
	{
		printfs(TEXT, "\nVálasszon a lehetőségek közül:\n"
		" 1. Statisztikák a gráfról\n"
		" 2. Összefüggőség vizsgálata (irányítatlan gráf esetén)\n"
		" 3. BFS\n"
		" 4. DFS\n"
		" 5. Dijkstra\n"
		" 6. Ford\n");
		readline(buf, BUFLEN);
		if(buf[0]<'0'||buf[0]>'9')
			break;
		int user = atoi(buf);
		switch(user)
		{
			case 1:
				printfs(RESULT,"\ncsúcsok száma: %d\nélek száma: %d\n", generic_linkedlist_size(v_head), generic_linkedlist_sum(v_head, countedges)/(1+!directed));
				break;
			case 2:
				if(directed)
				{
					printfs(ERROR,"\nÖsszefüggőség csak irányítatlan gráf esetén vizsgálható!\n");
				}else{
					generic_tree* gt = BFS(v_head, v_head->data);
					int size = generic_tree_size(gt)+1;
					printfs(RESULT,"\nA gráf %sösszefüggő\n", size == generic_linkedlist_size(v_head) ? "" : "nem ");
					generic_tree_free(gt, NULL);
				}
				break;
			case 3:
				{
					generic_tree* gt = BFS(v_head, read_vertex_name(v_head, "gyökércsúcsot"));
					printfs(TEXT, "\n");
					generic_tree_print(gt, vertexnameprint);
					generic_tree_free(gt, NULL);
				}
				break;
			case 4:
				{
					generic_tree* gt = DFS(v_head, read_vertex_name(v_head, "gyökércsúcsot"));
					printfs(TEXT, "\n");
					generic_tree_print(gt, vertexnameprint);
					generic_tree_free(gt, NULL);
				}
				break;
			case 5:
				{
					vertexdata* vroot = read_vertex_name(v_head, "gyökércsúcsot");
					vertexdata* vgoal = read_vertex_name(v_head, "célcsúcsot");
					printfs(TEXT, "\n");
					generic_linkedlist* path;
					if(Dijkstra(v_head, vroot, vgoal, &path))
					{
						generic_linkedlist_print(path, vertexprint, " --> ");
						generic_linkedlist_free(&path, NULL);
					}else{
						printfs(ERROR,"Nem található út vagy a gráf negatív súlyú élet tartalmaz!\n");
					}
				}
				break;
			case 6:
				{
					vertexdata* vroot = read_vertex_name(v_head, "gyökércsúcsot");
					printfs(TEXT, "\n");
					generic_linkedlist* paths;
					if(Ford(v_head, vroot, &paths))
					{
						generic_linkedlist_print(paths, pathprint, "\n");
					}else{
						printfs(ERROR, "A gráf tartalmaz negatív kört!\n");
					}
					generic_linkedlist_free(&paths, pathlistfree);
				}
				break;
			default:
				printfs(ERROR,"\nHibás választás!\n");
				break;
		}
	}
	generic_linkedlist_free(&v_head, vlistfree);
	return 0;
}
