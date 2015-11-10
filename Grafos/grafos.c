#include "grafos.h"



CELL* create_CELL()
{
	lastPos++;
    heap[lastPos].left = NULL;
    heap[lastPos].right = NULL;
    return &heap[lastPos];
}


CELL* create_CELL_parenthesis(CELL* esq, CELL* dir)
{
	lastPos++;
    heap[lastPos].type = '@';
    heap[lastPos].left = esq;
    heap[lastPos].right = dir;
    return &heap[lastPos];
}
CELL* create_CELL_leaf(char type)
{
	lastPos++;
    heap[lastPos].type = type;
    heap[lastPos].left = NULL;
    heap[lastPos].right = NULL;
    return &heap[lastPos];
}

Pilha* create_pilha()
{
    Pilha* pilha_nova = (Pilha*)malloc(sizeof(Pilha));
    pilha_nova->tamanho = 500;
    pilha_nova->cabeca_pilha = -1; //pilha vazia
    pilha_nova->celulas = (CELL**)malloc(sizeof(CELL*)*pilha_nova->tamanho); //alocando o espaco para 500 celulas

    return pilha_nova;
}

void pilha_insere(Pilha *p, CELL* celula)
{
    p->cabeca_pilha++;
    p->celulas[p->cabeca_pilha] = celula;
    if(p->cabeca_pilha + 1 == p->tamanho) //a pilha ta eminência de encher
    {
        p->tamanho += 100;
        p->celulas = (CELL**)realloc((CELL**)p->celulas, sizeof(CELL*)*p->tamanho); //realoca mais espaço pra caber mais celula na pilha
    }

}

CELL* get_topo_pilha(Pilha* p)
{
    return p->celulas[p->cabeca_pilha];
}

int is_Pilha_Vazia(Pilha* p)
{
    if(p->cabeca_pilha > -1)
    {
        return 0;
    }
    else
    {
        return 1; //ta vazia
    }
}

void pilha_remove(Pilha* p)
{
    if(is_Pilha_Vazia(p) == 0)
    {
        p->cabeca_pilha--;
    }
    //nao tem else porque se estiver vazia, n faz nada.
}

void free_pilha(Pilha* p)
{
    free(p->celulas);
    free(p);
}


int pos = 0;

