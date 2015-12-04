/*
 * Reductions, this document provides functions to reduct the Graph
 * implemented in this project (Here is the implement of each funtion, 
 * the assign is in the Global Header File)
 */

#ifndef REDUCTIONS_H_
#define REDUCTIONS_H_

// Function to reduct
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
        /*
         printf("operador = %c\n", aux->type.operador);
         print_graph(inicio);
         printf("\n");
         getchar();
         */

        switch (aux->type.operador)
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
                            c->left = a->right;
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
            if(pilha == NULL)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                pilha_remove(pilha); // Tirar o operador 'k'
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
                            c->left = b->right;
                        }
                        else   // Nao tem cauda
                        {
                           b->left = b->right;
                           b->right = NULL;
                           pilha_insere(pilha,b);
                        }
                    }
                }
            }
#ifdef COUNTERK
            contKlinha++;
#endif
            if(imprimirGrafo == 1)
            {
                print_graph(inicio);
            }
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
                            
                            aux2 = create_CELL_parenthesis(NULL, NULL);
                            aux2->left = create_CELL_parenthesis(NULL, NULL);
                            aux2->right = create_CELL_parenthesis(NULL, NULL);

                            aux2->left->left = a->right;
                            aux2->left->right = c->right;
                            aux2->right->left = b->right;
                            aux2->right->right = c->right;

                            if(!is_Pilha_Vazia(pilha)) // Tem cauda, vai ter que mudar o ponteiro
                            {
                                d = get_topo_pilha(pilha);
                                d->left = aux2;
                            }
                            else   // Nao tem cauda
                            {
                                inicio = aux2;
                                pilha_insere(pilha, aux2);
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
                        b->left = a->right;
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
                            
                            aux2 = create_CELL_parenthesis(NULL,NULL);
                            aux2->right = create_CELL_parenthesis(NULL, NULL);

                            aux2->left = f->right;
                            aux2->right->left = g->right;
                            aux2->right->right = x->right;



                            if(!is_Pilha_Vazia(pilha)) // Tem cauda, vai ter que mudar o ponteiro
                            {
                                cauda = get_topo_pilha(pilha);
                                cauda->left = aux2;
                            }
                            else   // Nao tem cauda
                            {
                                inicio = aux2;
                                pilha_insere(pilha, aux2);
                            }
                        }
                    }
                }


            }
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
            else
            {
                pilha_remove(pilha); //tira o operador 'C'
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

                            aux2 = create_CELL_parenthesis(NULL, NULL);
                            aux2->left = create_CELL_parenthesis(NULL, NULL);
                            aux2->right = x->right;
                            aux2->left->right = y->right;
                            aux2->left->left = f->right;

                            if(!is_Pilha_Vazia(pilha)) // Tem cauda, vai ter que mudar o ponteiro
                            {
                                cauda = get_topo_pilha(pilha);
                                cauda->left = aux2;
                            }
                            else   // Nao tem cauda
                            {
                                inicio = aux2; // tem que atualizar o inicio, ja que nao tem cauda
                                pilha_insere(pilha, aux2);
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
                                d = get_topo_pilha(pilha);  // o '@' que guarda o d
                                pilha_remove(pilha);

                                aux2 = create_CELL_parenthesis(NULL, NULL);
                                aux2->left = create_CELL_parenthesis(NULL, NULL);
                                aux2->left->right = create_CELL_parenthesis(NULL, NULL);
                                aux2->right = create_CELL_parenthesis(NULL, NULL);

                                aux2->left->left = a->right;
                                aux2->left->right->left = b->right;
                                aux2->left->right->right = d->right;
                                aux2->right->left = c->right;
                                aux2->right->right = d->right;


                                if(!is_Pilha_Vazia(pilha)) // Tem cauda, vai ter que mudar o ponteiro
                                {
                                    cauda = get_topo_pilha(pilha);
                                    cauda->left = aux2;
                                }
                                else   // Nao tem cauda
                                {
                                    inicio = aux2;
                                    pilha_insere(pilha, aux2);
                                    // Nao precisa atualizar o inicio, pq reutilizamos o d, que ja ta sendo apontado por ele
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
                                d = get_topo_pilha(pilha); // o '@' que guarda o d
                                pilha_remove(pilha);

                                aux2 = create_CELL_parenthesis(NULL, NULL);
                                aux2->right = create_CELL_parenthesis(NULL, NULL);
                                aux2->left = create_CELL_parenthesis(NULL, NULL);

                                aux2->left->left = a->right;
                                aux2->left->right = b->right;
                                aux2->right->left = c->right;
                                aux2->right->right = d->right;

                                if(!is_Pilha_Vazia(pilha)) // Tem cauda, vai ter que mudar o ponteiro
                                {
                                    cauda = get_topo_pilha(pilha);
                                    cauda->left = aux2;
                                }
                                else   // Nao tem cauda
                                {
                                    inicio = aux2;
                                    pilha_insere(pilha, aux2);
                                    // tem que atualizar o inicio, ja que nao tem cauda
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
                                d = get_topo_pilha(pilha); // o '@' que guarda o d
                                pilha_remove(pilha);

                                aux2 = create_CELL_parenthesis(NULL, NULL);
                                aux2->left = create_CELL_parenthesis(NULL, NULL);
                                aux2->left->right = create_CELL_parenthesis(NULL, NULL);

                                aux2->left->left = a->right;
                                aux2->left->right->left = b->right;
                                aux2->left->right->right = d->right;
                                aux2->right = c->right;

                                if(!is_Pilha_Vazia(pilha)) // Tem cauda, vai ter que mudar o ponteiro
                                {
                                    cauda = get_topo_pilha(pilha);
                                    cauda->left = aux2;
                                }
                                else   // Nao tem cauda
                                {
                                    inicio = aux2;
                                    pilha_insere(pilha, aux2); // como foi criado o aux3, tem que atualizar o ponteiro inicial
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

                        if(!is_Pilha_Vazia(pilha)) // o '@' que guarda a cauda c
                        {
                            c = get_topo_pilha(pilha);
                            pilha_remove(pilha);

                            a->right = reduct(a->right);
                            b->right = reduct(b->right);

                            if(a->right->type.operador == '@')
                            {
                                if (a->right->left != NULL)
                                {
                                    a->right = a->right->left;
                                }
                            }
                            if(b->right->type.operador == '@')
                            {
                                if (b->right->left != NULL)
                                {
                                    b->right = b->right->left;
                                }
                            }

                            resultSoma = (a->right->type.number + b->right->type.number);

                            c->left = create_CELL_number(resultSoma);
                            pilha_insere(pilha, c);
                        }
                        else
                        {
                            // Nao tem cauda
                            if(a->right->id != 'n')
                            {
                                a->right = reduct(a->right);
                            }
                            if(b->right->id != 'n')
                            {
                                b->right = reduct(b->right);
                            }

                            if(a->right->type.operador == '@')
                            {
                                a->right = a->right->left;
                            }
                            if(b->right->type.operador == '@')
                            {
                                b->right = b->right->left;
                            }
                            resultSoma = (a->right->type.number + b->right->type.number);
                            b->left = create_CELL_number(resultSoma);
                            b->right = NULL;
                            pilha_insere(pilha, b);
                        }
                    }
                }
            }
            #ifdef COUNTERSOMA
            contSoma++;
            #endif
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

                        if(!is_Pilha_Vazia(pilha)) // o '@' que guarda a cauda c
                        {
                            c = get_topo_pilha(pilha);
                            pilha_remove(pilha);

                            a->right = reduct(a->right);
                            b->right = reduct(b->right);

                            if(a->right->type.operador == '@')
                            {
                                if (a->right->left != NULL)
                                {
                                    a->right = a->right->left;
                                }
                            }
                            if(b->right->type.operador == '@')
                            {
                                if (b->right->left != NULL)
                                {
                                    b->right = b->right->left;
                                }
                            }

                            resultSoma = (a->right->type.number - b->right->type.number);
                            c->left = create_CELL_number(resultSoma);
                            pilha_insere(pilha, c);
                        }
                        else
                        {
                            // Nao tem cauda
                            if(a->right->id != 'n')
                            {
                                a->right = reduct(a->right);
                            }
                            if(b->right->id != 'n')
                            {
                                b->right = reduct(b->right);
                            }

                            if(a->right->type.operador == '@')
                            {
                                a->right = a->right->left;
                            }
                            if(b->right->type.operador == '@')
                            {
                                b->right = b->right->left;
                            }
                            resultSoma = (a->right->type.number - b->right->type.number);
                            b->left = create_CELL_number(resultSoma);
                            b->right = NULL;
                            pilha_insere(pilha, b);
                        }
                    }
                }
            }
            #ifdef COUNTERSUB
            contSub++;
            #endif
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

                        if(!is_Pilha_Vazia(pilha)) // o '@' que guarda a cauda c
                        {
                            c = get_topo_pilha(pilha);
                            pilha_remove(pilha);

                            a->right = reduct(a->right);
                            b->right = reduct(b->right);

                            if(a->right->type.operador == '@')
                            {
                                if (a->right->left != NULL)
                                {
                                    a->right = a->right->left;
                                }
                            }
                            if(b->right->type.operador == '@')
                            {
                                if (b->right->left != NULL)
                                {
                                    b->right = b->right->left;
                                }
                            }

                            resultSoma = (a->right->type.number * b->right->type.number);

                            c->left = create_CELL_number(resultSoma);
                            pilha_insere(pilha, c);
                        }
                        else
                        {
                            // Nao tem cauda
                            if(a->right->id != 'n')
                            {
                                a->right = reduct(a->right);
                            }
                            if(b->right->id != 'n')
                            {
                                b->right = reduct(b->right);
                            }

                            if(a->right->type.operador == '@')
                            {
                                a->right = a->right->left;
                            }
                            if(b->right->type.operador == '@')
                            {
                                b->right = b->right->left;
                            }
                            resultSoma = (a->right->type.number * b->right->type.number);
                            b->left = create_CELL_number(resultSoma);
                            b->right = NULL;
                            pilha_insere(pilha, b);
                        }

                    }
                }
            }
            #ifdef COUNTERMULT
            contMult++;
            #endif
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

                        if(!is_Pilha_Vazia(pilha)) // o '@' que guarda a cauda c
                        {
                            c = get_topo_pilha(pilha);
                            pilha_remove(pilha);

                            a->right = reduct(a->right);
                            b->right = reduct(b->right);

                            if(a->right->type.operador == '@')
                            {
                                if (a->right->left != NULL)
                                {
                                    a->right = a->right->left;
                                }
                            }
                            if(b->right->type.operador == '@')
                            {
                                if (b->right->left != NULL)
                                {
                                    b->right = b->right->left;
                                }
                            }

                            resultSoma = (a->right->type.number / b->right->type.number);
                            c->left = create_CELL_number(resultSoma);
                            pilha_insere(pilha, c);
                        }
                        else
                        {
                            // Nao tem cauda
                            if(a->right->id != 'n')
                            {
                                a->right = reduct(a->right);
                            }
                            if(b->right->id != 'n')
                            {
                                b->right = reduct(b->right);
                            }

                            if(a->right->type.operador == '@')
                            {
                                a->right = a->right->left;
                            }
                            if(b->right->type.operador == '@')
                            {
                                b->right = b->right->left;
                            }
                            resultSoma = (a->right->type.number / b->right->type.number);
                            b->left = create_CELL_number(resultSoma);
                            b->right = NULL;
                            pilha_insere(pilha, b);
                        }

                    }
                }
            }
            #ifdef COUNTERDIV
            contDiv++;
            #endif
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

                        if(a->right->id != 'n')
                        {
                            a->right = reduct(a->right);
                        }

                        if(b->right->id != 'n')
                        {
                            b->right = reduct(b->right);
                        }

                        if(a->right->type.operador == '@')
                        {
                            a->right = a->right->left;
                        }
                        if(b->right->type.operador == '@')
                        {
                            b->right = b->right->left;
                        }
                        printf("\na = %d b = %d\n",a->right->type.number, b->right->type.number);

                        if(a->right->type.number == b->right->type.number)
                        {
                            aux2 = create_CELL_leaf('K');
                        }
                        else
                        {
                            aux2 = create_CELL_leaf('k');
                        }

                        //system("PAUSE");
                        if(!is_Pilha_Vazia(pilha)) // Tem cauda, vai ter que mudar o ponteiro
                        {
                            c = get_topo_pilha(pilha);
                            c->left = aux2;
                        }
                        else
                        {
                            pilha_insere(pilha,aux2);
                            inicio = aux2;
                        }
                    }
                }

            }
            if(imprimirGrafo == 1)
            {
               // printf("?");
                print_graph(inicio);
            }

            #ifdef COUNTERIGUAL
            contIgual++;
            #endif
            break;


        case '<':
            if(pilha == NULL)
            {
                reductible = 0; // chegou ao fim
                break;
            }
              else
            {
                pilha_remove(pilha); // Tirar o operador '>'
                if (!is_Pilha_Vazia(pilha))
                {
                    a = get_topo_pilha(pilha); // Guarda o ponteiro de 'a'
                    pilha_remove(pilha);    // Retira o @ que guarda o 'a'

                    if(!is_Pilha_Vazia(pilha))
                    {
                        b = get_topo_pilha(pilha);  // o '@' que guarda o b
                        pilha_remove(pilha);

                        if(a->right->id != 'n')
                        {
                            a->right = reduct(a->right);
                        }

                        if(b->right->id != 'n')
                        {
                            b->right = reduct(b->right);
                        }

                        if(a->right->type.operador == '@')
                        {
                            a->right = a->right->left;
                        }
                        if(b->right->type.operador == '@')
                        {
                            b->right = b->right->left;
                        }
                        printf("\na = %d b = %d\n",a->right->type.number, b->right->type.number);

                        if(a->right->type.number < b->right->type.number)
                        {
                            aux2 = create_CELL_leaf('K');
                        }
                        else
                        {
                            aux2 = create_CELL_leaf('k');
                        }

                        if(!is_Pilha_Vazia(pilha)) // Tem cauda, vai ter que mudar o ponteiro
                        {
                            c = get_topo_pilha(pilha);
                            c->left = aux2;
                        }
                        else
                        {
                            pilha_insere(pilha,aux2);
                            inicio = aux2;
                        }
                    }
                }

            }
            #ifdef COUNTERMENOR
            contMenor++;
            #endif
            break;


        case '>':
            if(pilha == NULL)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                pilha_remove(pilha); // Tirar o operador '>'
                if (!is_Pilha_Vazia(pilha))
                {
                    a = get_topo_pilha(pilha); // Guarda o ponteiro de 'a'
                    pilha_remove(pilha);    // Retira o @ que guarda o 'a'

                    if(!is_Pilha_Vazia(pilha))
                    {
                        b = get_topo_pilha(pilha);  // o '@' que guarda o b
                        pilha_remove(pilha);

                        if(a->right->id != 'n')
                        {
                            a->right = reduct(a->right);
                        }

                        if(b->right->id != 'n')
                        {
                            b->right = reduct(b->right);
                        }

                        if(a->right->type.operador == '@')
                        {
                            a->right = a->right->left;
                        }
                        if(b->right->type.operador == '@')
                        {
                            b->right = b->right->left;
                        }
                        printf("\na = %d b = %d\n",a->right->type.number, b->right->type.number);

                        if(a->right->type.number > b->right->type.number)
                        {
                            aux2 = create_CELL_leaf('K');
                        }
                        else
                        {
                            aux2 = create_CELL_leaf('k');
                        }

                        if(!is_Pilha_Vazia(pilha)) // Tem cauda, vai ter que mudar o ponteiro
                        {
                            c = get_topo_pilha(pilha);
                            c->left = aux2;
                        }
                        else
                        {
                            pilha_insere(pilha,aux2);
                            inicio = aux2;
                        }
                    }
                }

            }
            if(imprimirGrafo == 1)
            {
                print_graph(inicio);
            }
            #ifdef COUNTERMAIOR
            contMaior++;
            #endif
            break;

        case 'Y':
            if(pilha == NULL)
            {
                reductible = 0;
                break;
            }
            else
            {
                op = get_topo_pilha(pilha);
                pilha_remove(pilha); //tira o operador
                if (!is_Pilha_Vazia(pilha))
                {
                    a = get_topo_pilha(pilha);  // o '@' que guarda o a
                    pilha_remove(pilha);

                    aux2 = create_CELL_parenthesis(NULL, NULL);
                    aux2->left = a->right;
                    aux2->right = create_CELL_parenthesis(NULL, NULL);
                    aux2->right->right = a->right;
                    aux2->right->left = op;

                    if(!is_Pilha_Vazia(pilha)) // Tem cauda, vai ter que mudar o ponteiro
                    {
                        b = get_topo_pilha(pilha);  // o '@' que guarda o b
                        b->left = aux2;
                    }
                    else   // Nao tem cauda
                    {
                        inicio = aux2;
                    }
                }
            }
            #ifdef COUNTERY
            contY++;
            #endif

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


#endif