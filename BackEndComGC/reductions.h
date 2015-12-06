/*
 * Reductions, this document provides functions to reduct the Graph
 * implemented in this project (Here is the implement of each funtion, 
 * the assign is in the Global Header File)
 */

#ifndef REDUCTIONS_H_
#define REDUCTIONS_H_
// getArguments(arguments,1,)
void getArguments(int arguments, int arit, int arg)
{
    if(arit == 0)
    {
        printf("\nArit = %d\n", arit);
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
    else if(arit == 1) // Eh um aritmetico, vou pegar argumento por argumento
    {
        // void getArguments(int arguments, int arit, int arg)
        printf("\nArit = %d\n", arit);

        if(arg == 0)
        {
          //  printf("A: ");
            a = get_topo_pilha(pilha);  // Guarda o '@' que guarda o 'a'
        //    if(a->right != NULL)
        //    print_graph(a->right);
      //  printf("\n");
         //   pilha_remove(pilha);       // Retira o @ que guarda o 'a'    
        }
        else if(arg == 1)
        {
            b = get_topo_pilha(pilha);  // Guarda o '@' que guarda o 'b'
        //    printf("B: ");
        //    if(b->right != NULL)
        //        print_graph(b->right);
        //    printf("\n");
          //  pilha_remove(pilha);       // Retira o @ que guarda o 'b'    
        }

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
    CELL* raiz_aux = inicio;;
    posRaizPilha = pilhaPos;
    pilha_insere(pilha, inicio);
    aux = inicio;
    printf("\nGraph Inicio: ");
    print_graph(inicio);
    printf("\n");
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
        
         // printf("operador = %c\n", aux->type.operador);
         // print_graph(inicio);
         // printf("\n");
         // getchar();
        printf("\nOP: %c\n",op->type.operador);
        switch (op->type.operador)
        {
        case 'K':
            arguments = 2; // Sao 2 argumentos 
            if(pilha == NULL || pilhaPos <= 1)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                getArguments(arguments,0,0); // Pegamos o a, b, mas falta saber se tem o elemento cauda ou nao
          
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
                getArguments(arguments,0,0);  // Pegamos o a, b, mas falta saber se tem o elemento cauda ou nao
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
            if(heapQtdCallGc(3))
            {
                garbage = 1;
                return inicio;
            }
            arguments = 3;  // Sao 3 argumentos 
            if(pilha == NULL || pilhaPos  <= 2)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                getArguments(arguments,0,0);  // Pegamos o a, b, c,  mas falta saber se tem o elemento cauda ou nao
           
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
            if(pilha[pilhaPos-1].celula->right == NULL || pilhaPos  <= 0)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                 getArguments(arguments,0,0); // Pegamos o a, mas falta saber se tem o elemento cauda ou nao
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
            if(heapQtdCallGc(2))
            {
                garbage = 1;
                return inicio;
            }
            arguments = 3; // Sao 3 argumentos 
            if(pilha == NULL || pilhaPos  <= 1)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                getArguments(arguments,0,0);  // Pegamos o a,b,c mas falta saber se tem o elemento cauda ou nao            
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
            if(heapQtdCallGc(2))
            {
                garbage = 1;
                return inicio;
            }
            arguments = 3; // Sao 3 argumentos 
            if(pilha == NULL || pilhaPos  <= 1)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                getArguments(arguments,0,0); // Pegamos o a,b,c mas falta saber se tem o elemento cauda ou nao         
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
            if(heapQtdCallGc(4))
            {
                garbage = 1;
                return inicio;
            }
            arguments = 4; // Sao 4 argumentos 
            if(pilha == NULL || pilhaPos  <= 1)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                getArguments(arguments,0,0);  // Pegamos o a,b,c,d mas falta saber se tem o elemento cauda ou nao   
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
            if(heapQtdCallGc(3))
            {
                garbage = 1;
                return inicio;
            }
            arguments = 4; // Sao 4 argumentos 
            if(pilha == NULL || pilhaPos  <= 1)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                getArguments(arguments,0,0); // Pegamos o a,b,c,d mas falta saber se tem o elemento cauda ou nao   
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
            if(heapQtdCallGc(3))
            {
                garbage = 1;
                return inicio;
            }
            arguments = 4; // Sao 4 argumentos 
            if(pilha == NULL || pilhaPos  <= 1)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                getArguments(arguments,0,0);  // Pegamos o a,b,c,d mas falta saber se tem o elemento cauda ou nao   
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
            if(heapQtdCallGc(1))
            {
                garbage = 1;
                return inicio;
            }
            arguments = 2; // Sao 2 argumentos 
            if(pilha == NULL || pilhaPos  <= 1)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
               // getArguments(arguments,1,)
                //getArguments(arguments,1,0); // Pega o ArgA
                CELL *arg_a = pilha[pilhaPos - 1].celula->right; 

                if(arg_a == NULL)
                    return inicio;
                else if(arg_a->id == 'o')
                {
                        printf("\nA: ");
                        print_graph(arg_a);
                        printf("\n");
                    if (arg_a->type.operador == '@')
                    {
                        int var1 = posRaizPilha;
                        int var2 = pilhaPos;
                        pilhaPos++;
                        arg_a = reduct(arg_a);
                        posRaizPilha = var1;
                        pilhaPos = var2;
                        pilha[pilhaPos - 1].celula->right = arg_a;
                        inicio = raiz_aux;

                        if(garbage == 1)
                            return inicio;
                    }
                }

                //getArguments(arguments,1,1); // Pegar o ArgB
               CELL *arg_b = pilha[pilhaPos - 2].celula->right;
             
                if(arg_b == NULL)
                    return inicio;
                else if(arg_b->id == 'o')
                {
                        printf("\nB: ");
                        print_graph(arg_b);
                        printf("\n");
                    if (arg_b->type.operador == '@')
                    {
                        int var1 = posRaizPilha;
                        int var2 = pilhaPos;
                        pilhaPos++;
                        arg_b = reduct(arg_b);
                        posRaizPilha = var1;
                        pilhaPos = var2;
                        pilha[pilhaPos - 2].celula->right = arg_b;
                        inicio = raiz_aux;

                        if(garbage == 1)
                            return inicio;
                    }
                }

                if(heapQtdCallGc(1))
                {
                    garbage = 1;
                    return inicio;
                }

                resultSoma = (arg_a->type.number + arg_b->type.number);
                printf("A : %d , B : %d\n",arg_a->type.number , arg_b->type.number);
                if(arg_a->left != NULL)
                     printf("Al : %d\n",arg_a->left->type.number); 
                if(arg_a->right != NULL)
                     printf("Ar : %d\n",arg_a->right->type.number); 
                aux2 = create_CELL_number(resultSoma);
                printf("AUX2 : %d, GR:  ", aux2->type.number);
                print_graph(aux2);
                printf("\n\n");

               

                if (!is_Pilha_Vazia(pilha))
                {
                   // c = get_topo_pilha(pilha);
                    c = pilha[pilhaPos - 3].celula;
                    c->left = aux2;
                }
                else
                {
                    inicio = aux2;
                   
                }
                
                pilha_remove(pilha);
                pilha_remove(pilha);
                pilha_insere(pilha, aux2);
              return inicio;
            }
            
            #ifdef COUNTERSOMA
            contSoma++;
            #endif
            return inicio;

        case '-':
            if(heapQtdCallGc(1))
            {
                garbage = 1;
                return inicio;
            }
            arguments = 2; // Sao 2 argumentos 
            if(pilha == NULL || pilhaPos  <= 1)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                raiz_aux = inicio;
                 getArguments(arguments,0,0); 
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
                        // pilha[pilhaPos].celula->right = arg_a;
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
                        // pilha[pilhaPos].celula->right = arg_b;
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
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    pilha_insere(pilha, aux2);
                }
                

            }
            #ifdef COUNTERSUB
            contSub++;
            #endif
            return inicio;

        case '*':
            if(heapQtdCallGc(1))
            {
                garbage = 1;
                return inicio;
            }
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
            if(heapQtdCallGc(1))
            {
                garbage = 1;
                return inicio;
            }
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
            if(heapQtdCallGc(1))
            {
                garbage = 1;
                return inicio;
            }
            arguments = 2; // Sao 2 argumentos 
            if(pilha == NULL || pilhaPos  <= 1)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                raiz_aux = inicio;
                getArguments(arguments,0,0);

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
                        // pilha[pilhaPos].celula->right = arg_a;
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
                        // pilha[pilhaPos].celula->right = arg_b;
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
            if(heapQtdCallGc(1))
            {
                garbage = 1;
               return inicio;
            }
            arguments = 2; // Sao 2 argumentos 
            if(pilha == NULL || pilhaPos  <= 1)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                raiz_aux = inicio;
                 getArguments(arguments,0,0); 

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
                        // pilha[pilhaPos].celula->right = arg_a;
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
                        // pilha[pilhaPos].celula->right = arg_b;
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
            if(heapQtdCallGc(1))
            {
                garbage = 1;
                return inicio;
            }
            arguments = 2; // Sao 2 argumentos 
            if(pilha == NULL || pilhaPos  <= 1)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                raiz_aux = inicio;
                 getArguments(arguments,0,0); 

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
                        // pilha[pilhaPos].celula->right = arg_a;
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
                        // pilha[pilhaPos].celula->right = arg_b;
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
            if(heapQtdCallGc(2))
            {
                garbage = 1;
                return inicio;;
            }
            arguments = 1; // Tem so 1 argumento
            if(pilha == NULL || pilhaPos  <= 1)
            {
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                 getArguments(arguments,0,0); 

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