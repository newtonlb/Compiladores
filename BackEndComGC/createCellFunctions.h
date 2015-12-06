/*
 * Create Cell Functions, this document provides functions to create cell
 * implemented in this project (Here is the implement of each funtion, 
 * the assign is in the Global Header File)
 */

#ifndef CREATECELLFUNCTIONS_H_
#define CREATECELLFUNCTIONS_H_

// Function to create a cell
CELL* create_CELL()
{
    lastPos++;
    heap[lastPos].memory = not_copied;
    heap[lastPos].left = NULL;
    heap[lastPos].right = NULL;
    return &heap[lastPos];
}

// Function to create a parenthesis cell
CELL* create_CELL_parenthesis(CELL* esq, CELL* dir)
{
    lastPos++;
    heap[lastPos].id = 'o';
    heap[lastPos].memory = not_copied;
    heap[lastPos].type.operador = '@';
    heap[lastPos].left = esq;
    heap[lastPos].right = dir;
    return &heap[lastPos];
}

// Function to create a leaf cell
CELL* create_CELL_leaf(char type)
{
    lastPos++;
    heap[lastPos].memory = not_copied;
    heap[lastPos].type.operador = type;
    heap[lastPos].left = NULL;
    heap[lastPos].right = NULL;
    heap[lastPos].id = 'o';
    return &heap[lastPos];
}

// Function to create a number cell
CELL* create_CELL_number(int type)
{
    lastPos++;
    heap[lastPos].memory = not_copied;
    heap[lastPos].type.number = type;
    heap[lastPos].left = NULL;
    heap[lastPos].right = NULL;
    heap[lastPos].id = 'n';
    return &heap[lastPos];
}

 #endif

