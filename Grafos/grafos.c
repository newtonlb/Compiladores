#include "grafos.h"

CELL* create_cell()
{
    CELL* novo = (CELL*) malloc(sizeof(CELL));
    novo->left = NULL;
    novo->right = NULL;
    return novo;
}



CELL* create_cell_parenthesis(CELL* esq, CELL* dir)
{
    CELL* novo = (CELL*) malloc(sizeof(CELL));
    novo->type = '@';
    novo->left = esq;
    novo->right = dir;
    return novo;
}
CELL* create_cell_leaf(char type)
{
    CELL* novo = (CELL*) malloc(sizeof(CELL));
    novo->type = type;
    novo->left = NULL;
    novo->right = NULL;
    return novo;
}

int searchParenthesis(int initPos, char* string)
{
    int i = 0;
    int lvl = 0;
    int removed = 0;
    
    if(string[initPos] == '(')
    {
        lvl = 1;
        i = initPos;
        
        while (removed == 0)
        {
            i++;
            if(string[i] == '(')
            {
                lvl++;
            }
            else if(string[i] == ')')
            {
                lvl--;
                if(lvl == 0)
                {
                    removed = 1;
                }
            }
        }
        
    }
    return i;
}

CELL* create_graph(int i, int j, char* str)
{
    int k = 0;
    CELL* inicio = create_cell_parenthesis(NULL, NULL);
    CELL* aux = NULL;
    for (k = i; k <= j && string[k] != ')' ; k++)
    {
        if(string[k] == '(')
        {
            int novoj;
            novoj = searchParenthesis(k, string);
            if(inicio->left == NULL)
            {
                inicio->left = create_graph(k + 1, novoj - 1, string);
                k = novoj;
            }
            else if(inicio->right == NULL)
            {
                inicio->right = create_graph(k+1, novoj - 1, string);
                k = novoj;
            }
            
            else
            {
                aux = inicio;
                inicio = create_cell_parenthesis(aux, create_graph(k+1, novoj - 1, string));
                k = novoj;
            }
        }
        else
        {
            if(inicio->left == NULL)
            {
                inicio->left = create_cell_leaf(string[k]);
               
            }
            else if(inicio->right == NULL)
            {
                inicio->right = create_cell_leaf(string[k]);
            }
            else
            {
                aux = inicio;
                inicio = create_cell_parenthesis(aux, create_cell_leaf(string[k]));
            }
        }
    }
    return inicio;
}

void print_graph(CELL* inicio)
{
    if(inicio->type == '@')
    {
        if(inicio->left != NULL)
        {
            print_graph(inicio->left);
        }
        if(inicio->right != NULL)
        {
            if(inicio->right->type == '@')
            {
                printf("(");
            }
            print_graph(inicio->right);
            if(inicio->right->type == '@')
            {
                printf(")");
            }
        }
    }
    else
    {
        printf("%c",inicio->type);
    }
}



int main()
{
    int size = strlen(string);
    
    CELL* inicio = create_graph(0, size, string);
    print_graph(inicio);
    printf("\n");
    CELL* vetor[] = {NULL, NULL, NULL, NULL}; //para guardar os 3 nós anteriores ao operador
    CELL* aux = inicio;
    int reductible = 1;
    
    while(reductible == 1)
    {
        for(aux = inicio; aux->left != NULL; aux = aux->left)
        {
            vetor[3] = vetor[2];
            vetor[2] = vetor[1];
            vetor[1] = vetor[0];
            vetor[0] = aux;
        } //para pegar os 3 nós anteriores quando desce no grafo
        switch (aux->type)
        {
            case 'K':
                if(vetor[1] == NULL)
                {
                    reductible = 0; // chegou ao fim
                    break;
                }
                if (vetor[1] != inicio) //se o nó for diferente de raiz, faz logo o filho de cima apontar pro a
                {
                    vetor[2]->left = vetor[0]->right;
                }
                else
                {
                    vetor[1]->left = vetor[0]->right;
                    vetor[1]->right = NULL;
                }
                break;
                
                
                
                
                
            default:
                reductible = 0;
                break;
        }

        
    }
    print_graph(inicio);
    printf("\n");
    
    
    
    
    
    
    return 0;
}
