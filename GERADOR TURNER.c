#include <stdio.h>
#include <stdlib.h>



int main( ){
    int i=0, numY = 200;
    char valordeY[1000] = "s(cBI(SII))I(B(cBI(SII))I)";
    FILE *entradagerada;

    printf("Numero de repeticoes de Y: ");
    scanf("%d", &numY);
    entradagerada = fopen ("input.txt", "w");
    for(i=0; i<numY-2; i++){
        fputs(valordeY,entradagerada);
        fputs("((",entradagerada);
    }
    fputs(valordeY,entradagerada);
    fputs("((",entradagerada);
    fputs(valordeY,entradagerada);
    fputs("(KK))K)",entradagerada);
    for(i=0; i<numY-2; i++){
        fputs(")K)",entradagerada);
    }
    return 0;
}
