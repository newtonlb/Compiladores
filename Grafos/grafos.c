#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 8000 // We will define later

typedef struct cell
{
  char type;
  char memory;
  CELL* left;
  CELL* right;
}CELL;

CELL* create_cell()
{
    CELL* novo = (CELL*) malloc(sizeof(CELL));
    novo->left = NULL;
    novo->right = NULL;
    return novo;
}

int main()
{






    return 0;
}
