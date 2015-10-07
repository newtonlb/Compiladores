#ifndef LISTA_H_
#define LISTA_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MACROS

#ifdef MACROS
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
    //#define PRINTS

    #ifdef COUNTERK
           int contK = 0;
    #endif

    #ifdef COUNTERS
           int contS = 0;
    #endif

    #ifdef COUNTERI
           int contI = 0;
    #endif

    #ifdef COUNTERB
           int contB = 0;
    #endif

    #ifdef COUNTERC
            int contC = 0;
    #endif

    #ifdef COUNTERSLINHA
            int contSlinha = 0;
    #endif

    #ifdef COUNTERBLINHA
          int contBlinha = 0;
    #endif

    #ifdef COUNTERCLINHA
           int contClinha = 0;
    #endif

    #ifdef COUNTERREMOVEPARENTESES
           int contRemoveParenteses = 0;
    #endif

    #ifdef ITERATIONS
           int iterations = 0;
    #endif

#endif // MACROS


// Node Struct
typedef struct node
{
	char caract;
	struct node *next;
	struct node *down;
} NODE;


// Global var to indicate redutible
int redutible = 0;

/// Functions
NODE* new_node();
int searchParenthesis(int initPos, char* string);
void insertCaractToNode(char entrada, NODE* no);
NODE* create_list(int i, int j, char* string);
void imprime(NODE* no);
NODE* retiraParenteses(NODE* inicio);
void freeRecursao(NODE* inicio);

// Substitutions
NODE* substitution_K(NODE* inicio);
NODE* substitution_S(NODE* inicio);
NODE* substitution_I(NODE* inicio);
NODE* substitution_B(NODE* inicio);
NODE* substitution_C(NODE* inicio);
NODE* substitution_s(NODE* inicio);
NODE* substitution_b(NODE* inicio);
NODE* substitution_c(NODE* inicio);


// Initial Input String
//char *string = "S(S(S(KS)(S(KK)(SKK)))(K(S(SKK)(SKK))))(S(S(KS)(S(KK)(SKK)))(K(S(SKK)(SKK))))((S(S(S(KS)(S(KK)(SKK)))(K(S(SKK)(SKK))))(S(S(KS)(S(KK)(SKK)))(K(S(SKK)(SKK))))(KK))K)";
//char *string = "S(XXX)(YYY)(ZZ(Z)Z)(DDD)";
char *string = "S(X(X)(XX(Z))(XX))(YY(Y))((Z)ZZ)(XXX)";


#endif
