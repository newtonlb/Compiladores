#include "lista.h"


// Search Parenthesis in Initial String
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


NODE* create_list(int i, int j, char* string)
{
	NODE* inicio = NULL;
	int k = 0;
	for (k = i; k <= j && string[k] != ')' ; k++)
	{
		if (string[k] != '(')
		{
			if (inicio == NULL)
			{
				inicio = (NODE*)malloc(sizeof(NODE));
				inicio->caract = string[k];
			}
			else
			{
				NODE* aux = inicio;
				while(aux->next != NULL)
				{
					aux = aux->next;
				}
				aux->next = (NODE*)malloc(sizeof(NODE));
				aux->next->caract = string[k];
			}
		}
		else
		{
			int novoj;
			novoj = searchParenthesis(k, string);
			if(inicio == NULL)
			{
				inicio = (NODE*)malloc(sizeof(NODE));
				inicio->caract = string[k];
				inicio->down = create_list(k + 1, novoj - 1, string);
				k = novoj;
			}
			else
			{
				NODE* aux = inicio;
				while(aux->next != NULL)
				{
					aux = aux->next;
				}
				aux->next = (NODE*)malloc(sizeof(NODE));
				aux->next->caract = string[k];
				aux->next->down = create_list(k + 1, novoj - 1 , string);
				k = novoj;
			}
		}
	}
	return inicio;
}

void imprime(NODE* no)
{
	NODE* aux = no;
	while(aux != NULL)
	{
		if (aux->caract != '(')
		{
			printf("%c", aux->caract);
		}
		else
		{
			printf("(");
			imprime(aux->down);
			printf(")");
		}
		aux = aux->next;
	}
}

NODE* retiraParenteses(NODE* inicio)
{
  NODE* retorno;
  NODE* aux = inicio;
  if(aux->caract == '(')
  {
    retorno = aux->down;
    aux = aux->down;
    while(aux->next != NULL)
    {
    	aux = aux->next;
    }
    aux->next = inicio->next;
  }
  free(inicio);


return retorno;
}



void freeRecursao(NODE* inicio)
{
    while(inicio != NULL)
    {
    	if(inicio->caract == '(')
    		freeRecursao(inicio->down);
    	//else
    	//{
		NODE* aux = inicio->next;
		free(inicio);
		inicio = aux;
    	//}
    }
}




NODE* clone(NODE* inicio)
{
	NODE* novoinicio;
	NODE* clonado = (NODE*)malloc(sizeof(NODE));
	NODE* aux = inicio;

	novoinicio = clonado;

	while(aux->next != NULL)
	{
		if(aux->caract != '(')
		{
			clonado->caract = aux->caract;
		}
		else
		{
			clonado->caract = '(';
			clonado->down = clone(aux->down);
		}

		aux = aux->next;
		clonado->next = (NODE*)malloc(sizeof(NODE));
		clonado = clonado->next;
	} 

	if(aux->caract != '(')
	{
		clonado->caract = aux->caract;
	}
	else
	{
		clonado->caract = '(';
		clonado->down = clone(aux->down);
	}

	clonado->next = NULL;

	return novoinicio;
}




