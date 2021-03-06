#include "globalHeader.h"
#include "createCellFunctions.h"
#include "stackFunctions.h"
#include "graphFunctions.h"
#include "gcCheney.h"
#include "reductions.h"


void mg_V2()
{
    int size = strlen(string);
    
    CELL* inicio = create_graph(size);
    CELL* aux = inicio, *aux2, *aux3;
    int i;
    int imprimirGrafo = 0;
    int reductible = 1;
    CELL* vetor[] = {NULL, NULL, NULL, NULL}, *a, *b, *c, *d, *op, *cauda, *f, *g, *x, *y, *par1, *par2;
    int counter = 0;
    
    inicio = reduct(inicio);
    printf("antes do GC: \n");
    //print_graph(inicio);
    while(garbage == 1)
    {
        printf("chegou aqui\n");
    
        if(heapUsado == 0){
            
            heapUsado = 1;
            heap = heap2;
            GC_cheney(inicio, heap);
            inicio = heap;
            
            //ptrRaiz = heap;
        }
        else
        {
            heapUsado = 0;
            heap=heap1;
            GC_cheney(inicio, heap);
            
            //lastPos = 0;
            inicio = heap;
            printf("SAIU DO GARBAGE\n");
        }
        garbage = 0;
        free_pilha(pilha);
         printf("depois do GC do GC: \n");
        //print_graph(inicio);
        printf("\n");
        inicio = reduct(inicio);
    }
    print_graph(inicio);
}


int main()
{
    mg_V2();
    printf("\n\n");
    
#ifdef PRINTS
    printf("ContK = %d\n", contK);
    printf("ContS = %d\n", contS);
    printf("ContI = %d\n", contI);
    printf("ContB = %d\n", contB);
    printf("ContC = %d\n", contC);
    printf("ContSlinha = %d\n", contSlinha);
    printf("ContBlinha = %d\n", contBlinha);
    printf("ContClinha = %d\n", contClinha);
    printf("ContKlinha = %d\n", contKlinha);
    printf("ContSoma = %d\n", contSoma);
    printf("ContSub = %d\n", contSub);
    printf("ContMenor = %d\n", contMenor);
    printf("ContMaior = %d\n", contMaior);
    printf("ContMult = %d\n", contMult);
    printf("ContDiv = %d\n", contDiv);
    printf("ContIgual = %d\n", contIgual);
    printf("ContY = %d\n", contY);
    printf("ContRemoveParenteses = %d\n", contRemoveParenteses);
    printf("Iterations = %d\n", iterations);
    printf("lastPos = %d\n", lastPos);
#endif
    
    return 0;
}
