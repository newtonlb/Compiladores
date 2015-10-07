#include "lista.h"

// Create a New Node
NODE* new_node()
{
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	return newNode;
}


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




void insertCaractToNode(char entrada, NODE* no)
{
	NODE* aux = no;
	aux->caract = entrada;
	aux->next = NULL;
	aux->down = NULL;
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
				inicio = new_node();
				insertCaractToNode(string[k], inicio);
			}
			else
			{
				NODE* aux = inicio;
				while(aux->next != NULL)
				{
					aux = aux->next;
				}
				aux->next = new_node();
				insertCaractToNode(string[k], aux->next);
			}
		}
		else if (string[k] == '(')
		{
			int novoj;
			novoj = searchParenthesis(k, string);
			if(inicio == NULL)
			{
				inicio = new_node();
				insertCaractToNode(string[k], inicio);
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
				aux->next = new_node();
				insertCaractToNode(string[k], aux->next);
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
	//printf("\n");
	//system("PAUSE");
	//printf("\n");
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

    if(inicio->down != NULL)
    {
        freeRecursao(inicio->down);
    }
    else
    {
        while(inicio->next != NULL)
        {
           NODE* aux = inicio->next;
           free(inicio);
           inicio = aux;
        }

    }
    free(inicio);
}

/// K a b => a
NODE* substitution_K(NODE* inicio)
{

    NODE* a = inicio->next;
    NODE* b = a->next;
    NODE* cauda = b->next;
    a->next = cauda;
    b->next = NULL;
    freeRecursao(b);
    free(inicio);
    return a;
}

NODE* clone(NODE* no)
{
  NODE* novo = NULL;

  if(no != NULL)
  {
     novo = new_node();
     novo->caract = no->caract;
     novo->next = clone(no->next);
     if(no->down != NULL)
     {
         novo->caract = '(';
         novo->down = clone(no->down);
     }
  }
  return novo;
}


/// S a b c => (ac)(bc) == ac(bc)
NODE* substitution_S(NODE* inicio)
{
	NODE* a = inicio->next;
	NODE* b = a->next;
	NODE* c = b->next;
	NODE* cauda = c->next;
    NODE* novoC = clone(c);
    NODE* aux = new_node();

    a->next = c;
    c->next = aux;
    aux->caract = '(';
    aux->down = b;
    b->next = novoC;
    novoC->next = NULL;
    aux->next = cauda;
    free(inicio);

	return a;
}

/// I a => a
NODE* substitution_I(NODE* inicio)
{
	NODE* a = inicio->next;
	free(inicio);
	return a;
}

/// B f g x => f(gx)
NODE* substitution_B(NODE* inicio)
{
	NODE* f = inicio->next;
	NODE* g = f->next;
	NODE* x = g->next;
	NODE* cauda = x->next;
	NODE* aux = new_node();
	f->next = aux;
	aux->caract = '(';
	aux->next = cauda;
	aux->down = g;
	g->next = x;
	x->next = NULL;
	free(inicio);
	return f;
}


/// C f x y => f y x
NODE* substitution_C(NODE* inicio)
{
	NODE* f = inicio->next;
	NODE* x = f->next;
	NODE* y = x->next;
	NODE* cauda = y->next;
	f->next = y;
	y->next = x;
	x->next = cauda;
	free(inicio);
	return f;
}

/// S' a b c d => a(bd)(cd)
NODE* substitution_s(NODE* inicio)
{
	NODE* a = inicio->next;
	NODE* b = a->next;
	NODE* c = b->next;
	NODE* d = c->next;
	NODE* novod = clone(d);
	NODE* cauda = d->next;
	NODE* aux1 = new_node();
	NODE* aux2 = new_node();
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
	//system("PAUSE");
	free(inicio);
	return a;

}

/// B' a b c d => ab(cd)
NODE* substitution_b(NODE* inicio)
{
	NODE* a = inicio->next;
	NODE* b = a->next;
	NODE* c = b->next;
	NODE* d = c->next;
	NODE* cauda = d->next;
	NODE* aux = new_node();
	a->next = b;
	b->next = aux;
	aux->caract = '(';
	aux->next = cauda;
	aux->down = c;
	c->next = d;
	d->next = NULL;
	free(inicio);
	return a;
}

/// C' a b c d => a(bd)c
NODE* substitution_c(NODE* inicio)
{
	NODE* a = inicio->next;
	NODE* b = a->next;
	NODE* c = b->next;
	NODE* d = c->next;
	NODE* cauda = d->next;
	NODE* aux = new_node();
	a->next = aux;
	aux->caract = '(';
	aux->next = c;
	aux->down = b;
	b->next = d;
	d->next = NULL;
	c->next = cauda;
	free(inicio);
	return a;
}


int main()
{
	int tamanho = strlen(string);
	int i = 0, redutible = 1;
	NODE* inicio = create_list(0,tamanho,string);
	printf("Entrada = ");
    imprime(inicio);
	printf("\n");

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
				if (inicio->next->next == NULL)
				{
					redutible = 0;
					break;
				}
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
				inicio = substitution_I(inicio);
				break;
			case 'K':
				#ifdef COUNTERK
         			         contK++;
    				#endif
				contK++;
				if (inicio->next->next == NULL)
				{
					redutible = 0;
					break;
				}
				inicio = substitution_K(inicio);
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
				inicio = substitution_C(inicio);
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
				inicio = substitution_B(inicio);
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
				inicio = substitution_b(inicio);
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
				inicio = substitution_c(inicio);
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
				inicio = substitution_S(inicio);
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
				inicio = substitution_s(inicio);
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
