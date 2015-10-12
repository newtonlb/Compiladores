#include "primeiraEntrega.h"

void readFile()
{
	FILE* filein;
	filein = fopen("input.txt", "r");
	char* inputString;
	inputString = (char*) malloc(sizeof(char) * ARRAY_SIZE);

	fscanf(filein,"%s", inputString);
	memcpy(strings[(countVet%2)], inputString, ARRAY_SIZE*sizeof(char));

    fclose(filein);
}


int removeParenthesis(int tamanho)
{
		int removed = 0;
		int lvl = 1;
		int i = 0;
		while (removed == 0)
		{
			i++;

			if(strings[(countVet%2)][i] == '(')
			{
				lvl++;
			}
			else if(strings[(countVet%2)][i] == ')')
			{
				lvl--;
                if(lvl == 0)
                {
                   
                    memcpy(strings[(countVet+1)%2], strings[(countVet%2)] + 1,(i-1)*sizeof(char)) ;
                    memcpy((strings[(countVet+1)%2] + i -1), (strings[(countVet%2)] + i + 1), (tamanho - i )*sizeof(char));
                    removed = 1;
                }
			}

		}
		return tamanho - 2;
}

int searchParenthesis(int initPos)
{
	int i = 0;
	int lvl = 0;
	int removed = 0;

	if(strings[(countVet%2)][initPos] == '(')
	{
		lvl = 1;
		i = initPos;

		while (removed == 0)
		{
			i++;
			if(strings[(countVet%2)][i] == '(')
			{
				lvl++;
			}
			else if(strings[(countVet%2)][i] == ')')
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

int substitution_K(int tamanho)
{
	int i = 0;
	int initPos = 1;
	int posAinit = 0;
	int posAfinal = 0;
	int posBinit = 0;
	int posBfinal = 0;
	int posCinit = 0;
	int posCfinal = 0;


	if(strings[(countVet%2)][initPos] == '(')
	{
		posAinit = initPos;
		posAfinal = searchParenthesis(initPos);

	}
	else
	{
		posAinit = initPos;
		posAfinal = posAinit;
	}
	posBinit = posAfinal + 1;
	if (posBinit > tamanho - 1)
	{
		return 0;
	}
	else if(strings[(countVet%2)][posBinit] == '(')
	{
		posBfinal = searchParenthesis(posBinit);

		
	}
	else
	{
		posBfinal = posBinit;
	}
	memcpy(strings[(countVet+1)%2], strings[(countVet%2)] + posAinit, posAfinal*sizeof(char));
	int tamanhoOutputString = tamanho;
	memcpy(strings[(countVet+1)%2] + (posAfinal - posAinit + 1) , strings[(countVet%2)] + posBfinal +1, (tamanhoOutputString - posBfinal)*sizeof(char));
	return tamanhoOutputString - (posBfinal - posBinit + 1) - 1;

}


int substitution_S(int tamanho)
{

	int posAinit = 0;
	int posAfinal = 0;
	int posBinit = 0;
	int posBfinal = 0;
	int posCinit = 0;
	int posCfinal = 0;
	int stringLastPos = 0;

	if(strings[(countVet%2)][1] == '(')
	{
		posAinit = 1;
		posAfinal = searchParenthesis(1);

	}
	else
	{
		posAfinal = 1;
		posAinit = 1;


	}
	posBinit = posAfinal + 1;
	if (posBinit > tamanho - 1)
	{
		return 0;
	}
	else if(strings[(countVet%2)][posBinit] == '(')
	{


		posBfinal = searchParenthesis(posBinit);
	}
	else
	{
		posBfinal = posBinit;
	}
	posCinit = posBfinal + 1;
	if (posCinit > tamanho - 1)
	{
		return 0;
	}
	else if(strings[(countVet%2)][posCinit] == '(')
	{
		posCfinal = searchParenthesis(posCinit);
	}
	else
	{
		posCfinal = posCinit;
	}

	strings[(countVet+1)%2][0] = '(';

	stringLastPos++;
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posAinit, (posAfinal - posAinit +1)*sizeof(char));  //(a

	stringLastPos += posAfinal - posAinit +1;
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posCinit, (posCfinal - posCinit +1)*sizeof(char)); //(ac

	stringLastPos += posCfinal - posCinit +1;

	strings[(countVet+1)%2][stringLastPos] = ')';

	stringLastPos++;

	strings[(countVet+1)%2][stringLastPos] = '(';

	stringLastPos++;
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] +posBinit, (posBfinal-posBinit +1)*sizeof(char));
	stringLastPos += posBfinal-posBinit +1;
	memcpy(strings[(countVet+1)%2] + stringLastPos ,strings[(countVet%2)] + posCinit, (posCfinal-posCinit +1)*sizeof(char));
	stringLastPos+= posCfinal-posCinit +1;

	strings[(countVet+1)%2][stringLastPos] = ')';

	stringLastPos++;
	int tamanhoOutputString = tamanho;
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posCfinal +1, (tamanhoOutputString-posCfinal +1)*sizeof(char));
	return tamanhoOutputString - 1 + 4 + (posCfinal - posCinit + 1);
}

