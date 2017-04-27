// Fényes Balázs
// f.balazs96@gmail.com

#ifndef _IO_H
#define _IO_H

#include <stdio.h>
#include <string.h>
#include "generics.h"
#include "data.h"

///a terminálon használható néhány szín, az enumban az elemek sorrendje számít.
typedef enum { BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE } COLOR;
///ezeket a színeket használja a program
typedef enum { TEXT = CYAN, RESULT = GREEN, INPUT = YELLOW, DEBUG = MAGENTA, ERROR = RED } STYLE;

#define printfs(style,fmt,...) do{ setstyle(style); printf(fmt, ##__VA_ARGS__); } while(0)

#define BUFLEN 20

///kimenet színének beállítása
void setstyle(STYLE s);
///egész sor beolvasása
void readline(char* buffer, size_t len);
///sor végi whitespace karakterek levágása
char* trimend(char* s);
///csúcs megkeresése név alapján
vertexdata* read_vertex_name(generic_linkedlist* v_head, const char* str);

#endif
