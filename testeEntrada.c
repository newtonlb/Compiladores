#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define ARRAY_SIZE 900000
char newString[ARRAY_SIZE];
char inputString[ARRAY_SIZE];
char outputString[ARRAY_SIZE];
char a[ARRAY_SIZE];
char b[ARRAY_SIZE];
char c[ARRAY_SIZE];
char blank[ARRAY_SIZE];
char d[ARRAY_SIZE];

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
				
				printf("%d\n", i);
				memcpy(newString, outputString + 1,(i-1)*sizeof(char)) ;
				printf("result: %s\n",newString);
				memcpy((newString + i -1), (outputString + i + 1), (ARRAY_SIZE - i )*sizeof(char));
				memcpy(outputString, newString, ARRAY_SIZE*sizeof(char));
				printf("removed parenthesis: %s\n",outputString);

				

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
	memcpy(a, blank, ARRAY_SIZE*sizeof(char));
	memcpy(b, blank, ARRAY_SIZE*sizeof(char));
	memcpy(c, blank, ARRAY_SIZE*sizeof(char));
	memcpy(newString, blank, ARRAY_SIZE*sizeof(char));

	
	if(outputString[1] == '(')
	{
		posAinit = 1;
		posAfinal = searchParenthesis(1);
		memcpy(a, outputString + posAinit, (posAfinal - posAinit +1)*sizeof(char));
		printf("a: %s\n",a );
		
	}
	else
	{
		posAinit = 1;
		posAfinal = posAinit;
		memcpy(a, outputString + 1, sizeof(char));
		printf("a: %s\n", a);
	}
	posBinit = posAfinal + 1;
	if(outputString[posBinit] == '(')
	{
		
		
		posBfinal = searchParenthesis(posBinit);
		memcpy(b, outputString + posBinit, (posBfinal - posBinit +1)*sizeof(char));
		printf("b: %s\n",b );
		/*printf(" parthesis pos: %d\n",finalPos );
		memcpy(b, (outputString + (initPos)), (finalPos - initPos) *sizeof(char));
		printf("b: %s\n",b );*/
	}
	else
	{
		posBfinal = posBinit;
		memcpy(b, outputString +posBinit, sizeof(char));


	
	}
	memcpy(newString, outputString + posAinit, posAfinal*sizeof(char));
	printf("%s\n",newString);
	printf("%d\n", posBfinal);
	memcpy(newString + strlen(newString) , outputString + posBfinal +1, (ARRAY_SIZE - posBfinal)*sizeof(char));
	printf("%s\n", newString );

	
	memcpy(outputString, newString, ARRAY_SIZE*sizeof(char));

}
/// VOU FAZER QUANDO VOLTAR , FUI ALMOCAR, DEIXA ESSE PRA MIM! FLW VLW



