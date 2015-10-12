#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct lista{
	struct lista *next;
	char c;
}Lista;

Lista criaLista()
{
	Lista *p;
	p = (Lista*)malloc(sizeof(Lista));
	return p;
}