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
void mg_V1()
{
    int size = strlen(string);
    
    CELL* inicio = create_graph(0, size, string);
    CELL* vetor[] = {NULL, NULL, NULL, NULL}; //para guardar os 3 nós anteriores ao operador
    CELL* aux = inicio;
    int i;
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
                
            case 'S':
                if(vetor[2] == NULL)
                {
                    reductible = 0;
                    break;
                }
                vetor[1]->left = vetor[0]->right; //colocando o a no lugar
                vetor[0]->left = vetor[1]->right; //montando o nó que vai ser o bc
                vetor[0]->right = vetor[2]->right; //aqui tbm (mais especificamente, o c)
                vetor[2]->right = vetor[0]; //colocando o no que é bc no lado direito da raiz
                vetor[1]->right = vetor[0]->right; //juntando, apontando o segundo c para o primeiro c
                
                break;
                
                
            case 'I':
                if(vetor[0] == NULL)
                {
                    reductible = 0;
                    break;
                }
                vetor[1]->left = vetor[0]->right;
                break;
                
            case 'B':
                if(vetor[2] == NULL)
                {
                    reductible = 0;
                    break;
                }
                vetor[1]->left = vetor[1]->right;
                vetor[1]->right = vetor[2]->right;
                vetor[2]->right = vetor[1];
                vetor[2]->left = vetor[0]->right;
                
                break;
                
            case 'C':
                if(vetor[2] == NULL)
                {
                    reductible = 0;
                    break;
                }
                vetor[0]->left = vetor[0]->right;
                vetor[0]->right = vetor[2]->right;
                vetor[2]->right = vetor[1]->right;
                vetor[2]->left = vetor[0];
                break;
                
            case 's':
                if(vetor[3] == NULL)
                {
                    reductible = 0;
                    break;
                }
                
                vetor[2]->left = vetor[0]->right; //a
                vetor[0]->left = vetor[1]->right;
                vetor[0]->right = vetor[3]->right;
                vetor[1]->left = vetor[2]->right;
                vetor[1]->right = vetor[3]->right;
                vetor[2]->right = vetor[0]; //bd
                vetor[3]->right = vetor[1]; //cd
                
                break;
                
            case 'b':
                if (vetor[3] == NULL)
                {
                    reductible = 0;
                    break;
                }
                vetor[1]->left = vetor[0]->right;
                vetor[2]->left = vetor[2]->right;
                vetor[2]->right = vetor[3]->right;
                vetor[3]->left = vetor[1];
                vetor[3]->right = vetor[2];
                
                break;
                
            case 'c':
                if(vetor[3] == NULL)
                {
                    reductible = 0;
                    break;
                }
                
                vetor[2]->left = vetor[0]->right;
                vetor[0]->left = vetor[1]->right;
                vetor[0]->right = vetor[3]->right;
                vetor[3]->right = vetor[2]->right;
                vetor[2]->right = vetor[0];
                break;
                
            default:
                reductible = 0;
                break;
        }
        for(i = 0; i< 4; i++)
        {
            vetor[i] = NULL;
        }
        
        
    }
    print_graph(inicio);
    printf("\n");
}


int main()
{
    
    //print_graph(inicio);
    mg_V1();
    
       //printf("DEVERIA TER REDUZIDO\N\N\N\N\N");
  
    
    
    
    
    
    
    return 0;
}