CELL* create_graph2(int size)
{
    CELL* inicio = create_CELL_parenthesis(NULL, NULL);
    CELL* aux = NULL;
    while(pos < size)
    {
        if (string[pos] == ')')
        {
            pos++;
            return inicio;
        }
        else if (string[pos] == '(')
        {
            pos++;
            if(inicio->left == NULL)
                inicio->left = create_graph2(size);
            else if (inicio->right == NULL)
                inicio->right = create_graph2(size);
            else
            {
                aux = inicio;
                inicio = create_CELL_parenthesis(aux, create_graph2(size));
            }
        }
        else
        {
            if(inicio->left == NULL)
                inicio->left = create_CELL_leaf(string[pos]);
            else if(inicio->right == NULL)
                inicio->right = create_CELL_leaf(string[pos]);
            else
            {
                aux = inicio;
                inicio = create_CELL_parenthesis(aux, create_CELL_leaf(string[pos])); 
            }
            pos++;
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
    
    CELL* inicio = create_graph2(size);
    CELL* vetor[] = {NULL, NULL, NULL, NULL}; //para guardar os 4 nós anteriores ao operador
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
                #ifdef COUNTERK
                         contK++;
                    #endif
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
                
                #ifdef COUNTERS
                         contS++;
                    #endif
                break;
                
                
            case 'I':
                if(vetor[0] == NULL)
                {
                    reductible = 0;
                    break;
                }
                vetor[1]->left = vetor[0]->right;

                #ifdef COUNTERI
                         contI++;
                    #endif
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
                
                #ifdef COUNTERB
                         contB++;
                    #endif
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

                #ifdef COUNTERC
                         contC++;
                    #endif
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
                
                #ifdef COUNTERSLINHA
                         contSlinha++;
                    #endif
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

                #ifdef COUNTERBLINHA
                         contBlinha++;
                    #endif

                
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

                #ifdef COUNTERCLINHA
                         contClinha++;
                    #endif
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


void mg_V2()
{
    int size = strlen(string);

    CELL* inicio = create_graph2(size);
    CELL* aux = inicio;
    int i;
    int reductible = 1;
    Pilha* pilha = create_pilha();
    pilha_insere(pilha, inicio);
    CELL* vetor[] = {NULL, NULL, NULL, NULL};
    while(reductible == 1)
    {
        for(aux = get_topo_pilha(pilha); aux->left != NULL; aux = aux->left)
        {           

            if(aux->type == '@' && aux != get_topo_pilha(pilha))
            {
                pilha_insere(pilha, aux);
            }

        } 

         switch (aux->type)
            {
                case 'K':
                    if(pilha == NULL)
                    {
                        reductible = 0; // chegou ao fim
                        break;
                    }

                    for(i = 0; i < 2; i++)
                    {
                        if(!is_Pilha_Vazia(pilha))
                        {
                            vetor[i] = get_topo_pilha(pilha);
                            if(i != 1)
                            {
                                pilha_remove(pilha);
                            }
                        }
                        else
                        {
                            reductible = 0;
                            break;
                        }
                    }
                        if(vetor[1] != inicio)
                        {
                            if(is_Pilha_Vazia(pilha))
                            {
                                reductible = 0;
                                break;
                            }
                            pilha_remove(pilha);
                            vetor[2] = get_topo_pilha(pilha);
                            vetor[2]->left = vetor[0]->right;


                        }
                        else
                        {
                            vetor[1]->left = vetor[0]->right;
                            vetor[1]->right = NULL;
                        }
                    #ifdef COUNTERK
                             contK++;
                        #endif
                    break;

                case 'S':
                    if(pilha == NULL)
                    {
                        reductible = 0;
                        break;
                    }
                    for(i = 0; i < 3; i++)
                    {
                        if(!is_Pilha_Vazia(pilha))
                        {
                            vetor[i] = get_topo_pilha(pilha);
                            if(i != 2)
                            {
                                pilha_remove(pilha);
                            }
                        }
                        else
                        {
                            reductible = 0;
                            break;
                        }
               

                    }
                vetor[1]->left = vetor[0]->right; //colocando o a no lugar
                vetor[0]->left = vetor[1]->right; //montando o nó que vai ser o bc
                vetor[0]->right = vetor[2]->right; //aqui tbm (mais especificamente, o c)
                vetor[2]->right = vetor[0]; //colocando o no que é bc no lado direito da raiz
                vetor[1]->right = vetor[0]->right; //juntando, apontando o segundo c para o primeiro c
                
                    #ifdef COUNTERS
                             contS++;
                        #endif
                    break;


                case 'I':
                    if(pilha == NULL)
                    {
                        reductible = 0;
                        break;
                    }
                    if (!is_Pilha_Vazia(pilha))
                    {
                    	vetor[0] = get_topo_pilha(pilha);
                    	pilha_remove(pilha);
                    }
                    else
                    {
                    	reductible = 0;
                    	break;
                    }
                    vetor[1] = get_topo_pilha(pilha);
                   	vetor[1]->left = vetor[0]->right;

                    #ifdef COUNTERI
                             contI++;
                        #endif
                    break;

                case 'B':
                    if(pilha == NULL)
                    {
                        reductible = 0;
                        break;
                    }
                    for(i = 0; i < 3; i++)
                    {
                        if(!is_Pilha_Vazia(pilha))
                        {
                            vetor[i] = get_topo_pilha(pilha);
                            if(i != 2)
                            {
                                pilha_remove(pilha);
                            }
                        }
                        else
                        {
                            reductible = 0;
                            break;
                        }
                    }
               
                    vetor[1]->left = vetor[1]->right;
                    vetor[1]->right = vetor[2]->right;
                    vetor[2]->right = vetor[1];
                    vetor[2]->left = vetor[0]->right;
                    #ifdef COUNTERB
                             contB++;
                        #endif
                    break;

                case 'C':
                    if(pilha == NULL)
                    {
                        reductible = 0;
                        break;
                    }
                    for(i = 0; i < 3; i++)
                    {
                        if(!is_Pilha_Vazia(pilha))
                        {
                            vetor[i] = get_topo_pilha(pilha);
                            if(i != 2)
                            {
                                pilha_remove(pilha);
                            }
                        }
                        else
                        {
                            reductible = 0;
                            break;
                        }
                    }
                    
                    vetor[0]->left = vetor[0]->right;
                    vetor[0]->right = vetor[2]->right;
                    vetor[2]->right = vetor[1]->right;
                    vetor[2]->left = vetor[0];
                    
                    #ifdef COUNTERC
                             contC++;
                        #endif
                    break;

                case 's':
                    if(pilha == NULL)
                    {
                        reductible = 0;
                        break;
                    }
                    for(i = 0; i < 4; i++)
                    {
                        if(!is_Pilha_Vazia(pilha))
                        {
                            vetor[i] = get_topo_pilha(pilha);
                            if(i != 3)
                            {
                                pilha_remove(pilha);
                            }
                        }
                        else
                        {
                            reductible = 0;
                            break;
                        }
                    }
                    vetor[2]->left = vetor[0]->right; //a
                    vetor[0]->left = vetor[1]->right;
                    vetor[0]->right = vetor[3]->right;
                    vetor[1]->left = vetor[2]->right;
                    vetor[1]->right = vetor[3]->right;
                    vetor[2]->right = vetor[0]; //bd
                    vetor[3]->right = vetor[1]; //cd
                    #ifdef COUNTERSLINHA
                             contSlinha++;
                        #endif
                    break;

                case 'b':
                    if (pilha == NULL)
                    {
                        reductible = 0;
                        break;
                    }
                    for(i = 0; i < 4; i++)
                    {
                        if(!is_Pilha_Vazia(pilha))
                        {
                            vetor[i] = get_topo_pilha(pilha);
                            if(i != 3)
                            {
                                pilha_remove(pilha);
                            }
                        }
                        else
                        {
                            reductible = 0;
                            break;
                        }
                    }
                    
                    vetor[1]->left = vetor[0]->right;
                    vetor[2]->left = vetor[2]->right;
                    vetor[2]->right = vetor[3]->right;
                    vetor[3]->left = vetor[1];
                    vetor[3]->right = vetor[2];
                    
                    #ifdef COUNTERBLINHA
                             contBlinha++;
                        #endif


                    break;

                case 'c':
                    if(pilha == NULL)
                    {
                        reductible = 0;
                        break;
                    }
                    for(i = 0; i < 4; i++)
                    {
                        if(!is_Pilha_Vazia(pilha))
                        {
                            vetor[i] = get_topo_pilha(pilha);
                            if(i != 3)
                            {
                                pilha_remove(pilha);
                            }
                        }
                        else
                        {
                            reductible = 0;
                            break;
                        }
                    }
                    vetor[2]->left = vetor[0]->right;
                    vetor[0]->left = vetor[1]->right;
                    vetor[0]->right = vetor[3]->right;
                    vetor[3]->right = vetor[2]->right;
                    vetor[2]->right = vetor[0];
                    #ifdef COUNTERCLINHA
                             contClinha++;
                        #endif
                    break;

                default:
                    reductible = 0;
                    break;
            }
            /*
            for(i = 0; i< 4; i++)
            {
                vetor[i] = NULL;
            }
            */

        

    }
    print_graph(inicio);
    printf("\n");
}

int main()
{
    //print_graph(inicio);
    //mg_V1();
    mg_V2();

       //printf("DEVERIA TER REDUZIDO\n\n\n");

    #ifdef PRINTS
        printf("ContK = %d\n", contK);
        printf("ContS = %d\n", contS);
        printf("ContI = %d\n", contI);
        printf("ContB = %d\n", contB);
        printf("ContC = %d\n", contC);
        printf("ContSlinha = %d\n", contSlinha);
        printf("ContBlinha = %d\n", contBlinha);
        printf("ContClinha = %d\n", contClinha);
        printf("ContRemoveParenteses = %d\n", contRemoveParenteses);
        printf("Iterations = %d\n", iterations);
        printf("lastPos = %d\n", lastPos);
        #endif





    return 0;
}
