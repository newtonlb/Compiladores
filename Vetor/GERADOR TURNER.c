#include <stdio.h>
#include <stdlib.h>



int main( ){
    int i=0, numY = 200, opcao = 0;
    char valordeY[1000] = "s(cBI(SII))I(B(cBI(SII))I)";
    char valorKS[1000] = "S(S(S(KS)(S(KK)(SKK)))(K(S(SKK)(SKK))))(S(S(KS)(S(KK)(SKK)))(K(S(SKK)(SKK))))";
    FILE *entradagerada;

    printf("Numero de repeticoes de Y: ");
    scanf("%d", &numY);
    printf("\nOpcao 1 Turner, Opcao 2 KS:");
    scanf("%d", &opcao);
    entradagerada = fopen ("input.txt", "w");
    if (opcao == 1)
    {
        for(i=0; i<numY-2; i++)
        {
            fputs(valordeY,entradagerada);
            fputs("((",entradagerada);
        }
        fputs(valordeY,entradagerada);
        fputs("((",entradagerada);
        fputs(valordeY,entradagerada);
        fputs("(KK))K)",entradagerada);
        for(i=0; i<numY-2; i++)
        {
            fputs(")K)",entradagerada);
        }
    }
    else if (opcao == 2)
    {
        for(i=0; i<numY-2; i++)
        {
            fputs(valorKS,entradagerada);
            fputs("((",entradagerada);
        }
        fputs(valorKS,entradagerada);
        fputs("((",entradagerada);
        fputs(valorKS,entradagerada);
        fputs("(KK))K)",entradagerada);
        for(i=0; i<numY-2; i++)
        {
            fputs(")K)",entradagerada);
        }
    }
    return 0;
}
