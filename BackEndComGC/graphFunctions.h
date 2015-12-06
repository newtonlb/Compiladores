/*
 * Graph Functions, this document provides functions to use the Graph
 * implemented in this project (Here is the implement of each funtion, 
 * the assign is in the Global Header File)
 */

#ifndef GRAPHFUNCTIONS_H_
#define GRAPHFUNCTIONS_H_

// Function to create a Graph in the project
CELL* create_graph(int size)
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
                inicio->left = create_graph(size);
            else if (inicio->right == NULL)
                inicio->right = create_graph(size);
            else
            {
                aux = inicio;
                inicio = create_CELL_parenthesis(aux, create_graph(size));
            }
        }
        else if(string[pos] == '$')
        {

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

// Function to print the Graph
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


#endif