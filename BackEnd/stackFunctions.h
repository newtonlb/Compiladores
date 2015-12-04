/*
 * Stack Functions, this document provides functions to use the Stack
 * implemented in this project (Here is the implement of each funtion, 
 * the assign is in the Global Header File)
 */

#ifndef STACKFUNCTIONS_H_
#define STACKFUNCTIONS_H_

// Function to insert an element in the Stack 
void pilha_insere(Pilha* p, CELL* celula)
{
    p[pilhaPos].celula = celula;
    pilhaPos++;
}

// Function to get the top of the Stack
CELL* get_topo_pilha(Pilha* p)
{
    return p[pilhaPos - 1].celula;
}

// Function to check if the stack is empty or not
int is_Pilha_Vazia(Pilha* p)
{
    if(pilhaPos > 0 && p[pilhaPos - 1].celula != NULL)
    {
        return 0;
    }
    else
    {
        return 1; //ta vazia
    }
}

// Function to remove an element of the stack
void pilha_remove(Pilha* p)
{
    if (pilhaPos - 1 > -1)
    {
        p[pilhaPos].celula = NULL;
        pilhaPos--;
    } // Nao tem else porque se estiver vazia, n faz nada.
}


// Function to free each element of the stack
void free_pilha(Pilha* p)
{
    while(!is_Pilha_Vazia(p))
        pilha_remove(p);
}



 #endif

