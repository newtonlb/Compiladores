/*
 * Reductions, this document provides functions to reduct the Graph
 * implemented in this project (Here is the implement of each funtion, 
 * the assign is in the Global Header File)
 */

#ifndef REDUCTIONS_H_
#define REDUCTIONS_H_

void getArguments(int arguments, int arit, int arg)
{
    if(arit == 0)
    {
        //printf("\nArit = %d\n", arit);
        if(arguments >= 1)
        {
            a = pilha[pilhaPos - 1].celula->right;
           // a = get_topo_pilha(pilha)->right;  // Guarda o '@' que guarda o 'a'
           // pilha_remove(pilha);       // Retira o @ que guarda o 'a'    
        }

        if(arguments >= 2)
        {
            b= pilha[pilhaPos - 2].celula->right;
         //   b = get_topo_pilha(pilha)->right;  // Guarda o '@' que guarda o 'b'
         //   pilha_remove(pilha);       // Retira o @ que guarda o 'b'
        }
        
        if(arguments >= 3)
        {
            c = pilha[pilhaPos - 3].celula->right;
           // c = get_topo_pilha(pilha)->right;  // Guarda o '@' que guarda o 'c'
        //    pilha_remove(pilha);       // Retira o @ que guarda o 'c'
        }

        if(arguments >= 4)
        {
            d = pilha[pilhaPos - 4].celula->right;
           // d = get_topo_pilha(pilha)->right;  // Guarda o '@' que guarda o 'd'
         //   pilha_remove(pilha);       // Retira o @ que guarda o 'd'
        }
    }
    else if(arit == 1) // Eh um aritmetico, vou pegar argumento por argumento
    {
        if(arg == 0)
        {
            a = get_topo_pilha(pilha);  // Guarda o '@' que guarda o 'a'  
        }
        else if(arg == 1)
        {
            b = get_topo_pilha(pilha);  // Guarda o '@' que guarda o 'b'   
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
    //printf("\nGraph Inicio: ");
    //print_graph(inicio);
    //printf("\n");
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
        
          //printf("operador = %c\n", op->type.operador);
             //printf("\nOP: %c\n",op->type.operador);
            //print_graph(inicio);
          //printf("\n");
          //getchar();
       
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
                CELL* arg_a = a;

                if((pilhaPos-2-posRaizPilha) > 0) // Tem cauda, vai ter que mudar o ponteiro
                {
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    cauda = get_topo_pilha(pilha);  // o '@' que guarda o c
                    cauda->left = arg_a;
                }
                else   // Nao tem cauda
                {
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    inicio = arg_a;
                    pilha_insere(pilha, arg_a);
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
                
                getArguments(arguments,0,0);
                CELL* arg_b = b;// Pegamos o a, b, mas falta saber se tem o elemento cauda ou nao
    
                if((pilhaPos-2-posRaizPilha) > 0) // Tem cauda, vai ter que mudar o ponteiro
                {
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    cauda = get_topo_pilha(pilha);  // o '@' que guarda o c
                    cauda->left = arg_b;
                }
                else   // Nao tem cauda
                {
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    inicio = arg_b;
                    pilha_insere(pilha, arg_b);
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
                CELL* arg_a = a;
                CELL* arg_b = b;
                CELL* arg_c = c;
                
           
                aux2 = create_CELL_parenthesis(NULL, NULL);
                aux2->left = create_CELL_parenthesis(NULL, NULL);
                aux2->right = create_CELL_parenthesis(NULL, NULL);

                aux2->left->left = arg_a;
                aux2->left->right = arg_c;
                aux2->right->left = arg_b;
                aux2->right->right = arg_c;

                if((pilhaPos-3-posRaizPilha) > 0) // Tem cauda, vai ter que mudar o ponteiro
                {
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    cauda = get_topo_pilha(pilha);  // o '@' que guarda o c
                    cauda->left = aux2;
                }
                else   // Nao tem cauda
                {
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    pilha_remove(pilha);
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
                CELL* arg_a = a;

                if((pilhaPos-1-posRaizPilha) > 0) // Tem cauda, vai ter que mudar o ponteiro
                {
                    pilha_remove(pilha);
                    cauda = get_topo_pilha(pilha);  // o '@' que guarda o c
                    cauda->left = arg_a;
                }
                else   // Nao tem cauda
                {
                    pilha_remove(pilha);
                    inicio = arg_a;
                    pilha_insere(pilha, arg_a);
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
                CELL* arg_a = a;
                CELL* arg_b = b;
                CELL* arg_c = c;
                aux2 = create_CELL_parenthesis(NULL,NULL);
                aux2->right = create_CELL_parenthesis(NULL, NULL);
                aux2->left = arg_a;
                aux2->right->left = arg_b;
                aux2->right->right = arg_c;
               
                if((pilhaPos-3-posRaizPilha) > 0) // Tem cauda, vai ter que mudar o ponteiro
                {
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    cauda = get_topo_pilha(pilha);  // o '@' que guarda o c
                    cauda->left = aux2;
                }
                else   // Nao tem cauda
                {
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    pilha_remove(pilha);
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
                CELL* arg_a = a;
                CELL* arg_b = b;
                CELL* arg_c = c;
                
                aux2 = create_CELL_parenthesis(NULL, NULL);
                aux2->left = create_CELL_parenthesis(NULL, NULL);
                aux2->right = arg_b;
                aux2->left->right = arg_c;
                aux2->left->left = arg_a;

                if((pilhaPos-3-posRaizPilha) > 0) // Tem cauda, vai ter que mudar o ponteiro
                {
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    cauda = get_topo_pilha(pilha);  // o '@' que guarda o c
                    cauda->left = aux2;
                }
                else   // Nao tem cauda
                {
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    inicio = aux2;
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
                CELL* arg_a = a;
                CELL* arg_b = b;
                CELL* arg_c = c;
                CELL* arg_d = d;
                aux2 = create_CELL_parenthesis(NULL, NULL);
                aux2->left = create_CELL_parenthesis(NULL, NULL);
                aux2->left->right = create_CELL_parenthesis(NULL, NULL);
                aux2->right = create_CELL_parenthesis(NULL, NULL);
                aux2->left->left = arg_a;
                aux2->left->right->left = arg_b;
                aux2->left->right->right = arg_d;
                aux2->right->left = arg_c;
                aux2->right->right = arg_d;

                if((pilhaPos-4-posRaizPilha) > 0) // Tem cauda, vai ter que mudar o ponteiro
                {
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    cauda = get_topo_pilha(pilha);  // o '@' que guarda o c
                    cauda->left = aux2;
                }
                else   // Nao tem cauda
                {
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    inicio = aux2;
                    pilha_insere(pilha, aux2);
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
                CELL* arg_a = a;
                CELL* arg_b = b;
                CELL* arg_c = c;
                CELL* arg_d = d;
                aux2 = create_CELL_parenthesis(NULL, NULL);
                aux2->right = create_CELL_parenthesis(NULL, NULL);
                aux2->left = create_CELL_parenthesis(NULL, NULL);
                aux2->left->left = arg_a;
                aux2->left->right = arg_b;
                aux2->right->left = arg_c;
                aux2->right->right = arg_d;

                if((pilhaPos-4-posRaizPilha) > 0) // Tem cauda, vai ter que mudar o ponteiro
                {
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    cauda = get_topo_pilha(pilha);  // o '@' que guarda o c
                    cauda->left = aux2;
                }
                else   // Nao tem cauda
                {
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    inicio = aux2;
                    pilha_insere(pilha, aux2);
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
                CELL* arg_a = a;
                CELL* arg_b = b;
                CELL* arg_c = c;
                CELL* arg_d = d;
                aux2 = create_CELL_parenthesis(NULL, NULL);
                aux2->left = create_CELL_parenthesis(NULL, NULL);
                aux2->left->right = create_CELL_parenthesis(NULL, NULL);
                aux2->left->left = arg_a;
                aux2->left->right->left = arg_b;
                aux2->left->right->right = arg_d;
                aux2->right = arg_c;

                if((pilhaPos-4-posRaizPilha) > 0) // Tem cauda, vai ter que mudar o ponteiro
                {
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    cauda = get_topo_pilha(pilha);  // o '@' que guarda o c
                    cauda->left = aux2;
                }
                else   // Nao tem cauda
                {
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    inicio = aux2;
                    pilha_insere(pilha, aux2);
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
                        /*printf("\nA: ");
                        print_graph(arg_a);
                        printf("\n");*/
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
                        /*printf("\nB: ");
                        print_graph(arg_b);
                        printf("\n");*/
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
                //printf("A : %d , B : %d\n",arg_a->type.number , arg_b->type.number);
                //if(arg_a->left != NULL)
                     //printf("Al : %d\n",arg_a->left->type.number);
                //if(arg_a->right != NULL)
                     //printf("Ar : %d\n",arg_a->right->type.number);
                aux2 = create_CELL_number(resultSoma);
                //printf("AUX2 : %d, GR:  ", aux2->type.number);
                //print_graph(aux2);
                //printf("\n\n");

                if((pilhaPos-2-posRaizPilha) > 0) // Tem cauda, vai ter que mudar o ponteiro
                {
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    cauda = get_topo_pilha(pilha);  // o '@' que guarda o c
                    cauda->left = aux2;
                }
                else   // Nao tem cauda
                {
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    inicio = aux2;
                    pilha_insere(pilha, aux2);
                }

            //  return inicio;
            }
            
            #ifdef COUNTERSOMA
            contSoma++;
            #endif
             //   return aux2;
            break;
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
                    // getArguments(arguments,1,)
                    //getArguments(arguments,1,0); // Pega o ArgA
                    CELL *arg_a = pilha[pilhaPos - 1].celula->right;
                    
                    
                    if(arg_a == NULL)
                        return inicio;
                    else if(arg_a->id == 'o')
                    {
                        /*printf("\nA: ");
                        print_graph(arg_a);
                        printf("\n");*/
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
                        /*printf("\nB: ");
                        print_graph(arg_b);
                        printf("\n");*/
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
                    
                    resultSoma = (arg_a->type.number - arg_b->type.number);
                    //printf("A : %d , B : %d\n",arg_a->type.number , arg_b->type.number);
                    //if(arg_a->left != NULL)
                        //printf("Al : %d\n",arg_a->left->type.number);
                    //if(arg_a->right != NULL)
                        //printf("Ar : %d\n",arg_a->right->type.number);
                    aux2 = create_CELL_number(resultSoma);
                    //printf("AUX2 : %d, GR:  ", aux2->type.number);
                    //print_graph(aux2);
                    //printf("\n\n");
                    
                    
                    
                    if((pilhaPos-2-posRaizPilha) > 0) // Tem cauda, vai ter que mudar o ponteiro
                    {
                        pilha_remove(pilha);
                        pilha_remove(pilha);
                        cauda = get_topo_pilha(pilha);  // o '@' que guarda o c
                        cauda->left = aux2;
                    }
                    else   // Nao tem cauda
                    {
                        pilha_remove(pilha);
                        pilha_remove(pilha);
                        inicio = aux2;
                        pilha_insere(pilha, aux2);
                    }
                }
            #ifdef COUNTERSUB
            contSub++;
            #endif
              //  return aux2;
            break;

        case '*':
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
                        //printf("\nA: ");
                        //print_graph(arg_a);
                        //printf("\n");
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
                        //printf("\nB: ");
                        //print_graph(arg_b);
                        //printf("\n");
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
                    
                    resultSoma = (arg_a->type.number * arg_b->type.number);
                    //printf("A : %d , B : %d\n",arg_a->type.number , arg_b->type.number);
                    //if(arg_a->left != NULL)
                        //printf("Al : %d\n",arg_a->left->type.number);
                    //if(arg_a->right != NULL)
                        //printf("Ar : %d\n",arg_a->right->type.number);
                    aux2 = create_CELL_number(resultSoma);
                    //printf("AUX2 : %d, GR:  ", aux2->type.number);
                    //print_graph(aux2);
                    //printf("\n\n");
                    
                    if((pilhaPos-2-posRaizPilha) > 0) // Tem cauda, vai ter que mudar o ponteiro
                    {
                        pilha_remove(pilha);
                        pilha_remove(pilha);
                        cauda = get_topo_pilha(pilha);  // o '@' que guarda o c
                        cauda->left = aux2;
                    }
                    else   // Nao tem cauda
                    {
                        pilha_remove(pilha);
                        pilha_remove(pilha);
                        inicio = aux2;
                        pilha_insere(pilha, aux2);
                    }
                }
            #ifdef COUNTERMULT
            contMult++;
            #endif
                //return aux2;
            break;

        case '/':
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
                        //printf("\nA: ");
                        //print_graph(arg_a);
                        //printf("\n");
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
                        //printf("\nB: ");
                        //print_graph(arg_b);
                        //printf("\n");
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
                    
                    resultSoma = (arg_a->type.number / arg_b->type.number);
                    //printf("A : %d , B : %d\n",arg_a->type.number , arg_b->type.number);
                    //if(arg_a->left != NULL)
                        //printf("Al : %d\n",arg_a->left->type.number);
                    //if(arg_a->right != NULL)
                        //printf("Ar : %d\n",arg_a->right->type.number);
                    aux2 = create_CELL_number(resultSoma);
                    //printf("AUX2 : %d, GR:  ", aux2->type.number);
                    //print_graph(aux2);
                    //printf("\n\n");
                    if((pilhaPos-2-posRaizPilha) > 0) // Tem cauda, vai ter que mudar o ponteiro
                    {
                        pilha_remove(pilha);
                        pilha_remove(pilha);
                        cauda = get_topo_pilha(pilha);  // o '@' que guarda o c
                        cauda->left = aux2;
                    }
                    else   // Nao tem cauda
                    {
                        pilha_remove(pilha);
                        pilha_remove(pilha);
                        inicio = aux2;
                        pilha_insere(pilha, aux2);
                    }
                }
            #ifdef COUNTERDIV
            contDiv++;
            #endif
               // return aux2;
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
                    // getArguments(arguments,1,)
                    //getArguments(arguments,1,0); // Pega o ArgA
                    CELL *arg_a = pilha[pilhaPos - 1].celula->right;
                    
                    
                    if(arg_a == NULL)
                        return inicio;
                    else if(arg_a->id == 'o')
                    {
                        //printf("\nA: ");
                        //print_graph(arg_a);
                        //printf("\n");
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
                        //printf("\nB: ");
                        //print_graph(arg_b);
                        //printf("\n");
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
                    
                    if(arg_a->type.number == arg_b->type.number)
                    {
                        aux2 = create_CELL_leaf('K');
                    }
                    else
                    {
                        aux2 = create_CELL_leaf('k');
                    }
                    
                        //printf("A : %d , B : %d\n",arg_a->type.number , arg_b->type.number);
                        //if(arg_a->left != NULL)
                        //printf("Al : %d\n",arg_a->left->type.number);
                    //if(arg_a->right != NULL)
                        //printf("Ar : %d\n",arg_a->right->type.number);
                    //aux2 = create_CELL_number(resultSoma);
                    //printf("AUX2 : %c, GR:  ", aux2->type.operador);
                    //print_graph(aux2);
                    //printf("\n\n");
                    
                    if((pilhaPos-2-posRaizPilha) > 0) // Tem cauda, vai ter que mudar o ponteiro
                    {
                        pilha_remove(pilha);
                        pilha_remove(pilha);
                        cauda = get_topo_pilha(pilha);  // o '@' que guarda o c
                        cauda->left = aux2;
                    }
                    else   // Nao tem cauda
                    {
                        pilha_remove(pilha);
                        pilha_remove(pilha);
                        inicio = aux2;
                        pilha_insere(pilha, aux2);
                    }
                }

            #ifdef COUNTERIGUAL
            contIgual++;
            #endif
                //return aux2;
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
                    // getArguments(arguments,1,)
                    //getArguments(arguments,1,0); // Pega o ArgA
                    CELL *arg_a = pilha[pilhaPos - 1].celula->right;
                    
                    
                    if(arg_a == NULL)
                        return inicio;
                    else if(arg_a->id == 'o')
                    {
                        /*printf("\nA: ");
                        print_graph(arg_a);
                        printf("\n");*/
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
                        /*printf("\nB: ");
                        print_graph(arg_b);
                        printf("\n");*/
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
                    
                    if(arg_a->type.number < arg_b->type.number)
                    {
                        aux2 = create_CELL_leaf('K');
                    }
                    else
                    {
                        aux2 = create_CELL_leaf('k');
                    }
                    
                    //printf("A : %d , B : %d\n",arg_a->type.number , arg_b->type.number);
                    //if(arg_a->left != NULL)
                        //printf("Al : %d\n",arg_a->left->type.number);
                    //if(arg_a->right != NULL)
                        //printf("Ar : %d\n",arg_a->right->type.number);
                    //aux2 = create_CELL_number(resultSoma);
                    //printf("AUX2 : %c, GR:  ", aux2->type.operador);
                    //print_graph(aux2);
                    //printf("\n\n");
                    
                    if((pilhaPos-2-posRaizPilha) > 0) // Tem cauda, vai ter que mudar o ponteiro
                    {
                        pilha_remove(pilha);
                        pilha_remove(pilha);
                        cauda = get_topo_pilha(pilha);  // o '@' que guarda o c
                        cauda->left = aux2;
                    }
                    else   // Nao tem cauda
                    {
                        pilha_remove(pilha);
                        pilha_remove(pilha);
                        inicio = aux2;
                        pilha_insere(pilha, aux2);
                    }
                    //return aux2;
                }
            #ifdef COUNTERMENOR
            contMenor++;
            #endif
              //  return aux2;
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
                        //printf("\nB: ");
                        //print_graph(arg_b);
                        //printf("\n");
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
                    
                    if(arg_a->type.number > arg_b->type.number)
                    {
                        aux2 = create_CELL_leaf('K');
                    }
                    else
                    {
                        aux2 = create_CELL_leaf('k');
                    }
                    
                   /* printf("A : %d , B : %d\n",arg_a->type.number , arg_b->type.number);
                    if(arg_a->left != NULL)
                        printf("Al : %d\n",arg_a->left->type.number);
                    if(arg_a->right != NULL)
                        printf("Ar : %d\n",arg_a->right->type.number);
                    //aux2 = create_CELL_number(resultSoma);
                    printf("AUX2 : %c, GR:  ", aux2->type.operador);
                    print_graph(aux2);
                    printf("\n\n");
                    
                    */
                    if((pilhaPos-2-posRaizPilha) > 0) // Tem cauda, vai ter que mudar o ponteiro
                    {
                        pilha_remove(pilha);
                        pilha_remove(pilha);
                        cauda = get_topo_pilha(pilha);  // o '@' que guarda o c
                        cauda->left = aux2;
                    }
                    else   // Nao tem cauda
                    {
                        pilha_remove(pilha);
                        pilha_remove(pilha);
                        inicio = aux2;
                        pilha_insere(pilha, aux2);
                    }
                }
            #ifdef COUNTERMAIOR
            contMaior++;
            #endif
               // return aux2;
            break;

        case 'Y':
            if(heapQtdCallGc(2))
            {
                garbage = 1;
                return inicio;;
            }
            arguments = 1; // Tem so 1 argumento
            if(pilha == NULL || (pilhaPos -posRaizPilha)  <= 0)
            {//printf("chegou aqui\n");
                reductible = 0; // chegou ao fim
                break;
            }
            else
            {
                 getArguments(arguments,0,0);
                CELL* arg_a = a;
                
                //print_graph(a);
                //printf("\n\n");
                
                aux2 = create_CELL_parenthesis(NULL, NULL);
                aux2->left = arg_a;
                aux2->right = create_CELL_parenthesis(NULL, NULL);
                aux2->right->right = arg_a;
                aux2->right->left = op;
                //print_graph(aux2);

                if((pilhaPos-1-posRaizPilha) > 0) // Tem cauda, vai ter que mudar o ponteiro
                {
                    pilha_remove(pilha);
                    cauda = get_topo_pilha(pilha);  // o '@' que guarda o c
                    cauda->left = aux2;
                }
                else   // Nao tem cauda
                {
                    pilha_remove(pilha);
                    pilha_remove(pilha);
                    inicio = aux2;
                    pilha_insere(pilha, aux2);
                }
            }
            #ifdef COUNTERY
            contY++;
            #endif
            return inicio;
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