int substitution_I(int tamanho)
{
    int initPos = 1;
    int posAinit = 0;
    int posAfinal = 0;
    if(strings[(countVet%2)][initPos] == '(')
    {
        posAinit = initPos;
        posAfinal = searchParenthesis(initPos);
    }
    else
    {
        posAinit = initPos;
        posAfinal = posAinit;
    }

    memcpy(strings[(countVet+1)%2], strings[(countVet%2)] + posAinit, (posAfinal-posAinit+1)*sizeof(char));

    int tamanhoOutputString = tamanho;

	memcpy(strings[(countVet+1)%2] + posAfinal, strings[(countVet%2)] + posAfinal + 1, (tamanhoOutputString-posAfinal +1)*sizeof(char));

	return tamanhoOutputString - 1;

}

// B f g x => f(gx)
int substitution_B(int tamanho)
{
	int initPos = 1;
	int posFinit = 0;
	int posFfinal = 0;
	int posGinit = 0;
	int posGfinal = 0;
	int posXinit = 0;
	int posXfinal = 0;
	int stringLastPos = 0;

	if (strings[(countVet%2)][initPos] == '(')
	{
		posFinit = initPos;
		posFfinal = searchParenthesis(posFinit);
	}
	else
	{
		posFinit = initPos;
		posFfinal = posFinit;
	}
	posGinit = posFfinal + 1;
	if (posGinit > tamanho - 1)
	{
		return 0;
	}
	else if (strings[(countVet%2)][posGinit] == '(')
	{
		posGfinal = searchParenthesis(posGinit);
	}
	else
	{
		posGfinal = posGinit;
	}

	posXinit = posGfinal + 1;
	if (posXinit > tamanho - 1)
	{
		return 0;
	}
	else if (strings[(countVet%2)][posXinit] == '(')
	{
		posXfinal = searchParenthesis(posXinit);
	}
	else
	{
		posXfinal = posXinit;
	}

	int tamanhoOutputString = tamanho;


	memcpy(strings[(countVet+1)%2], strings[(countVet%2)] + posFinit, (posFfinal - posFinit + 1)*sizeof(char));
	stringLastPos+= (posFfinal - posFinit + 1);
	strings[(countVet+1)%2][stringLastPos] = '(';

	stringLastPos++;
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posGinit, (posGfinal - posGinit +1)*sizeof(char));
	stringLastPos += (posGfinal - posGinit) + 1;
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posXinit, (posXfinal - posXinit + 1)*sizeof(char));
	stringLastPos += (posXfinal - posXinit) + 1;

	strings[(countVet+1)%2][stringLastPos] = ')';
	stringLastPos++;
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posXfinal + 1, (tamanhoOutputString - posXfinal + 1)*sizeof(char));

	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posXfinal + 1, (tamanhoOutputString-posXfinal+1)*sizeof(char));

	return tamanhoOutputString - 1 + 2;

}