int main()
{
	int tamanho = strlen(string);
	
	int i = 0, redutible = 1;
	NODE* a,*b,*c,*d,*f,*x,*y, *g,*cauda, *aux, *aux1, *aux2, *novod, *novoC;	
	
	NODE* inicio = create_list(0,tamanho,string);
	
	while(redutible == 1)
	{
		#ifdef ITERATIONS
          		 iterations++;
    		#endif
		switch(inicio->caract)
		{
			case '(':
				#ifdef COUNTERREMOVEPARENTESES
          				 contRemoveParenteses++;
    				#endif
				
				inicio = retiraParenteses(inicio);
				break;
			case 'I':
				#ifdef COUNTERI
        				 contI++;
    				#endif
				if (inicio->next->next == NULL)
				{
					redutible = 0;
					break;
				}
				aux = inicio;
				inicio = inicio->next;
				aux->next = NULL;
				free(aux);
				break;
			case 'K':
				#ifdef COUNTERK
         			         contK++;
    				#endif
				if (inicio->next->next == NULL)
				{
					redutible = 0;
					break;
				}
				//inicio = substitution_K(inicio);
				#ifdef SUBSTITUTION_K
					a = inicio->next;
	   				b = a->next;
	    			cauda = b->next;
	    			a->next = cauda;
				    b->next = NULL;
				    freeRecursao(b);
				    inicio->next = NULL;
				    free(inicio);
				    inicio = a;
			    #endif

				break;
			case 'C':
				#ifdef COUNTERC
          			  	contC++;
    				#endif
				if (inicio->next->next == NULL)
				{
					redutible = 0;
					break;
				}
				//inicio = substitution_C(inicio);
				#ifdef SUBSTITUTION_C
					f = inicio->next;
					x = f->next;
					y = x->next;
					cauda = y->next;
					f->next = y;
					y->next = x;
					x->next = cauda;
					free(inicio);
					inicio = f;
				#endif
				break;
			case 'B':
				#ifdef COUNTERB
         			   	contB++;
   				#endif
				if (inicio->next->next == NULL)
				{
					redutible = 0;
					break;
				}
				//inicio = substitution_B(inicio);
				#ifdef SUBSTITUTION_B
					f = inicio->next;
					g = f->next;
					x = g->next;
					cauda = x->next;
					aux = (NODE*)malloc(sizeof(NODE));
					f->next = aux;
					aux->caract = '(';
					aux->next = cauda;
					aux->down = g;
					g->next = x;
					x->next = NULL;
					free(inicio);
					inicio = f;
				#endif
				break;
			case 'b':
				#ifdef COUNTERBLINHA
         			 	contBlinha++;
    				#endif
				if (inicio->next->next == NULL)
				{
					redutible = 0;
					break;
				}
				//inicio = substitution_b(inicio);
				#ifdef SUBSTITUTION_BLINHA
					a = inicio->next;
					b = a->next;
					c = b->next;
					d = c->next;
					cauda = d->next;
					aux = (NODE*)malloc(sizeof(NODE));
					a->next = b;
					b->next = aux;
					aux->caract = '(';
					aux->next = cauda;
					aux->down = c;
					c->next = d;
					d->next = NULL;
					free(inicio);
					inicio = a;
				#endif
				break;
			case 'c':
				#ifdef COUNTERCLINHA
           				contClinha++;
  				#endif
				if (inicio->next->next == NULL)
				{
					redutible = 0;
					break;
				}
				//inicio = substitution_c(inicio);
				#ifdef SUBSTITUTION_CLINHA
					a = inicio->next;
					b = a->next;
					c = b->next;
					d = c->next;
					cauda = d->next;
					aux = (NODE*)malloc(sizeof(NODE));
					a->next = aux;
					aux->caract = '(';
					aux->next = c;
					aux->down = b;
					b->next = d;
					d->next = NULL;
					c->next = cauda;
					free(inicio);
					inicio = a;
				#endif
				break;
			case 'S':
				#ifdef COUNTERS
           				contS++;
    				#endif
				if (inicio->next->next == NULL)
				{
					redutible = 0;
					break;
				}
				//inicio = substitution_S(inicio);

				#ifdef SUBSTITUTION_S
				    a = inicio->next;
				    b = a->next;
				    c = b->next;
				    cauda = c->next;
				    c->next = NULL;
				    novoC = clone(c);
				    aux = (NODE*)malloc(sizeof(NODE));

				    a->next = c;
				    c->next = aux;
				    aux->caract = '(';
				    aux->down = b;
				    b->next = novoC;
				    novoC->next = NULL;
				    aux->next = cauda;
				    inicio->next = NULL;
				    free(inicio);
				    inicio = a;
				#endif

				break;
			case 's':
			    	#ifdef COUNTERSLINHA
            				contSlinha++;
    				#endif
				if (inicio->next->next == NULL)
				{
					redutible = 0;
					break;
				}
				//inicio = substitution_s(inicio);
				#ifdef SUBSTITUTION_SLINHA
					a = inicio->next;
					b = a->next;
					c = b->next;
					d = c->next;
					cauda = d->next;
					d->next = NULL;		
					novod = clone(d);
					
					aux1 = (NODE*)malloc(sizeof(NODE));
					aux2 = (NODE*)malloc(sizeof(NODE));
					a->next = aux1;
					aux1->caract = '(';
					aux1->next = aux2;
					aux1->down = b;
					b->next = d;
					d->next = NULL;
					aux2->caract = '(';
					aux2->down = c;
					c->next = novod;
					novod->next = NULL;
					aux2->next = cauda;
					inicio->next = NULL;
					free(inicio);
					inicio = a;
				#endif
				break;
			default:
				redutible = 0;
				break;
		}
	}



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
    	#endif

	imprime(inicio);
	printf("\n");

	return 0;
}
