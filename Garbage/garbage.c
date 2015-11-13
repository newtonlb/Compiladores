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
    while (!is_Pilha_Vazia(p))
    {
        pilha_remove(p);
    }
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


void mg_V2()
{
    int size = strlen(string);

    CELL* inicio = create_graph2(size);
    CELL* aux = inicio, *aux2, *aux3;
    int i;
    int reductible = 1;
    Pilha* pilha = create_pilha();
    pilha_insere(pilha, inicio);
    CELL* vetor[] = {NULL, NULL, NULL, NULL}, *a, *b, *c, *d, *op, *cauda, *f, *g, *x, *y, *par1, *par2;
    int counter = 0;
    while(reductible == 1)
    {
        if (is_Pilha_Vazia(pilha))
        {
            reductible = 0;
            break;
        }
        aux2 = get_topo_pilha(pilha);
        for(aux = aux2; aux != NULL; aux = aux->left)
        {
            if(aux != aux2)
            {
                 pilha_insere(pilha, aux);
            }

        }

        aux = get_topo_pilha(pilha);
       // printf("\n\n");
        switch (aux->type)
        {
        case 'K':
            if(pilha == NULL)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                pilha_remove(pilha); // Tirar o operador 'K'
                if (!is_Pilha_Vazia(pilha))
                {
                    a = get_topo_pilha(pilha); // Guarda o ponteiro de 'a'
                    pilha_remove(pilha);    // Retira o @ que guarda o 'a'

                    if(!is_Pilha_Vazia(pilha))
                     {
                        b = get_topo_pilha(pilha);  // o '@' que guarda o b
                        pilha_remove(pilha);

                        if(!is_Pilha_Vazia(pilha)) // Tem cauda, vai ter que mudar o ponteiro
                        {
                            c = get_topo_pilha(pilha);  // o '@' que guarda o c
                            pilha_remove(pilha);
                            c->left = a->right;
                            pilha_insere(pilha, c);
                        }
                        else   // Nao tem cauda
                        {
                            b->left = a->right;
                            b->right = NULL;
                            pilha_insere(pilha, b);
                        }

                     }
                }
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
            else
            {
                pilha_remove(pilha); //tira o operador

                if (!is_Pilha_Vazia(pilha))
                {
                    a = get_topo_pilha(pilha); // Guarda o ponteiro de 'a'
                    pilha_remove(pilha);    // Retira o @ que guarda o 'a'

                    if(!is_Pilha_Vazia(pilha))
                     {
                        b = get_topo_pilha(pilha);  // o '@' que guarda o b
                        pilha_remove(pilha);

                        if(!is_Pilha_Vazia(pilha))
                        {
                            c = get_topo_pilha(pilha);  // o '@' que guarda o c
                            pilha_remove(pilha);
                            a = create_CELL_parenthesis(a->right, c->right);
                            b = create_CELL_parenthesis(b->right, c->right);
                            c->left = a;
                            c->right = b;
                            if(!is_Pilha_Vazia(pilha)) // Tem cauda, vai ter que mudar o ponteiro
                            {
                                d = get_topo_pilha(pilha);
                                pilha_remove(pilha);
                                d->left = c;
                                pilha_insere(pilha, d);
                            }
                            else   // Nao tem cauda
                            {
                              pilha_insere(pilha, c);
                            }
                        }
                     }
                }


            }

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
            else
            {
                pilha_remove(pilha); //tira o operador
                if (!is_Pilha_Vazia(pilha))
                {
                     a = get_topo_pilha(pilha);  // o '@' que guarda o a
                     pilha_remove(pilha);

                     if(!is_Pilha_Vazia(pilha)) // Tem cauda, vai ter que mudar o ponteiro
                     {
                         b = get_topo_pilha(pilha);  // o '@' que guarda o b
                         pilha_remove(pilha);
                         b->left = a->right;
                         pilha_insere(pilha, b);
                     }
                     else   // Nao tem cauda
                     {
                         a->left = a->right;
                         a->right = NULL;
                         pilha_insere(pilha, a);
                     }
                }
            }

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
            else
            {
                pilha_remove(pilha); //tira o operador
                if (!is_Pilha_Vazia(pilha))
                {
                    f = get_topo_pilha(pilha); // Guarda o ponteiro de 'f'
                    pilha_remove(pilha);    // Retira o @ que guarda o 'f'

                    if(!is_Pilha_Vazia(pilha))
                     {
                        g = get_topo_pilha(pilha);  // o '@' que guarda o g
                        pilha_remove(pilha);

                        if(!is_Pilha_Vazia(pilha))
                        {
                            x = get_topo_pilha(pilha);  // o '@' que guarda o x
                            pilha_remove(pilha);
                            x->left = f->right;
                            x->right = create_CELL_parenthesis(g->right, x->right);


                            if(!is_Pilha_Vazia(pilha)) // Tem cauda, vai ter que mudar o ponteiro
                            {
                                cauda = get_topo_pilha(pilha);
                                pilha_remove(pilha);
                                cauda->left = x;
                                pilha_insere(pilha, cauda);
                            }
                            else   // Nao tem cauda
                            {
                                pilha_insere(pilha, x);
                            }
                        }
                     }
                }


            }
#ifdef COUNTERB
            contB++;
#endif
            break;

        case 'C': ///Funcionando para o caso base e o caso base com cauda, porem nao funciona com dois C seguidos
            if(pilha == NULL)
            {
                reductible = 0;
                break;
            }
            else
            {
                pilha_remove(pilha); //tira o operador
                if (!is_Pilha_Vazia(pilha))
                {
                    f = get_topo_pilha(pilha); // Guarda o ponteiro de 'f'
                    pilha_remove(pilha);    // Retira o @ que guarda o 'f'

                    if(!is_Pilha_Vazia(pilha))
                     {
                        x = get_topo_pilha(pilha);  // o '@' que guarda o x
                        pilha_remove(pilha);

                        if(!is_Pilha_Vazia(pilha))
                        {
                            y = get_topo_pilha(pilha);  // o '@' que guarda o y
                            pilha_remove(pilha);
                            f->left = f->right;
                            f->right = NULL;
                            aux2 = x->right;
                            x->right = y->right;
                            y->right = aux2;




                            if(!is_Pilha_Vazia(pilha)) // Tem cauda, vai ter que mudar o ponteiro
                            {
                                cauda = get_topo_pilha(pilha);
                                pilha_remove(pilha);
                                cauda->left = y;
                                pilha_insere(pilha, cauda);
                            }
                            else   // Nao tem cauda
                            {
                                pilha_insere(pilha, y);
                            }
                        }
                     }
                }
            }

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
            else
            {
                pilha_remove(pilha); //tira o operador

                if (!is_Pilha_Vazia(pilha))
                {
                    a = get_topo_pilha(pilha); // Guarda o ponteiro de 'a'
                    pilha_remove(pilha);    // Retira o @ que guarda o 'a'

                    if(!is_Pilha_Vazia(pilha))
                    {
                        b = get_topo_pilha(pilha);  // o '@' que guarda o b
                        pilha_remove(pilha);

                        if(!is_Pilha_Vazia(pilha))
                        {
                            c = get_topo_pilha(pilha);  // o '@' que guarda o c
                            pilha_remove(pilha);
                            if (!is_Pilha_Vazia(pilha))
                            {
                                d = get_topo_pilha(pilha);
                                pilha_remove(pilha);
                                a->left = a->right;
                                par1 = create_CELL_parenthesis(b->right, d->right);
                                par2 = create_CELL_parenthesis(c->right, d->right);
                                a->right = par1;
                                d->right = par2;
                                d->left = a;


                                if(!is_Pilha_Vazia(pilha)) // Tem cauda, vai ter que mudar o ponteiro
                                {
                                    cauda = get_topo_pilha(pilha);
                                    pilha_remove(pilha);
                                    cauda->left = d;
                                    pilha_insere(pilha, cauda);
                                }
                                else   // Nao tem cauda
                                {
                                    pilha_insere(pilha, d);
                                }
                            }

                        }
                    }
                }
            }
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
            else
            {
                pilha_remove(pilha); //tira o operador

                if (!is_Pilha_Vazia(pilha))
                {
                    a = get_topo_pilha(pilha); // Guarda o ponteiro de 'a'
                    pilha_remove(pilha);    // Retira o @ que guarda o 'a'

                    if(!is_Pilha_Vazia(pilha))
                    {
                        b = get_topo_pilha(pilha);  // o '@' que guarda o b
                        pilha_remove(pilha);

                        if(!is_Pilha_Vazia(pilha))
                        {
                            c = get_topo_pilha(pilha);  // o '@' que guarda o c
                            pilha_remove(pilha);
                            if (!is_Pilha_Vazia(pilha))
                            {
                                d = get_topo_pilha(pilha);
                                pilha_remove(pilha);

                                a->left = a->right;
                                a->right = b->right;
                                par1 = create_CELL_parenthesis(c->right, d->right);
                                d->right = par1;
                                d->left = a;


                                if(!is_Pilha_Vazia(pilha)) // Tem cauda, vai ter que mudar o ponteiro
                                {
                                    cauda = get_topo_pilha(pilha);
                                    pilha_remove(pilha);
                                    cauda->left = d;
                                    pilha_insere(pilha, cauda);
                                }
                                else   // Nao tem cauda
                                {
                                    pilha_insere(pilha, d);
                                }
                            }

                        }
                    }
                }
            }

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
            else
            {
                pilha_remove(pilha); //tira o operador

                if (!is_Pilha_Vazia(pilha))
                {
                    a = get_topo_pilha(pilha); // Guarda o ponteiro de 'a'
                    pilha_remove(pilha);    // Retira o @ que guarda o 'a'

                    if(!is_Pilha_Vazia(pilha))
                    {
                        b = get_topo_pilha(pilha);  // o '@' que guarda o b
                        pilha_remove(pilha);

                        if(!is_Pilha_Vazia(pilha))
                        {
                            c = get_topo_pilha(pilha);  // o '@' que guarda o c
                            pilha_remove(pilha);
                            if (!is_Pilha_Vazia(pilha))
                            {
                                d = get_topo_pilha(pilha);
                                pilha_remove(pilha);

                                a->left = a->right;
                                par1 = create_CELL_parenthesis(b->right, d->right);
                                a->right = par1;
                                d->left = a;
                                d->right = c->right;


                                if(!is_Pilha_Vazia(pilha)) // Tem cauda, vai ter que mudar o ponteiro
                                {
                                    cauda = get_topo_pilha(pilha);
                                    pilha_remove(pilha);
                                    cauda->left = d;
                                    pilha_insere(pilha, cauda);
                                }
                                else   // Nao tem cauda
                                {
                                    pilha_insere(pilha, d);
                                }
                            }

                        }
                    }
                }
            }
#ifdef COUNTERCLINHA
            contClinha++;
#endif
            break;

        default:
            reductible = 0;
            break;
        }



    }
    print_graph(inicio);
    printf("\n");
}

int main()
{
    mg_V2();


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
