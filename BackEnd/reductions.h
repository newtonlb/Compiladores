/*
 * Reductions, this document provides functions to reduct the Graph
 * implemented in this project (Here is the implement of each funtion, 
 * the assign is in the Global Header File)
 */

#ifndef REDUCTIONS_H_
#define REDUCTIONS_H_

void getArguments(int arguments)
{
    if(arguments >= 1)
    {
        a = get_topo_pilha(pilha);  // Guarda o '@' que guarda o 'a'
        pilha_remove(pilha);       // Retira o @ que guarda o 'a'    
    }

    if(arguments >= 2)
    {
        b = get_topo_pilha(pilha);  // Guarda o '@' que guarda o 'b'
        pilha_remove(pilha);       // Retira o @ que guarda o 'b'
    }
    
    if(arguments >= 3)
    {
        c = get_topo_pilha(pilha);  // Guarda o '@' que guarda o 'c'
        pilha_remove(pilha);       // Retira o @ que guarda o 'c'
    }

    if(arguments >= 4)
    {
        d = get_topo_pilha(pilha);  // Guarda o '@' que guarda o 'd'
        pilha_remove(pilha);       // Retira o @ que guarda o 'd'
    }

}


// Function to reduct
CELL* reduct(CELL* inicio)
{

    int i, arguments;
    int resultSoma = 0;
    int resultDiv = 0;
    int resultMult = 0;
    int resultSub = 0;
    int imprimirGrafo = 0;
    int reductible = 1;
    CELL* raiz_aux;
    pilha_insere(pilha, inicio);
    aux = inicio;

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


        op = get_topo_pilha(pilha);
        pilha_remove(pilha); 
        /*
         printf("operador = %c\n", aux->type.operador);
         print_graph(inicio);
         printf("\n");
         getchar();
         */

        switch (op->type.operador)
        {
        case 'K':
            arguments = 2; // Sao 2 argumentos 
            if(pilha == NULL || pilhaPos <= 1)
            {
                //printf("XXT\n");
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                getArguments(arguments); // Pegamos o a, b, mas falta saber se tem o elemento cauda ou nao
          
                if(!is_Pilha_Vazia(pilha)) // Tem cauda, vai ter que mudar o ponteiro
                {
                    cauda = get_topo_pilha(pilha);  // o '@' que guarda o c
                    cauda->left = a->right;
                }
                else   // Nao tem cauda
                {
                    inicio = a->right;
                    pilha_insere(pilha, a->right);
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
            arguments = 2; // Sao 2 argumentos 
            if(pilha == NULL || pilhaPos  <= 1)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                getArguments(arguments); // Pegamos o a, b, mas falta saber se tem o elemento cauda ou nao
                if(!is_Pilha_Vazia(pilha)) // Tem cauda, vai ter que mudar o ponteiro
                {
                    cauda = get_topo_pilha(pilha);
                    cauda->left = b->right;
                }
                else   // Nao tem cauda
                {
                   
                    inicio = b->right;
                    pilha_insere(pilha, b->right);
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
            arguments = 3;  // Sao 3 argumentos 
            if(pilha == NULL || pilhaPos  <= 1)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                getArguments(arguments); // Pegamos o a, b, c,  mas falta saber se tem o elemento cauda ou nao
           
                aux2 = create_CELL_parenthesis(NULL, NULL);
                aux2->left = create_CELL_parenthesis(NULL, NULL);
                aux2->right = create_CELL_parenthesis(NULL, NULL);

                aux2->left->left = a->right;
                aux2->left->right = c->right;
                aux2->right->left = b->right;
                aux2->right->right = c->right;

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

#ifdef COUNTERS
            contS++;
#endif
            break;


        case 'I':
            arguments = 1; // Tem so 1 argumento
            if(pilha == NULL || pilhaPos  <= 1)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                getArguments(arguments); // Pegamos o a, mas falta saber se tem o elemento cauda ou nao
                if(!is_Pilha_Vazia(pilha)) // Tem cauda, vai ter que mudar o ponteiro
                {
                    cauda = get_topo_pilha(pilha);  // o '@' que guarda o b
                    cauda->left = a->right;
                }
                else   // Nao tem cauda
                {
                    inicio = a->right;
                    pilha_insere(pilha, a->right);
                }
            }

#ifdef COUNTERI
            contI++;
#endif
            break;

        case 'B':
            arguments = 3; // Sao 3 argumentos 
            if(pilha == NULL || pilhaPos  <= 1)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                getArguments(arguments); // Pegamos o a,b,c mas falta saber se tem o elemento cauda ou nao            
                aux2 = create_CELL_parenthesis(NULL,NULL);
                aux2->right = create_CELL_parenthesis(NULL, NULL);
                aux2->left = a->right;
                aux2->right->left = b->right;
                aux2->right->right = c->right;
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
#ifdef COUNTERB
            contB++;
#endif

        break;

        case 'C':
            arguments = 3; // Sao 3 argumentos 
            if(pilha == NULL || pilhaPos  <= 1)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                getArguments(arguments); // Pegamos o a,b,c mas falta saber se tem o elemento cauda ou nao         
                aux2 = create_CELL_parenthesis(NULL, NULL);
                aux2->left = create_CELL_parenthesis(NULL, NULL);
                aux2->right = b->right;
                aux2->left->right = c->right;
                aux2->left->left = a->right;

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

#ifdef COUNTERC
            contC++;
#endif
            break;

        case 's':
            arguments = 4; // Sao 4 argumentos 
            if(pilha == NULL || pilhaPos  <= 1)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                getArguments(arguments); // Pegamos o a,b,c,d mas falta saber se tem o elemento cauda ou nao   
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
#ifdef COUNTERSLINHA
            contSlinha++;
#endif
            break;

        case 'b':
            arguments = 4; // Sao 4 argumentos 
            if(pilha == NULL || pilhaPos  <= 1)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                getArguments(arguments); // Pegamos o a,b,c,d mas falta saber se tem o elemento cauda ou nao   
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

#ifdef COUNTERBLINHA
            contBlinha++;
#endif


            break;

        case 'c':
            arguments = 4; // Sao 4 argumentos 
            if(pilha == NULL || pilhaPos  <= 1)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                getArguments(arguments); // Pegamos o a,b,c,d mas falta saber se tem o elemento cauda ou nao   
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
#ifdef COUNTERCLINHA
            contClinha++;
#endif
            break;

        case '+':
            arguments = 2; // Sao 2 argumentos 
            if(pilha == NULL || pilhaPos  <= 1)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                raiz_aux = inicio;
                getArguments(arguments);

                CELL *arg_a = a->right, *arg_b = b->right;
                int a_int, b_int;

                if(arg_a->id == 'o')
                {
                    if (arg_a->type.operador == '@')
                    {
                        int posLivrePilha = pilhaPos;
                        pilhaPos += 2;
                        arg_a = reduct(arg_a);
                        pilhaPos = posLivrePilha;
                        pilha[pilhaPos].celula->right = arg_a;
                        inicio = raiz_aux;
                    }
                }
                if(arg_b->id == 'o')
                {
                    if (arg_b->type.operador == '@')
                    {
                        int posLivrePilha = pilhaPos;
                        pilhaPos += 2;
                        arg_b = reduct(arg_b);
                        pilhaPos = posLivrePilha;
                        pilha[pilhaPos].celula->right = arg_b;
                        inicio = raiz_aux;
                    }
                }
                resultSoma = (arg_a->type.number + arg_b->type.number);


                aux2 = create_CELL_number(resultSoma);

                if (!is_Pilha_Vazia(pilha))
                {
                    c = get_topo_pilha(pilha);
                    c->left = aux2;
                }
                else
                {
                    inicio = aux2;
                    pilha_insere(pilha, aux2);
                }
                

            }
            
            #ifdef COUNTERSOMA
            contSoma++;
            #endif
            break;

        case '-':
            arguments = 2; // Sao 2 argumentos 
            if(pilha == NULL || pilhaPos  <= 1)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                raiz_aux = inicio;
                getArguments(arguments);

                CELL *arg_a = a->right, *arg_b = b->right;
                int a_int, b_int;

                if(arg_a->id == 'o')
                {
                    if (arg_a->type.operador == '@')
                    {
                        int posLivrePilha = pilhaPos;
                        pilhaPos += 2;
                        arg_a = reduct(arg_a);
                        pilhaPos = posLivrePilha;
                        pilha[pilhaPos].celula->right = arg_a;
                        inicio = raiz_aux;
                    }
                }
                if(arg_b->id == 'o')
                {
                    if (arg_b->type.operador == '@')
                    {
                        int posLivrePilha = pilhaPos;
                        pilhaPos += 2;
                        arg_b = reduct(arg_b);
                        pilhaPos = posLivrePilha;
                        pilha[pilhaPos].celula->right = arg_b;
                        inicio = raiz_aux;
                    }
                }
                resultSoma = (arg_a->type.number - arg_b->type.number);

                aux2 = create_CELL_number(resultSoma);

                if (!is_Pilha_Vazia(pilha))
                {
                    c = get_topo_pilha(pilha);
                    c->left = aux2;
                }
                else
                {
                    inicio = aux2;
                    pilha_insere(pilha, aux2);
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
            arguments = 2; // Sao 2 argumentos 
            if(pilha == NULL || pilhaPos  <= 1)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                raiz_aux = inicio;
                getArguments(arguments);

                CELL *arg_a = a->right, *arg_b = b->right;
                int a_int, b_int;

                if(arg_a->id == 'o')
                {
                    if (arg_a->type.operador == '@')
                    {
                        int posLivrePilha = pilhaPos;
                        pilhaPos += 2;
                        arg_a = reduct(arg_a);
                        pilhaPos = posLivrePilha;
                        pilha[pilhaPos].celula->right = arg_a;
                        inicio = raiz_aux;
                    }
                }
                if(arg_b->id == 'o')
                {
                    if (arg_b->type.operador == '@')
                    {
                        int posLivrePilha = pilhaPos;
                        pilhaPos += 2;
                        arg_b = reduct(arg_b);
                        pilhaPos = posLivrePilha;
                        pilha[pilhaPos].celula->right = arg_b;
                        inicio = raiz_aux;
                    }
                }

                if (arg_a->type.number == arg_b->type.number)
                {
                    aux2 = create_CELL_leaf('K');
                }
                else
                    aux2 = create_CELL_leaf('k');
                

                if (!is_Pilha_Vazia(pilha))
                {
                    c = get_topo_pilha(pilha);
                    c->left = aux2;
                }
                else
                {
                    inicio = aux2;
                    pilha_insere(pilha, aux2);
                }
                

            }

            #ifdef COUNTERIGUAL
            contIgual++;
            #endif
            break;


        case '<':
            arguments = 2; // Sao 2 argumentos 
            if(pilha == NULL || pilhaPos  <= 1)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                raiz_aux = inicio;
                getArguments(arguments);

                CELL *arg_a = a->right, *arg_b = b->right;
                int a_int, b_int;

                if(arg_a->id == 'o')
                {
                    if (arg_a->type.operador == '@')
                    {
                        int posLivrePilha = pilhaPos;
                        pilhaPos += 2;
                        arg_a = reduct(arg_a);
                        pilhaPos = posLivrePilha;
                        pilha[pilhaPos].celula->right = arg_a;
                        inicio = raiz_aux;
                    }
                }
                if(arg_b->id == 'o')
                {
                    if (arg_b->type.operador == '@')
                    {
                        int posLivrePilha = pilhaPos;
                        pilhaPos += 2;
                        arg_b = reduct(arg_b);
                        pilhaPos = posLivrePilha;
                        pilha[pilhaPos].celula->right = arg_b;
                        inicio = raiz_aux;
                    }
                }

                if (arg_a->type.number < arg_b->type.number)
                {
                    aux2 = create_CELL_leaf('K');
                }
                else
                    aux2 = create_CELL_leaf('k');
                

                if (!is_Pilha_Vazia(pilha))
                {
                    c = get_topo_pilha(pilha);
                    c->left = aux2;
                }
                else
                {
                    inicio = aux2;
                    pilha_insere(pilha, aux2);
                }
                

            }
            #ifdef COUNTERMENOR
            contMenor++;
            #endif
            break;


        case '>':
            arguments = 2; // Sao 2 argumentos 
            if(pilha == NULL || pilhaPos  <= 1)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                raiz_aux = inicio;
                getArguments(arguments);

                CELL *arg_a = a->right, *arg_b = b->right;
                int a_int, b_int;

                if(arg_a->id == 'o')
                {
                    if (arg_a->type.operador == '@')
                    {
                        int posLivrePilha = pilhaPos;
                        pilhaPos += 2;
                        arg_a = reduct(arg_a);
                        pilhaPos = posLivrePilha;
                        pilha[pilhaPos].celula->right = arg_a;
                        inicio = raiz_aux;
                    }
                }
                if(arg_b->id == 'o')
                {
                    if (arg_b->type.operador == '@')
                    {
                        int posLivrePilha = pilhaPos;
                        pilhaPos += 2;
                        arg_b = reduct(arg_b);
                        pilhaPos = posLivrePilha;
                        pilha[pilhaPos].celula->right = arg_b;
                        inicio = raiz_aux;
                    }
                }

                if (arg_a->type.number > arg_b->type.number)
                {
                    aux2 = create_CELL_leaf('K');
                }
                else
                    aux2 = create_CELL_leaf('k');
                

                if (!is_Pilha_Vazia(pilha))
                {
                    c = get_topo_pilha(pilha);
                    c->left = aux2;
                }
                else
                {
                    inicio = aux2;
                    pilha_insere(pilha, aux2);
                }
                

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