
#include "lista.h"

// Create a New Node
NODE* new_node()
{
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode->down = NULL;
    newNode->next = NULL;
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


NODE* create_list(int i, int j, char* string)
{
    NODE* inicio = NULL;
    int k;
    //printf("Entrou\n");
    for (k = i; k <= j && string[k] != ')' ; k++)
    {
        //printf("%c", string[k]);
        if (string[k] != '(') // Qualquer caracter e ')'
        {
            if (inicio == NULL)
            {
                inicio = new_node();
                inicio->caract = string[k];
            }
            else
            {
                NODE* aux = inicio;
                while(aux->next != NULL)
                {
                    aux = aux->next;
                }
                aux->next = new_node();
                aux->next->caract = string[k];
            }
        }
        else if (string[k] == '(') // Quando for '('
        {
            int novoj;
            novoj = searchParenthesis(k, string);
            if(inicio == NULL)
            {
                inicio = new_node();
                inicio->caract = string[k];
                inicio->down = create_list(k + 1, novoj - 1, string);
                k = novoj;
            }
            else
            {
               // printf("\nSKT");
                NODE* aux = new_node();
                aux = inicio;
                int contadorAB = 1;
                while(aux->next != NULL)
                {

                    aux = aux->next;
                    printf("%d\n", contadorAB);
                    contadorAB++;

                }
               // printf("TABOM");
                aux->next = new_node();
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
   // free(inicio);


    return retorno;
}


void freeRecursao(NODE* inicio)
{
    if (inicio != NULL)
    {
        while(inicio->next != NULL)
        {
            if(inicio->down != NULL)
                freeRecursao(inicio->down);
            else
            {
                NODE* aux = inicio->next;
                free(inicio);
                inicio = aux;
            }
        }
    }

}

/// K a b => a
NODE* substitution_K(NODE* inicio)
{

    NODE* a = inicio->next;
    NODE* b = a->next;
    NODE* cauda = b->next;
    a->next = cauda;
    b->next = NULL;
   // freeRecursao(b);
  //  free(inicio);
    return a;
}

NODE* clone(NODE* inicio)
{
    NODE* novo = new_node();
    NODE* novoinicio = novo;

    NODE* aux = NULL;
    aux = new_node();
    aux = inicio;
    int ehNull = 0;


    while(aux != NULL)
    {
        novo->caract = aux->caract;
        novo->next = new_node();
        //printf("%c\n", aux->caract);
        if((aux->caract == '(') && (aux->down != NULL))
        {
            novo->down = clone(aux->down);
        }
        aux = aux->next;
        novo = novo->next;
    }
    //free(aux);
    //free(novo);
    //free(inicio);
    return novoinicio;
}



/// S a b c => (ac)(bc) == ac(bc)
NODE* substitution_S(NODE* inicio)
{
    //printf("chegou no S\n");
    NODE* a = inicio->next;
    NODE* b = a->next;
    NODE* c = b->next;
    NODE* cauda = c->next;
    NODE* novoC = clone(c);
    NODE* aux = new_node();
    //imprime(c);
    //imprime(novoC);

    a->next = c;
    c->next = aux;
    aux->caract = '(';
    aux->down = b;
    b->next = novoC;
    novoC->next = NULL;
    aux->next = cauda;
   // free(inicio);
    //imprime(a);
    return a;

}

/// I a => a
NODE* substitution_I(NODE* inicio)
{
    NODE* a = inicio->next;
  //  free(inicio);
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
   // free(inicio);
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
   // free(inicio);
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
  //  free(inicio);
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
    //free(inicio);
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
    //free(inicio);
    return a;
}


int main()
{
   // freopen("saidaLista.txt", "w", stdout);
    int tamanho = strlen(string);
    int i = 0, redutible = 0;
    printf("\nWTFK\n");
    printf("Entrada1:\n%s\n", string);
    NODE* inicio = create_list(0,tamanho,string);
    printf("\nWTFK2\n");
    printf("Entrada2:\n");
    //imprime(inicio);
    printf("\n\n");
  //  printf("Clonado:\n");
   // NODE* clonado = clone(inicio);
   // imprime(clonado);
    printf("\n");

    while(redutible == 1)
    {
#ifdef ITERATIONS
        iterations++;
#endif
        if(inicio !=NULL)
        {
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
                inicio = substitution_I(inicio);
                break;
            case 'K':
#ifdef COUNTERK
                contK++;
#endif
                contK++;
                if (inicio->next == NULL)
                {

                    redutible = 0;
                    break;
                }
                else if(inicio->next->next == NULL)
                {
                    redutible = 0;
                    break;
                }
                inicio = substitution_K(inicio);
                //imprime(inicio);
                //printf("\n\n");
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
                //imprime(inicio);
                //printf("\n\n");
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

            /*case '\0':
                inicio = inicio->next;
                if(inicio == NULL)
                    redutible = 0;
                break;*/
            default:
                redutible = 0;
                break;
        }
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
    printf("chegou aqui\n");
   // imprime(inicio);
    printf("\n");

    return 0;
}