int substitution_C(int tamanho)
{
	int initPos = 1;
	int posFinit = 0;
	int posFfinal = 0;
	int posYinit = 0;
	int posYfinal = 0;
	int posXinit = 0;
	int posXfinal = 0;

	if (strings[(countVet%2)][initPos] == '(')
	{
		posFinit = initPos;
		posFfinal = searchParenthesis(posFinit);
	}
	else
	{
		posFinit = initPos;
		posFfinal = posFinit;
	}

	posXinit = posFfinal + 1;
	if (posXinit > tamanho - 1)
	{
		return 0;
	}
	else if (strings[(countVet%2)][posXinit] == '(')
	{
		posXfinal = searchParenthesis(posXinit);
	}
	else
	{
		posXfinal = posXinit;
	}

	posYinit = posXfinal + 1;
	if (posYinit > tamanho - 1)
	{
		return 0;
	}
	else if (strings[(countVet%2)][posYinit] == '(')
	{
		posYfinal = searchParenthesis(posYinit);	

	}
	else
	{
		posYfinal = posYinit;
	}

	int stringLastPos = 0;
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posFinit, (posFfinal - posFinit + 1)*sizeof(char));
	stringLastPos += (posFfinal - posFinit + 1);
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posYinit, (posYfinal - posYinit + 1)*sizeof(char));
	stringLastPos += (posYfinal - posYinit + 1);
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posXinit, (posXfinal - posXinit + 1)*sizeof(char));
	stringLastPos += (posXfinal - posXinit + 1);

	int tamanhoOutputString = tamanho;

	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posYfinal + 1, (tamanhoOutputString-posYfinal+1)*sizeof(char));

	return tamanhoOutputString - 1;

}

// S'abcd => a(bd)(cd)
int substitution_s(int tamanho)
{

	int initPos = 1;
	int posAinit = 0;
	int posAfinal = 0;
	int posBinit = 0;
	int posBfinal = 0;
	int posCinit = 0;
	int posCfinal = 0;
	int posDinit = 0;
	int posDfinal = 0;

	if (strings[(countVet%2)][initPos] == '(')
	{
		posAinit = initPos;
		posAfinal = searchParenthesis(posAinit);
	}
	else
	{
		posAinit = initPos;
		posAfinal = posAinit;
	}

	posBinit = posAfinal + 1;
	if (posBinit > tamanho - 1)
	{
		return 0;
	}
	else if (strings[(countVet%2)][posBinit] == '(')
	{
		posBfinal = searchParenthesis(posBinit);
	}
	else
	{
		posBfinal = posBinit;
	}

	posCinit = posBfinal + 1;
	if (posCinit > tamanho - 1)
	{
		return 0;
	}
	else if (strings[(countVet%2)][posCinit] == '(')
	{
		posCfinal = searchParenthesis(posCinit);	

	}
	else
	{
		posCfinal = posCinit;
	}

	posDinit = posCfinal + 1;
	if (posDinit > tamanho - 1)
	{
		return 0;
	}
	else if (strings[(countVet%2)][posDinit] == '(')
	{
		posDfinal = searchParenthesis(posDinit);	

	}
	else
	{
		posDfinal = posDinit;
	}

	
	int stringLastPos = 0;
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posAinit, (posAfinal - posAinit + 1)*sizeof(char));
	stringLastPos += (posAfinal - posAinit + 1);

	strings[(countVet+1)%2][stringLastPos] = '(';

	stringLastPos++;

	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posBinit, (posBfinal - posBinit + 1)*sizeof(char));
	stringLastPos += (posBfinal - posBinit + 1);

	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posDinit, (posDfinal - posDinit + 1)*sizeof(char));
	stringLastPos += (posDfinal - posDinit + 1);


	strings[(countVet+1)%2][stringLastPos] = ')';

	stringLastPos++;

	strings[(countVet+1)%2][stringLastPos] = '(';

	stringLastPos++;

	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posCinit, (posCfinal - posCinit + 1)*sizeof(char));
	stringLastPos += (posCfinal - posCinit + 1);

	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posDinit, (posDfinal - posDinit + 1)*sizeof(char));
	stringLastPos += (posDfinal - posDinit + 1);

	strings[(countVet+1)%2][stringLastPos] = ')';

	stringLastPos++;

	int tamanhoOutputString = tamanho;

	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posDfinal + 1, (tamanhoOutputString-posDfinal +1)*sizeof(char));

	return tamanhoOutputString - 1 + 4 + (posDfinal - posDinit + 1);


}
int substitution_b(int tamanho)
{

	int posAinit = 0;
	int posAfinal = 0;
	int posBinit = 0;
	int posBfinal = 0;
	int posCinit = 0;
	int posCfinal = 0;
	int posDinit = 0;
	int posDfinal = 0;
	int stringLastPos = 0;

	if(strings[(countVet%2)][1] == '(')
	{
		posAinit = 1;
		posAfinal = searchParenthesis(1);

	}
	else
	{
		posAfinal = 1;
		posAinit = 1;


	}
	posBinit = posAfinal + 1;
	if (posBinit > tamanho - 1)
	{
		return 0;
	}
	else if(strings[(countVet%2)][posBinit] == '(')
	{


		posBfinal = searchParenthesis(posBinit);
	}
	else
	{
		posBfinal = posBinit;
	}
	posCinit = posBfinal + 1;
	if (posCinit > tamanho - 1)
	{
		return 0;
	}
	else if(strings[(countVet%2)][posCinit] == '(')
	{
		posCfinal = searchParenthesis(posCinit);
	}
	else
	{
		posCfinal = posCinit;
	}
	posDinit = posCfinal + 1;
	if (posDinit > tamanho - 1)
	{
		return 0;
	}
	else if(strings[(countVet%2)][posDinit] == '(')
	{
		posDfinal = searchParenthesis(posDinit);
	}
	else
	{
		posDfinal = posDinit;
	}


	 //(
	
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posAinit, (posAfinal - posAinit +1)*sizeof(char));  //a
	stringLastPos += posAfinal - posAinit +1;
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posBinit, (posBfinal - posBinit +1)*sizeof(char)); //b
	stringLastPos += posBfinal - posBinit +1;

	strings[(countVet+1)%2][stringLastPos] = '(';

	stringLastPos++;
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] +posCinit, (posCfinal-posCinit +1)*sizeof(char));//ab(c
	stringLastPos += posCfinal-posCinit +1;
	memcpy(strings[(countVet+1)%2] + stringLastPos ,strings[(countVet%2)] + posDinit, (posDfinal-posDinit +1)*sizeof(char));//ab(cd
	stringLastPos+= posCfinal-posCinit +1;

	strings[(countVet+1)%2][stringLastPos] = ')';

	stringLastPos++;
	int tamanhoOutputString = tamanho;
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posDfinal +1, (tamanhoOutputString-posDfinal +1)*sizeof(char));

	return tamanhoOutputString - 1 + 2;
}

