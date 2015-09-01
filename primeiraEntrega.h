#ifndef PRIMEIRAENTREGA_H_
#define PRIMEIRAENTREGA_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARRAY_SIZE 100000000

#define MACROS

#ifdef MACROS
    #define COUNTERK
    #define COUNTERS
    #define ITERATIONS
    #define COUNTER
    int countK = 0;
    int countS = 0;
    int counter = 0;
	int iterations = 0;

#endif // MACROS

char newString[ARRAY_SIZE];
char inputString[ARRAY_SIZE];
char outputString[ARRAY_SIZE];

char blank[ARRAY_SIZE];


int posAinit;
int posAfinal;
int posBinit;
int posBfinal;
int posCinit;
int posCfinal;

void readFile()
{
	FILE* filein;
	filein = fopen("input.txt", "r");
	char* inputString;
	inputString = (char*) malloc(sizeof(char) * ARRAY_SIZE);

	fscanf(filein,"%s", inputString);
	memcpy(outputString, inputString, ARRAY_SIZE*sizeof(char));

    fclose(filein);
}


void removeParenthesis()
{
		int removed = 0;
		int lvl = 1;
		int i = 0;

		while (removed == 0)
		{
			i++;
			if(outputString[i] == '(')
			{
				lvl++;
			}
			else if(outputString[i] == ')')
			{
				lvl--;
			}
			if(lvl == 0)
			{

				//printf("%d\n", i);
				memcpy(newString, outputString + 1,(i-1)*sizeof(char)) ;
				//printf("result: %s\n",newString);
				memcpy((newString + i -1), (outputString + i + 1), (ARRAY_SIZE - i )*sizeof(char));
				memcpy(outputString, newString, ARRAY_SIZE*sizeof(char));
				//printf("removed parenthesis: %s\n",outputString);
				removed = 1;
			}
		}
}

int searchParenthesis(int initPos)
{
	int i = 0;
	int lvl = 0;
	int removed = 0;
	while(outputString[initPos] == '(')
	{
		lvl = 1;
		i = initPos;

		while (removed == 0)
		{
			i++;
			if(outputString[i] == '(')
			{
				lvl++;
			}
			else if(outputString[i] == ')')
			{
				lvl--;
			}
			if(lvl == 0)
			{
				removed = 1;
			}

		}
		break;

	}
	return i;
}

void substitution_K()
{
	int i = 0;
	int initPos = 1;
	int finalPos;
	posAinit = 0;
	posAfinal = 0;
	posBinit = 0;
	posBfinal = 0;
	posCinit = 0;
	posCfinal = 0;
	
	memcpy(newString, blank, ARRAY_SIZE*sizeof(char));

	if(outputString[1] == '(')
	{
		posAinit = 1;
		posAfinal = searchParenthesis(1);
		
		//printf("a: %s\n",a );

	}
	else
	{
		posAinit = 1;
		posAfinal = posAinit;
		
		//printf("a: %s\n", a);
	}
	posBinit = posAfinal + 1;
	if(outputString[posBinit] == '(')
	{


		posBfinal = searchParenthesis(posBinit);
		
		//printf("b: %s\n",b );
		/*printf(" parthesis pos: %d\n",finalPos );
		memcpy(b, (outputString + (initPos)), (finalPos - initPos) *sizeof(char));
		printf("b: %s\n",b );*/
	}
	else
	{
		posBfinal = posBinit;
		

	}
	memcpy(newString, outputString + posAinit, posAfinal*sizeof(char));
	//printf("%s\n",newString);
	//printf("%d\n", posBfinal);
	memcpy(newString + strlen(newString) , outputString + posBfinal +1, (ARRAY_SIZE - posBfinal)*sizeof(char));
	//printf("%s\n", newString );

	memcpy(outputString, newString, ARRAY_SIZE*sizeof(char));
}


void substitution_S(){

	posAinit = 0;
	posAfinal = 0;
	posBinit = 0;
	posBfinal = 0;
	posCinit = 0;
	posCfinal = 0;

	
	memcpy(newString, blank, ARRAY_SIZE*sizeof(char));
	if(outputString[1] == '(')
	{
		posAinit = 1;
		posAfinal = searchParenthesis(1);
		//printf("a: %s\n",a );
	}
	else
	{

		posAfinal = 1;
		posAinit = 1;
		
		//printf("a: %s\n", a);

	}
	posBinit = posAfinal + 1;
	if(outputString[posBinit] == '(')
	{


		posBfinal = searchParenthesis(posBinit);
		
		//printf("b: %s\n",b );
	}
	else
	{
		posBfinal = posBinit;
	
		//printf("b: %s\n",b );
	}
	posCinit = posBfinal + 1;
	if(outputString[posCinit] == '(')
	{
		posCfinal = searchParenthesis(posCinit);
		
		//printf("c: %s\n",c );


	}
	else
	{
		posCfinal = posCinit +1;
		
		
		posCfinal = posCinit;
	}

	memcpy(newString, "(", sizeof(char)); //(
	//printf("%s\n", newString);

	memcpy(newString +strlen(newString), outputString + posAinit, (posAfinal - posAinit +1)*sizeof(char));  //(a
	//printf("%s\n",newString );

	memcpy(newString + strlen(newString), outputString + posCinit, (posCfinal - posCinit +1)*sizeof(char)); //(ac
	//printf("%s\n",newString);

	memcpy(newString + strlen(newString), ")", sizeof(char)); //(ac)
	//printf("%s\n",newString );

	memcpy(newString + strlen(newString), "(", sizeof(char));// (ac)(
	//printf("%s\n",newString );

	memcpy(newString + strlen(newString), outputString +posBinit, (posBfinal-posBinit +1)*sizeof(char));
	//printf("%s\n",newString );

	memcpy(newString + strlen(newString),outputString + posCinit, (posCfinal-posCinit +1)*sizeof(char));
	//printf("%s\n",newString );

	memcpy(newString + strlen(newString), ")", (ARRAY_SIZE - (strlen(newString) + 1))*sizeof(char));
	//printf("%s\n",newString );

	memcpy(newString + strlen(newString), outputString + posCfinal +1, (ARRAY_SIZE-posCfinal +1)*sizeof(char));
	//printf("%s\n",newString );
	memcpy(outputString, newString, ARRAY_SIZE*sizeof(char));
}

#endif
