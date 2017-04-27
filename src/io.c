// Fényes Balázs
// f.balazs96@gmail.com

/** @file
Terminál kezelése, bemenet/kimenet formázása.*/

#include <stdio.h>
#include <string.h>
#include "io.h"
#include "generics.h"
#include "data.h"

void setstyle(STYLE s)
{
	printf("\033[%dm", s+30);
}

void readline(char* buffer, size_t len)
{
	setstyle(INPUT);
	fgets(buffer, len, stdin);
}

char* trimend(char* s)
{
	int len = strlen(s) - 1;
	while(len >= 0 && (s[len] == ' ' || s[len] == '\t' || s[len] == '\n'))
	{
		s[len--] = 0;
	}
	return s;
}

vertexdata* read_vertex_name(generic_linkedlist* v_head, const char* str)
{
	do{
		printfs(TEXT, "\nVálasszon %s: ", str);
		for(generic_linkedlist* iterator = v_head; iterator; iterator = iterator->next)
		{
			printfs(TEXT, "%s%s", ((vertexdata*)(iterator->data))->name, iterator->next == NULL ?"\n":", ");
		}
		char buf[BUFLEN];
		readline(buf, BUFLEN);
		char* inp = trimend(buf);
		vertexdata* root = NULL;
		for(generic_linkedlist* iterator = v_head; iterator; iterator = iterator->next)
		{
			if(strcmp(inp, ((vertexdata*)(iterator->data))->name)==0)
			{
				root = (vertexdata*)(iterator->data);
				break;
			}
		}
		if(root != NULL)
		{
			return root;
		}
		else
		{
			printfs(ERROR,"Hibás csúcsnév!\n");
		}
	}while(true);
}
