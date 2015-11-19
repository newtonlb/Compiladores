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
    heap[lastPos].type.operador = '@';
    heap[lastPos].left = esq;
    heap[lastPos].right = dir;
    return &heap[lastPos];
}
CELL* create_CELL_leaf(char type)
{
    lastPos++;
    heap[lastPos].type.operador = type;
    heap[lastPos].left = NULL;
    heap[lastPos].right = NULL;
    heap[lastPos].id = 'o';
    return &heap[lastPos];
}

CELL* create_CELL_number(int type)
{
    lastPos++;
    heap[lastPos].type.number = type;
    heap[lastPos].left = NULL;
    heap[lastPos].right = NULL;
    heap[lastPos].id = 'n';
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
        else if(string[pos] == '$')
        {
            //$$
            //$121312323$
            pos++;

            char stringAux[50];
            int contadorAux = 0;
            int number;
            while(string[pos] != '$')
            {

               stringAux[contadorAux] = string[pos];
               contadorAux++;
               pos++;
            }
            pos++;
            number = atoi(stringAux);
            while(contadorAux >= 0)
            {
                stringAux[contadorAux] = '\0';
                contadorAux--;
            }

            if(inicio->left == NULL)
                inicio->left = create_CELL_number(number);
            else if(inicio->right == NULL)
                inicio->right = create_CELL_number(number);
            else
            {
                aux = inicio;
                inicio = create_CELL_parenthesis(aux, create_CELL_number(number));
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
    if(inicio->type.operador == '@')
    {
        if(inicio->left != NULL)
        {
            print_graph(inicio->left);
        }
        if(inicio->right != NULL)
        {
            if(inicio->right->type.operador == '@')
            {
                printf("(");
            }
            print_graph(inicio->right);
            if(inicio->right->type.operador == '@')
            {
                printf(")");
            }
        }
    }
    else if (inicio->id == 'o')
    {

        printf("%c",inicio->type.operador);
    }
    else if(inicio->id == 'n')
    {

        printf("%d", (int)inicio->type.number);
    }
}

CELL* reduct(CELL* inicio)
{
    CELL* vetor[] = {NULL, NULL, NULL, NULL}, *a, *b, *c, *d, *op, *cauda, *f, *g, *x, *y, *par1, *par2;
    CELL* aux = inicio, *aux2, *aux3, *aux4, *aux5;
    int i;
    int resultSoma = 0;
    int resultDiv = 0;
    int resultMult = 0;
    int resultSub = 0;
    int imprimirGrafo = 0;
    int reductible = 1;
    Pilha* pilha = create_pilha();
    pilha_insere(pilha, inicio);
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
        printf("combinador: %c\n", aux->type.operador);
        printf("string = ");
        print_graph(inicio);
        printf("\n");
        switch (aux->type.operador)
        {
        case 'K':
        //printf("chegou aqui\n");
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
                            /*printf("GRAFO DE A\n\n\n");
                            print_graph(a->right);
                            printf("\n\n");
                            printf("GRAFO DE b\n\n\n");
                            print_graph(b->right);
                            printf("\n\n");*/

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
            if(imprimirGrafo == 1)
            {
                print_graph(inicio);
            }
            break;

        case 'k':
        //printf("chegou aqui\n");
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
                            /*printf("GRAFO DE A\n\n\n");
                            print_graph(a->right);
                            printf("\n\n");
                            printf("GRAFO DE b\n\n\n");
                            print_graph(b->right);
                            printf("\n\n");*/
                            //printf("chegou aqui no que tem cauda\n");
                            //printf("a: \n\n");
                            //print_graph(a->right);
                            //printf("\n\n\n");
                            //printf("b: \n\n");
                            //print_graph(b->right);
                            //printf("\n\n\n");
                            c = get_topo_pilha(pilha);
                            //printf("c: \n\n");
                            //print_graph(c->right);  // o '@' que guarda o c
                            //printf("\n");
                            pilha_remove(pilha);
                            c->left = b->right;
                            pilha_insere(pilha, c);
                        }
                        else   // Nao tem cauda
                        {
                            //printf("chegou aqui no que NAO tem cauda\n");
                            b->left = b->right;
                            b->right = NULL;
                            pilha_insere(pilha, b);
                        }

                     }
                }
            }
#ifdef COUNTERK
            contK++;
