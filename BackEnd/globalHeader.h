/*
 * Global Header that contains macro definitions,
 * functions definition and declaration of structs
 */

#ifndef GLOBALHEADER_H_
#define GLOBALHEADER_H_

// Define das bibliotecas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

 // Define input string lib
 #include "inputString.h"

// Heap Size
#define HEAP_SIZE 50000000 
#define HEAP_HALF_SIZE (HEAP_SIZE)/2

#define MACROS

#ifdef MACROS
// Define Macros
#define COUNTERK
#define COUNTERS
#define COUNTERI
#define COUNTERB
#define COUNTERC
#define COUNTERSLINHA
#define COUNTERBLINHA
#define COUNTERCLINHA
#define COUNTERREMOVEPARENTESES
#define ITERATIONS
#define COUNTERKLINHA
#define COUNTERSOMA
#define COUNTERSUB
#define COUNTERMULT
#define COUNTERDIV
#define COUNTERIGUAL
#define COUNTERMENOR
#define COUNTERMAIOR
#define COUNTERY
#define PRINTS

// Set all counter to zero
int contK = 0;
int contS = 0;
int contI = 0;
int contB = 0;
int contC = 0;
int contSlinha = 0;
int contBlinha = 0;
int contClinha = 0;
int contKlinha = 0;
int contSoma = 0;
int contSub = 0;
int contMult = 0;
int contDiv = 0;
int contIgual = 0;
int contMenor = 0;
int contMaior = 0;
int contY = 0;
int contRemoveParenteses = 0;
int iterations = 0;

#endif // MACROS


// Type Union to represent the Element (OP or Number)
typedef union type_union
{
	char operador;
	int number;
}elemento;

// CELL Struct
typedef struct CELL
{
    elemento type;
    char id;
    char memory;
    struct CELL* left;
    struct CELL* right;
}CELL;

// Stack Struct
typedef struct pilha
{
	CELL* celula;
}Pilha;

// Const Char to indicate copied or not in GC Cheney
const char copied = 0xFF;
const char not_copied = 0x00;

// Global Variables
int pos = 0;
int redutible = 0;
int globalReductible = 1;
int lastPos = -1;
int heapUsado = 0;
int pilhaPos = 0;
int garbage = 0;
CELL heap[HEAP_SIZE];
CELL* raizGlobal;
Pilha pilha[HEAP_SIZE];


CELL* vetor[] = {NULL, NULL, NULL, NULL}, *a, *b, *c, *d, *op, *cauda, *f, *g, *x, *y, *par1, *par2;
CELL* aux, *aux2, *aux3, *aux4, *aux5;

/// Functions to create Cell
CELL* create_CELL();
CELL* create_CELL_parenthesis(CELL* esq, CELL* dir);
CELL* create_CELL_leaf(char type);
CELL* create_CELL_number(int type);

// Functions to create and print Graph
CELL* create_graph(int size);
void print_graph(CELL* inicio);

// Functions to manipulate and create stack
void pilha_insere(Pilha* p, CELL* celula);
CELL* get_topo_pilha(Pilha* p);
int is_Pilha_Vazia(Pilha* p);
void pilha_remove(Pilha* p);
void free_pilha(Pilha* p);

// Functions to reduct
CELL* reduct(CELL* inicio);

// Functions to gcCheney
void copy_cell(CELL *dest, CELL *src);
void GC_cheney(CELL *root, CELL *dest);


#endif
