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
				memcpy((newString + i -1), (outputString + i + 1), (ARRAY_SIZE - i )*sizeof(char));
				memcpy(outputString, newString, ARRAY_SIZE*sizeof(char));
				

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
	
	if(outputString[1] == '(')
	{
		finalPos = searchParenthesis(1);
		memcpy(a, outputString + initPos, finalPos*sizeof(char));
		printf("%s\n", a);
		

	}

}

void substitution_S(){}


int main()
{
	
	FILE* fileout;
	fileout = fopen("output.txt", "w");
	int lvl = 0;
	int i = 0;
	int removed = 0;


	
	




	

	readFile();
	
	
	while(outputString[0] == '(')
	{
		removeParenthesis();

	}
	if(outputString[0] == 'K')
	{
		substitution_K();
	}
	else if(outputString[0] == 'S')
	{
		substitution_S();;
	}

	
	

	printf("%s\n", newString);


	return 0;




}