#endif
            if(imprimirGrafo == 1)
            {
                print_graph(inicio);
            }
            //printf("\n\n");
            //print_graph(inicio);
        //printf("\n\n");
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


        case '+':
            if(pilha == NULL)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                pilha_remove(pilha); // Tirar o operador '+'
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
                            c = get_topo_pilha(pilha);
                            pilha_remove(pilha);
                            //printf("entrou na recursao do a\n");
                            aux4 = reduct(a->right);
                            //printf("saiu na recursao do a\n");
                            //printf("entrou na recursao do b\n");
                            aux5 = reduct(b->right);
                            //printf("saiu na recursao do b\n");
                            //printf("chegou aqui depois\n");

                            if(aux4->type.operador == '@')
                            {
                                aux4 = aux4->left;
                            }
                            if(aux5->type.operador == '@')
                            {
                                aux5 = aux5->left;
                            }
                            //printf("primeiro: %d\n", (int)aux4->type.number);
                            //printf("segundo: %d\n", (int)aux5->type.number);

                            resultSoma = ((int)aux4->type.number + (int)aux5->type.number);

                            c->left = create_CELL_number(resultSoma);
                        }
                        else
                        {
                            //nao tem cauda

                            aux4 = reduct(a->right);
                            //printf("saiu na recursao do a\n");
                            //printf("entrou na recursao do b\n");
                            aux5 = reduct(b->right);
                            if(aux4->type.operador == '@')
                            {
                                aux4 = aux4->left;
                            }
                            if(aux5->type.operador == '@')
                            {
                                aux5 = aux5->left;
                            }
                            resultSoma = ((int)aux4->type.number + (int)aux5->type.number);
                            b->left = create_CELL_number(resultSoma);
                            b->right = NULL;


                        }



                     }
                }
            }
            break;
        case '-':
            if(pilha == NULL)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                pilha_remove(pilha); // Tirar o operador '+'
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
                            c = get_topo_pilha(pilha);
                            pilha_remove(pilha);
                            //printf("entrou na recursao do a\n");
                            aux4 = reduct(a->right);
                            //printf("saiu na recursao do a\n");
                            //printf("entrou na recursao do b\n");
                            aux5 = reduct(b->right);
                            //printf("saiu na recursao do b\n");
                            //printf("chegou aqui depois\n");

                            if(aux4->type.operador == '@')
                            {
                                aux4 = aux4->left;
                            }
                            if(aux5->type.operador == '@')
                            {
                                aux5 = aux5->left;
                            }
                            //printf("primeiro: %d\n", (int)aux4->type.number);
                            //printf("segundo: %d\n", (int)aux5->type.number);

                            resultSoma = ((int)aux4->type.number - (int)aux5->type.number);

                            c->left = create_CELL_number(resultSoma);
                        }
                        else
                        {
                            //nao tem cauda

                            aux4 = reduct(a->right);
                            //printf("saiu na recursao do a\n");
                            //printf("entrou na recursao do b\n");
                            aux5 = reduct(b->right);
                            if(aux4->type.operador == '@')
                            {
                                aux4 = aux4->left;
                            }
                            if(aux5->type.operador == '@')
                            {
                                aux5 = aux5->left;
                            }
                            resultSoma = ((int)aux4->type.number - (int)aux5->type.number);
                            b->left = create_CELL_number(resultSoma);
                            b->right = NULL;


                        }



                     }
                }
            }
            break;
        case '*':
            if(pilha == NULL)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                pilha_remove(pilha); // Tirar o operador '+'
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
                            c = get_topo_pilha(pilha);
                            pilha_remove(pilha);
                            //printf("entrou na recursao do a\n");
                            aux4 = reduct(a->right);
                            //printf("saiu na recursao do a\n");
                            //printf("entrou na recursao do b\n");
                            aux5 = reduct(b->right);
                            //printf("saiu na recursao do b\n");
                            //printf("chegou aqui depois\n");

                            if(aux4->type.operador == '@')
                            {
                                aux4 = aux4->left;
                            }
                            if(aux5->type.operador == '@')
                            {
                                aux5 = aux5->left;
                            }
                            //printf("primeiro: %d\n", (int)aux4->type.number);
                            //printf("segundo: %d\n", (int)aux5->type.number);

                            resultSoma = ((int)aux4->type.number * (int)aux5->type.number);

                            c->left = create_CELL_number(resultSoma);
                        }
                        else
                        {
                            //nao tem cauda

                            aux4 = reduct(a->right);
                            //printf("saiu na recursao do a\n");
                            //printf("entrou na recursao do b\n");
                            aux5 = reduct(b->right);
                            if(aux4->type.operador == '@')
                            {
                                aux4 = aux4->left;
                            }
                            if(aux5->type.operador == '@')
                            {
                                aux5 = aux5->left;
                            }
                            resultSoma = ((int)aux4->type.number * (int)aux5->type.number);
                            b->left = create_CELL_number(resultSoma);
                            b->right = NULL;


                        }



                     }
                }
            }
            break;
        case '/':
            if(pilha == NULL)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                pilha_remove(pilha); // Tirar o operador '+'
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
                            c = get_topo_pilha(pilha);
                            pilha_remove(pilha);
                            //printf("entrou na recursao do a\n");
                            aux4 = reduct(a->right);
                            //printf("saiu na recursao do a\n");
                            //printf("entrou na recursao do b\n");
                            aux5 = reduct(b->right);
                            //printf("saiu na recursao do b\n");
                            //printf("chegou aqui depois\n");

                            if(aux4->type.operador == '@')
                            {
                                aux4 = aux4->left;
                            }
                            if(aux5->type.operador == '@')
                            {
                                aux5 = aux5->left;
                            }
                            //printf("primeiro: %d\n", (int)aux4->type.number);
                            //printf("segundo: %d\n", (int)aux5->type.number);

                            resultSoma = ((int)aux4->type.number / (int)aux5->type.number);

                            c->left = create_CELL_number(resultSoma);
                        }
                        else
                        {
                            //nao tem cauda

                            aux4 = reduct(a->right);
                            //printf("saiu na recursao do a\n");
                            //printf("entrou na recursao do b\n");
                            aux5 = reduct(b->right);
                            if(aux4->type.operador == '@')
                            {
                                aux4 = aux4->left;
                            }
                            if(aux5->type.operador == '@')
                            {
                                aux5 = aux5->left;
                            }
                            resultSoma = ((int)aux4->type.number / (int)aux5->type.number);
                            b->left = create_CELL_number(resultSoma);
                            b->right = NULL;


                        }



                     }
                }
            }
            break;

        case '=':
            if(pilha == NULL)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                pilha_remove(pilha); // Tirar o operador '='
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
                            c = get_topo_pilha(pilha);
                            pilha_remove(pilha);
                            //print_graph(a->right);


                            //print_graph(b->right);

                            aux4 = reduct(a->right);
                            //printf("saiu na recursao do a\n");
                            //printf("entrou na recursao do b\n");
                            aux5 = reduct(b->right);
                            //printf("saiu na recursao do b\n");
                            //printf("chegou aqui depois\n");

                            if(aux4->type.operador == '@')
                            {
                                if (aux4->left != NULL)
                                {
                                    aux4 = aux4->left;
                                }
                                else
                                    aux4 = aux4->right;
                            }
                            if(aux5->type.operador == '@')
                            {
                                if (aux5->left != NULL)
                                {
                                    aux5 = aux5->left;
                                }
                                else
                                    aux5 = aux5->right;
                            }
                            print_graph(inicio);
                            printf("xxt\n");

                            if ((int)aux4->type.number == (int)aux5->type.number)
                            {
                                //printf("entrou no K\n");
                                c->left = create_CELL_leaf('K');
                            }
                            else
                            {
                                //printf("entrou no k\n");
                                c->left = create_CELL_leaf('k');
                            }
                            pilha_insere(pilha, c);
                        }
                        else   // Nao tem cauda
                        {
                             aux4 = reduct(a->right);


                            aux5 = reduct(b->right);



                            if(aux4->type.operador == '@')
                            {
                                aux4 = aux4->left;
                            }
                            if(aux5->type.operador == '@')
                            {
                                aux5 = aux5->left;
                            }
                            if ((int)aux4->type.number == (int)aux5->type.number)
                            {
                                //printf("entrou no K\n");
                                b->left = create_CELL_leaf('K');
                            }
                            else
                            {
                                b->left = create_CELL_leaf('k');
                            }

                            b->right = NULL;
                            pilha_insere(pilha, b);
                        }

                     }
                }

            }
            //printf("imprimindo depois do  = : \n");
            //print_graph(inicio);
            //printf("\n\n");
            //imprimirGrafo = 1;
            if(imprimirGrafo == 1)
            {
                print_graph(inicio);
            }
            break;
        case '<':
            if(pilha == NULL)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                pilha_remove(pilha); // Tirar o operador '+'
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
                            c = get_topo_pilha(pilha);
                            pilha_remove(pilha);
                            //printf("entrou na recursao do a\n");
                            aux4 = reduct(a->right);
                            //printf("saiu na recursao do a\n");
                            //printf("entrou na recursao do b\n");
                            aux5 = reduct(b->right);
                            //printf("saiu na recursao do b\n");
                            //printf("chegou aqui depois\n");

                            if(aux4->type.operador == '@')
                            {
                                aux4 = aux4->left;
                            }
                            if(aux5->type.operador == '@')
                            {
                                aux5 = aux5->left;
                            }
                            //printf("primeiro: %d\n", (int)aux4->type.number);
                            //printf("segundo: %d\n", (int)aux5->type.number);

                            if ((int)aux4->type.number < (int)aux5->type.number)
                            {
                                //printf("fez a comparação\n");
                                c->left = create_CELL_leaf('K');
                            }
                            else
                            {
                                //printf("fez a comparação\n");
                                c->left = create_CELL_leaf('k');
                            }

                            pilha_insere(pilha, c);
                        }
                        else   // Nao tem cauda
                        {
                            aux4 = reduct(a->right);


                            aux5 = reduct(b->right);



                            if(aux4->type.operador == '@')
                            {
                                aux4 = aux4->left;
                            }
                            if(aux5->type.operador == '@')
                            {
                                aux5 = aux5->left;
                            }
                            if ((int)aux4->type.number < (int)aux5->type.number)
                            {
                                //printf("entrou no K\n");
                                b->left = create_CELL_leaf('K');
                            }
                            else
                            {
                                b->left = create_CELL_leaf('k');
                            }

                            b->right = NULL;
                            pilha_insere(pilha, b);
                        }

                     }
                }
            }
            //printf("chegou aqui\n");
            break;
        case '>':
            if(pilha == NULL)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                pilha_remove(pilha); // Tirar o operador '='
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
                            c = get_topo_pilha(pilha);
                            pilha_remove(pilha);
                            //print_graph(a->right);


                            //print_graph(b->right);

                           aux4 = reduct(a->right);
                            //printf("saiu na recursao do a\n");
                            //printf("entrou na recursao do b\n");
                            aux5 = reduct(b->right);
                            //printf("saiu na recursao do b\n");
                            //printf("chegou aqui depois\n");

                            if(aux4->type.operador == '@')
                            {
                                aux4 = aux4->left;
                            }
                            if(aux5->type.operador == '@')
                            {
                                aux5 = aux5->left;
                            }


                            if ((int)aux4->type.number > (int)aux5->type.number)
                            {
                                //printf("entrou no K\n");
                                c->left = create_CELL_leaf('K');
                            }
                            else
                            {
                                //printf("entrou no k\n");
                                c->left = create_CELL_leaf('k');
                            }
                            pilha_insere(pilha, c);
                        }
                        else   // Nao tem cauda
                        {
                             aux4 = reduct(a->right);


                            aux5 = reduct(b->right);



                            if(aux4->type.operador == '@')
                            {
                                aux4 = aux4->left;
                            }
                            if(aux5->type.operador == '@')
                            {
                                aux5 = aux5->left;
                            }
                            if ((int)aux4->type.number > (int)aux5->type.number)
                            {
                                //printf("entrou no K\n");
                                b->left = create_CELL_leaf('K');
                            }
                            else
                            {
                                b->left = create_CELL_leaf('k');
                            }

                            b->right = NULL;
                            pilha_insere(pilha, b);
                        }

                     }
                }

            }
            //printf("imprimindo depois do  = : \n");
            //print_graph(inicio);
            //printf("\n\n");
            //imprimirGrafo = 1;
            if(imprimirGrafo == 1)
            {
                print_graph(inicio);
            }
            break;

        case 'Y':
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
                     printf("%c\n", a->type.operador);

                     aux2 = a->left;

                     a->left = a->right;
                     a->right = create_CELL_parenthesis(aux2, a->right);




                     if(!is_Pilha_Vazia(pilha)) // Tem cauda, vai ter que mudar o ponteiro
                     {
                         b = get_topo_pilha(pilha);  // o '@' que guarda o b
                         pilha_remove(pilha);
                         b->left = a;
                         pilha_insere(pilha, b);
                     }
                     else   // Nao tem cauda
                     {
                         pilha_insere(pilha, a);
                     }
                }
            }
            break;


        default:
            reductible = 0;
            break;
        }



        /*printf("\n\n");
        print_graph(inicio);
        printf("\n\n");*/
    }
    return inicio;
}
void mg_V2()
{
    int size = strlen(string);

    CELL* inicio = create_graph2(size);
    CELL* aux = inicio, *aux2, *aux3;
    int i;
    int imprimirGrafo = 0;
    int reductible = 1;
    Pilha* pilha = create_pilha();
    pilha_insere(pilha, inicio);
    CELL* vetor[] = {NULL, NULL, NULL, NULL}, *a, *b, *c, *d, *op, *cauda, *f, *g, *x, *y, *par1, *par2;
    int counter = 0;

    //print_graph(inicio);
    //printf("\n");
    inicio = reduct(inicio);
    print_graph(inicio);

}

int main()
{
    mg_V2();
    printf("\n\n");


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