int substitution_c(int tamanho)
{
	int initPos = 1;
	int posAinit = 0;
	int posAfinal = 0;
	int posBinit = 0;
	int posBfinal = 0;
	int posCinit = 0;
	int posCfinal = 0;
	int posDinit = 0;
	int posDfinal = 0;
	int stringLastPos = 0;

	if(strings[(countVet%2)][initPos] == '(')
	{
		posAinit = initPos;
		posAfinal = searchParenthesis(posAinit);

	}
	else
	{
		posAinit = initPos;
		posAfinal = posAinit;
	}
	posBinit = posAfinal + 1;
	if (posBinit > tamanho - 1)
	{
		return 0;
	}
	else if(strings[(countVet%2)][posBinit] == '(')
	{
		posBfinal = searchParenthesis(posBinit);
	}
	else
	{
		posBfinal = posBinit;
	}
	posCinit = posBfinal + 1;
	if (posCinit > tamanho - 1)
	{
		return 0;
	}
	else if(strings[(countVet%2)][posCinit] == '(')
	{
		posCfinal = searchParenthesis(posCinit);
	}
	else
	{
		posCfinal = posCinit;
	}
	posDinit = posCfinal + 1;
	if (posDinit > tamanho - 1)
	{
		return 0;
	}
	else if (strings[(countVet%2)][posDinit] == '(')
	{
		posDfinal = searchParenthesis(posDinit);
	}
	else
	{
		posDfinal = posDinit;
	}
	
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posAinit, (posAfinal - posAinit + 1)*sizeof(char));
	
	stringLastPos += (posAfinal - posAinit + 1);

	strings[(countVet+1)%2][stringLastPos] = '(';
	
	stringLastPos++;
	
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posBinit, (posBfinal - posBinit + 1)*sizeof(char));
	
	stringLastPos += (posBfinal - posBinit + 1);
	
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posDinit, (posDfinal - posDinit + 1)*sizeof(char));
	
	stringLastPos += (posDfinal - posDinit + 1);

	strings[(countVet+1)%2][stringLastPos] = ')';
		
	stringLastPos++;
	
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posCinit, (posCfinal - posCinit + 1)*sizeof(char));
	
	stringLastPos += (posCfinal - posCinit + 1);	
	
	int tamanhoOutputString = tamanho;
	
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posDfinal + 1, (tamanhoOutputString - posDfinal + 1)*sizeof(char));

	return tamanhoOutputString - 1 + 2;


}


