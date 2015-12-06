/*
 * GCCHENEY - GarbageCollector with Cheney Algorithm, this document provides the Cheney Algorithm
 * implemented in this project (Here is the implement of each funtion, 
 * the assign is in the Global Header File)
 */

#ifndef GCCHENEY_H_
#define GCCHENEY_H_

int heapQtdCallGc(int qtd)
{
        if ((lastPos+qtd -1) >(HEAP_SIZE-1))
        {
            return 1;
        }
        else
        {
            return 0;
        }
        
   
}

void copy_cell(CELL *dest, CELL *src)
{
    *dest = *src;
}

void GC_cheney(CELL *root, CELL *dest)
{
    CELL *cp = dest, **hp = &(dest->left), *hp_aux = dest;
    int left_right = 0;

    copy_cell(cp, root);
    root->memory = copied;
    root->left = root->right = cp;
    cp++;

    while(cp != hp_aux)
    {
        if(*hp != NULL)
        {
            if((*hp)->memory == not_copied)
            {
                *cp = **hp;                            //copia célula no novo heap
                (*hp)->memory = copied;                //marca célula como copiada
                (*hp)->left = (*hp)->right = cp;       //faz a célula antiga apontar para a nova
                *hp = cp;                              //atualiza campo hp para apontar para a célula copiada
                cp++;                                  //atualiza cp para próxima posição livre
            }
            else
            {
                *hp = (*hp)->left;                     //se já estiver copiado, atualize o ponteiro *hp
            }
        }

        if(left_right == 0)                        //hp aponta para o left da célula atual
        {
            hp = &(hp_aux->right);
        }
        else                                       //hp aponta para o right da célula atual
        {
            hp_aux++;
            hp = &(hp_aux->left);
        }

        left_right = ++left_right & 0x1;
    }

    //printf("Foram copiadas %d células\n", num);
     lastPos= (cp - dest);
}

#endif