void substitution_S(){

	posAinit = 0;
	posAfinal = 0;
	posBinit = 0;
	posBfinal = 0;
	posCinit = 0;
	posCfinal = 0;

	memcpy(a, blank, ARRAY_SIZE*sizeof(char));
	memcpy(b, blank, ARRAY_SIZE*sizeof(char));
	memcpy(c, blank, ARRAY_SIZE*sizeof(char));
	memcpy(newString, blank, ARRAY_SIZE*sizeof(char));
	if(outputString[1] == '(')
	{
		posAinit = 1;
		posAfinal = searchParenthesis(1);
		memcpy(a, outputString + posAinit, (posAfinal - posAinit +1)*sizeof(char));
		printf("a: %s\n",a );
	}
	else
	{
		
		posAfinal = 1;
		posAinit = 1;
		memcpy(a, outputString + 1, sizeof(char));
		printf("a: %s\n", a);
		
	}
	posBinit = posAfinal + 1;
	if(outputString[posBinit] == '(')
	{
		
		
		posBfinal = searchParenthesis(posBinit);
		memcpy(b, outputString + posBinit, (posBfinal - posBinit +1)*sizeof(char));
		printf("b: %s\n",b );
	}
	else
	{
		posBfinal = posBinit + 1;
		memcpy(b, outputString +posBinit, sizeof(char));
		printf("b: %s\n",b );
	}
	posCinit = posBfinal + 1;
	if(outputString[posCinit] == '(')
	{
		posCfinal = searchParenthesis(posCinit);
		memcpy(c, outputString + posCinit, (posCfinal - posCinit +1)*sizeof(char));
		printf("c: %s\n",c );


	}
	else
	{
		memcpy(c, outputString + posCinit, sizeof(char));
		printf("c: %s\n",c );
		posCfinal = posCinit;
	}


	memcpy(newString, "(", sizeof(char)); //(
	//printf("%s\n", newString);

	memcpy(newString +strlen(newString), outputString + posAinit, (posAfinal - posAinit +1)*sizeof(char));  //(a
	printf("%s\n",newString );

	memcpy(newString + strlen(newString), outputString + posCinit, (posCfinal - posCinit +1)*sizeof(char)); //(ac
	printf("%s\n",newString);

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



/*void substitution_S(){
	
	int i = 0;
	int initPos = 1;
	int finalPos;
	
	if(outputString[1] == '(')
	{
		finalPos = searchParenthesis(1);
		memcpy(a, outputString + initPos, ((finalPos-initPos) +1)*sizeof(char));
		printf(" a: %s\n", a);
		initPos = finalPos + 1;
	}
	else
	{
		memcpy(a, outputString + initPos, sizeof(char));
		initPos+=1;
	}
	
	if(outputString[initPos] == '(')
	{
		finalPos = searchParenthesis(initPos);
		finalPos++;
		printf(" parthesis pos: %d\n",finalPos );
		memcpy(b, (outputString + (initPos)), (finalPos - initPos) *sizeof(char));
		printf("b: %s\n",b );
		initPos = finalPos;
	}

	else
	{
		memcpy(b, outputString + initPos, sizeof(char));
	}
	printf("%c", outputString[initPos]);
	if(outputString[initPos] == '(')
	{
		finalPos = searchParenthesis(initPos);
		finalPos++;
		printf(" parthesis pos: %d\n",finalPos );
		memcpy(c, (outputString + (initPos)), (finalPos - initPos) *sizeof(char));
		printf("c: %s\n",c);
		
	}


	memcpy(d, outputString + finalPos, ARRAY_SIZE*sizeof(char));
	printf("d: %s\n",d );
	memcpy(newString, blank, ARRAY_SIZE*sizeof(char));


	memcpy(newString, "(", sizeof(char));
	printf("%s\n",newString );
	
	memcpy(newString+1, a, strlen(a)*sizeof(char));
	printf("%s\n",newString );
	
	memcpy(newString + strlen(newString), c, (ARRAY_SIZE - (strlen(newString) + strlen(c)))*sizeof(char));
	printf("%s\n",newString );

	memcpy(newString + strlen(newString), ")", sizeof(char));
	printf("%s\n",newString );
	
	memcpy(newString + strlen(newString), "(", sizeof(char));
	printf("%s\n",newString );

	memcpy(newString + strlen(newString), b, (ARRAY_SIZE - (strlen(newString) + strlen(b)))*sizeof(char));
	printf("%s\n",newString );

	memcpy(newString + strlen(newString), c, (ARRAY_SIZE - (strlen(newString) + strlen(c)))*sizeof(char));
	printf("%s\n",newString );

	memcpy(newString + strlen(newString), ")", (ARRAY_SIZE - (strlen(newString) + 1))*sizeof(char));
	printf("%s\n",newString );

	memcpy(newString + strlen(newString), d, (ARRAY_SIZE - (strlen(newString) + strlen(d)))*sizeof(char));
	printf("%s\n",newString );


	printf("reduction: %s\n",newString );

}

*/
int main()
{
	
	FILE* fileout;
	fileout = fopen("output.txt", "w");
	int lvl = 0;
	int i = 0;
	int removed = 0;
	int reductible = 1;
	int countK = 0;
	int countS = 0;
	int count = 0;
	int iterations = 0;


	
	




	

	readFile();
	
	while(reductible == 1)
	{
		while(outputString[0] == '(')
		{
			removeParenthesis();

		}
		if(outputString[0] == 'K' && strlen(outputString) > 2)
		{
			substitution_K();
			countK++;
		}
		else if(outputString[0] == 'S' && strlen(outputString) > 3)
		{
			substitution_S();
			countS++;
		}
		else
		{
			printf("chegou aqui\n");
			reductible = 0;
		}
		printf("interation %d : %s\n",iterations, outputString);
		printf("%lu\n",strlen(outputString));
		iterations++;
	}
	count = countK + countS;

	
	

	


	return 0;




}