int main()
{
	freopen("saida.txt", "w", stdout);

	int lvl = 0;
	int i = 0;
	int removed = 0;
	int reductible = 1;
    int tamanhoOutputString = 0;
    readFile();

	tamanhoOutputString = strlen(strings[(countVet%2)]);

	while(reductible == 1)
	{
		while(strings[countVet%2][0] == '(')
		{
			tamanhoOutputString = removeParenthesis(tamanhoOutputString);
			countVet++;

		}


		switch(strings[countVet%2][0])
		{

			case 'K':
			{
				tamanhoOutputString = substitution_K(tamanhoOutputString);
				printf("%s\n", strings[(countVet%2)]);
				printf("\n\n");
				if (tamanhoOutputString == 0)
				{
					reductible = 0;
					countVet--;
				}
				countVet++;
				#ifdef COUNTERK
	                countK++;
				#endif // COUNTERK
	            break;
			}
			case 'S':
			{
				tamanhoOutputString = substitution_S(tamanhoOutputString);
				printf("%s\n", strings[(countVet%2)]);
				printf("\n\n");
				if (tamanhoOutputString == 0)
				{
					reductible = 0;
					countVet--;
				}
				countVet++;
				#ifdef COUNTERS
	                countS++;
	            #endif // COUNTERS
	            break;
			}
			case 'I':
			{	
				tamanhoOutputString = substitution_I(tamanhoOutputString);
				if (tamanhoOutputString == 0)
				{
					reductible = 0;
					countVet--;
				}
				countVet++;
				#ifdef COUNTERI	
					countI++;
				#endif
				break;
			}
			case 'B':
			{
				tamanhoOutputString = substitution_B(tamanhoOutputString);
				if (tamanhoOutputString == 0)
				{
					reductible = 0;
					countVet--;
				}
				countVet++;
				#ifdef COUNTERB	
					countB++;
				#endif
				break;
			}
			case 'C':
			{
				tamanhoOutputString = substitution_C(tamanhoOutputString);
				if (tamanhoOutputString == 0)
				{
					reductible = 0;
					countVet--;
				}
				countVet++;
				#ifdef COUNTERC
					countC++;
				#endif
				break;
			}
			case 's':
			{
				tamanhoOutputString = substitution_s(tamanhoOutputString);
				if (tamanhoOutputString == 0)
				{
					reductible = 0;
					countVet--;
				}
				countVet++;
				#ifdef COUNTERSLINHA
					countSlinha++;
				#endif
				break;
			}
			case 'b':
			{
				tamanhoOutputString = substitution_b(tamanhoOutputString);
				if (tamanhoOutputString == 0)
				{
					reductible = 0;
					countVet--;
				}
				countVet++;
				#ifdef COUNTERBLINHA
					countBlinha++;
				#endif
				break;
			}
			case 'c':
			{
				tamanhoOutputString = substitution_c(tamanhoOutputString);
				if (tamanhoOutputString == 0)
				{
					reductible = 0;
					countVet--;
				}
				countVet++;
				#ifdef COUNTERCLINHA
					countClinha++;
				#endif
				break;
			}
			// default:
			// {
			// 	reductible = 0;
			// }
			#ifdef ITERATIONS
	            iterations++;
			#endif // ITERATIONS
    	}
	}

	#ifdef COUNTER
        counter = countK + countS + countI;
    #endif // COUNTER
     //printf("countK = %d , countS = %d, countI = %d, countB = %d, countC = %d, countSlinha = %d, countBlinha = %d, countClinha = %d\n", countK, countS, countI, countB, countC, countSlinha, countBlinha, countClinha);
     printf("%s\n", strings[(countVet%2)]);

	return 0;
}