/*
 * Stack Functions, this document provides functions to use the Stack
 * implemented in this project (Here is the implement of each funtion, 
 * the assign is in the Global Header File)
 */

#ifndef STACKFUNCTIONS_H_
#define STACKFUNCTIONS_H_

// Function to create Stack - This will be change to a global static declaration
Pilha* create_pilha()
{
    Pilha* pilha_nova = (Pilha*)malloc(sizeof(Pilha));
    pilha_nova->tamanho = 500;
    pilha_nova->cabeca_pilha = -1; //pilha vazia
    pilha_nova->celulas = (CELL**)malloc(sizeof(CELL*)*pilha_nova->tamanho); //alocando o espaco para 500 celulas

    return pilha_nova;
}

// Function to get the top of the Stack
CELL* get_topo_pilha(Pilha* p)
{
    return p->celulas[p->cabeca_pilha];
}

// Function to check if the stack is empty or not
int is_Pilha_Vazia(Pilha* p)
{
    if(p->cabeca_pilha > -1)
    {
        return 0; // Is not empty
    }
    else
    {
        return 1; // Is empty
    }
}

// Function to insert an element in the stack
void pilha_insere(Pilha *p, CELL* celula)
{
    p->cabeca_pilha++;
    p->celulas[p->cabeca_pilha] = celula;
    if(p->cabeca_pilha + 1 == p->tamanho) // Stack is closer to get full 
    {
        p->tamanho += 100;
        p->celulas = (CELL**)realloc((CELL**)p->celulas, sizeof(CELL*)*p->tamanho); // Realloc more space to the Stack
    }

}

// Function to remove an element of the stack
void pilha_remove(Pilha* p)
{
    if(is_Pilha_Vazia(p) == 0)
    {

        p->cabeca_pilha--;
    }
    // If it's empty it does nothing.
}


// Function to free each element of the stack
void free_pilha(Pilha* p)
{
    while (!is_Pilha_Vazia(p))
    {
        pilha_remove(p);
    }
}


 #endif

