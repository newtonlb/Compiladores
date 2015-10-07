#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int redutible = 0;


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

typedef struct node
{
	char caract;
	struct node *next;
	struct node *down;
} NODE;


NODE* new_node()
{
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	return newNode;
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

NODE* clone(NODE* inicio)
{
	NODE* novo = new_node();
	NODE* novoinicio = novo;
	NODE* aux = inicio;
	while(aux->next != NULL)
	{
		novo->caract = aux->caract;
		novo->next = new_node();
		if(aux->down != NULL)
		{
			novo->down = clone(aux->down);
		}
		aux = aux->next;
		novo = novo->next;
	}
	return novoinicio;
}

/// Bugado ::  S a b c => (ac)(bc) == ac(bc)
NODE* substitution_S(NODE* inicio)//NÃO TERMINADA!!!! BUGANDO PARA CARELEO
{
	NODE* a = inicio->next;
	NODE* b = a->next;
	NODE* c = b->next;
	NODE* cauda = c->next;
	NODE* aux1 = new_node();
	NODE* aux2 = new_node();
	NODE* novoc = clone(c);
	aux1->caract = '(';
	aux1->down = a;
	aux1->next = aux2;
	a->next = c;
	c->next = NULL;
	aux2->caract = '(';
	aux2->down = b;
	aux2->next = cauda;
	b->next = novoc;
	novoc->next = NULL;
	free(inicio);

	return aux1;
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
	char *string = "s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)((s(cBI(SII))I(B(cBI(SII))I)(KK))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K))K)";
	int tamanho = strlen(string);
	int i = 0, redutible = 1;
	NODE* inicio = create_list(0,tamanho,string);
	//imprime(inicio);
    
	while(redutible == 1)
	{
		switch(inicio->caract)
		{
			case '(':
				if (inicio->next->next == NULL)
				{
					redutible = 0;
					break;
				}
				inicio = retiraParenteses(inicio);
				break;
			case 'I':
				if (inicio->next->next == NULL)
				{
					redutible = 0;
					break;
				}
				inicio = substitution_I(inicio);
				break;
			case 'K':
				if (inicio->next->next == NULL)
				{
					redutible = 0;
					break;
				}
				inicio = substitution_K(inicio);
				break;
			case 'C':
				if (inicio->next->next == NULL)
				{
					redutible = 0;
					break;
				}
				inicio = substitution_C(inicio);
				break;
			case 'B':
				if (inicio->next->next == NULL)
				{
					redutible = 0;
					break;
				}
				inicio = substitution_B(inicio);
				break;
			case 'b':
				if (inicio->next->next == NULL)
				{
					redutible = 0;
					break;
				}
				inicio = substitution_b(inicio);
				break;
			case 'c':
				if (inicio->next->next == NULL)
				{
					redutible = 0;
					break;
				}
				inicio = substitution_c(inicio);
				break;
			case 'S':
				if (inicio->next->next == NULL)
				{
					redutible = 0;
					break;
				}
				inicio = substitution_S(inicio);
				break;
			case 's':
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
    
	printf("\n");
	


	imprime(inicio);
	printf("\n");

	return 0;

}
