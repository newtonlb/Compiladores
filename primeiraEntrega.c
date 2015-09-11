#include "primeiraEntrega.h"

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
        //printf("OutPutString = %s\n", outputString);
      //  system("PAUSE");
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
                if(lvl == 0)
                {
                   
                    memcpy(newString, outputString + 1,(i-1)*sizeof(char)) ;
                   

                  
                    int teste = strlen(outputString);
                 
                    memcpy((newString + i -1), (outputString + i + 1), (teste - i )*sizeof(char));
                    
                    memcpy(outputString, newString, ARRAY_SIZE*sizeof(char));


                    removed = 1;
                }
			}

		}
}

int searchParenthesis(int initPos)
{
	int i = 0;
	int lvl = 0;
	int removed = 0;

	if(outputString[initPos] == '(')
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
				if(lvl == 0)
                {
                    removed = 1;
                }
			}
		}

	}
	return i;
}

void substitution_K()
{
	int i = 0;
	int initPos = 1;
	int finalPos;
	int posAinit = 0;
	int posAfinal = 0;
	int posBinit = 0;
	int posBfinal = 0;
	int posCinit = 0;
	int posCfinal = 0;

	//memcpy(newString, blank, ARRAY_SIZE*sizeof(char));

	if(outputString[1] == '(')
	{
		posAinit = 1;
		posAfinal = searchParenthesis(1);

	}
	else
	{
		posAinit = 1;
		posAfinal = posAinit;
	}
	posBinit = posAfinal + 1;
	if(outputString[posBinit] == '(')
	{
		posBfinal = searchParenthesis(posBinit);

		
	}
	else
	{
		posBfinal = posBinit;
	}
	memcpy(newString, outputString + posAinit, posAfinal*sizeof(char));
	memcpy(newString + (posAfinal - posAinit + 1) , outputString + posBfinal +1, ((strlen(outputString)) - posBfinal)*sizeof(char));

	memcpy(outputString, newString, ARRAY_SIZE*sizeof(char));
}


void substitution_S()
{

	int posAinit = 0;
	int posAfinal = 0;
	int posBinit = 0;
	int posBfinal = 0;
	int posCinit = 0;
	int posCfinal = 0;
	int stringLastPos = 0;

	if(outputString[1] == '(')
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
	if(outputString[posBinit] == '(')
	{


		posBfinal = searchParenthesis(posBinit);
	}
	else
	{
		posBfinal = posBinit;
	}
	posCinit = posBfinal + 1;
	if(outputString[posCinit] == '(')
	{
		posCfinal = searchParenthesis(posCinit);
	}
	else
	{
		posCfinal = posCinit;
	}

	memcpy(newString, "(", sizeof(char)); //(
	//printf("%s\n", newString);
	stringLastPos++;
	memcpy(newString + stringLastPos, outputString + posAinit, (posAfinal - posAinit +1)*sizeof(char));  //(a
	//printf("%s\n",newString );
	stringLastPos += posAfinal - posAinit +1;
	memcpy(newString + stringLastPos, outputString + posCinit, (posCfinal - posCinit +1)*sizeof(char)); //(ac
	//printf("%s\n",newString);
	stringLastPos += posCfinal - posCinit +1;
	memcpy(newString + stringLastPos, ")", sizeof(char)); //(ac)
	//printf("%s\n",newString );
	stringLastPos++;
	memcpy(newString +stringLastPos, "(", sizeof(char));// (ac)(
	//printf("%s\n",newString );
	stringLastPos++;
	memcpy(newString + stringLastPos, outputString +posBinit, (posBfinal-posBinit +1)*sizeof(char));
	//printf("%s\n",newString );
	stringLastPos += posBfinal-posBinit +1;
	memcpy(newString + stringLastPos ,outputString + posCinit, (posCfinal-posCinit +1)*sizeof(char));
	//printf("%s\n",newString );
	stringLastPos+= posCfinal-posCinit +1;
	memcpy(newString + stringLastPos, ")", sizeof(char));
	//printf("%s\n",newString );
	stringLastPos++;
	memcpy(newString + stringLastPos, outputString + posCfinal +1, ((strlen(outputString))-posCfinal +1)*sizeof(char));
	//printf("%s\n",newString );

	memcpy(outputString, newString, ARRAY_SIZE*sizeof(char));
}

void substitution_I()
{
    int initPos = 1;
    int posAinit = 0;
    int posAfinal = 0;
    if(outputString[initPos] == '(')
    {
        posAinit = initPos;
        posAfinal = searchParenthesis(initPos);
    }
    else
    {
        posAinit = initPos;
        posAfinal = posAinit;
    }

    memcpy(newString, outputString + posAinit, (posAfinal-posAinit+1)*sizeof(char));

    int tamanhoOutputString = strlen(outputString);

	memcpy(newString + posAfinal, outputString + posAfinal + 1, (tamanhoOutputString-posAfinal +1)*sizeof(char));

	memcpy(outputString, newString, ((strlen(newString)+1)*sizeof(char)));

}

// B f g x => f(gx)
void substitution_B()
{
	int initPos = 1;
	int posFinit = 0;
	int posFfinal = 0;
	int posGinit = 0;
	int posGfinal = 0;
	int posXinit = 0;
	int posXfinal = 0;
	int stringLastPos = 0;

	if (outputString[initPos] == '(')
	{
		posFinit = initPos;
		posFfinal = searchParenthesis(posFinit);
	}
	else
	{
		posFinit = initPos;
		posFfinal = posFinit;
	}
	printf("F = %d %d", posFinit, posFfinal);
	posGinit = posFfinal + 1;
	if (outputString[posGinit] == '(')
	{
		posGfinal = searchParenthesis(posGinit);
	}
	else
	{
		posGfinal = posGinit;
	}
	printf("G = %d %d", posGinit, posGfinal);

	posXinit = posGfinal + 1;
	if (outputString[posXinit] == '(')
	{
		posXfinal = searchParenthesis(posXinit);
	}
	else
	{
		posXfinal = posXinit;
	}
	printf("X = %d %d", posXinit, posXfinal);

	int tamanho = strlen(outputString);

	memcpy(newString, outputString + posFinit, (posFfinal - posFinit + 1)*sizeof(char));
	stringLastPos+= (posFfinal - posFinit + 1);
	printf("newString = %s outputString = %s\n\n", newString, outputString);
	memcpy(newString + stringLastPos, "(", sizeof(char));
	stringLastPos++;
	printf("newString = %s outputString = %s\n\n", newString, outputString);
	memcpy(newString + stringLastPos, outputString + posGinit, (posGfinal - posGinit +1)*sizeof(char));
	stringLastPos += (posGfinal - posGinit) + 1;
	memcpy(newString + stringLastPos, outputString + posXinit, (posXfinal - posXinit + 1)*sizeof(char));
	stringLastPos += (posXfinal - posXinit) + 1;
	memcpy(newString + stringLastPos, ")", sizeof(char));
	stringLastPos++;
	memcpy(newString + stringLastPos, outputString + posXfinal + 1, (tamanho - posXfinal + 1)*sizeof(char));


	int tamanhoOutputString = strlen(outputString);

	memcpy(newString + stringLastPos, outputString + posXfinal + 1, (tamanhoOutputString-posXfinal+1)*sizeof(char));

	memcpy(outputString, newString, ((strlen(newString)+1)*sizeof(char)));

	printf("outputString = %s\n\n", outputString);

}


void substitution_C()
{
	int initPos = 1;
	int posFinit = 0;
	int posFfinal = 0;
	int posYinit = 0;
	int posYfinal = 0;
	int posXinit = 0;
	int posXfinal = 0;

	if (outputString[initPos] == '(')
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
	if (outputString[posXinit] == '(')
	{
		posXfinal = searchParenthesis(posXinit);
	}
	else
	{
		posXfinal = posXinit;
	}

	posYinit = posXfinal + 1;
	if (outputString[posYinit] == '(')
	{
		posYfinal = searchParenthesis(posYinit);	

	}
	else
	{
		posYfinal = posYinit;
	}

	int stringLastPos = 0;
	memcpy(newString + stringLastPos, outputString + posFinit, (posFfinal - posFinit + 1)*sizeof(char));
	stringLastPos += (posFfinal - posFinit + 1);
	memcpy(newString + stringLastPos, outputString + posYinit, (posYfinal - posYinit + 1)*sizeof(char));
	stringLastPos += (posYfinal - posYinit + 1);
	memcpy(newString + stringLastPos, outputString + posXinit, (posXfinal - posXinit + 1)*sizeof(char));
	stringLastPos += (posXfinal - posXinit + 1);

	int tamanhoOutputString = strlen(outputString);

	memcpy(newString + stringLastPos, outputString + posYfinal + 1, (tamanhoOutputString-posYfinal+1)*sizeof(char));

	memcpy(outputString, newString, ((strlen(newString)+1)*sizeof(char)));
}

// NAO TERMINADO
// S'abcd => a(bd)(cd)
void substitution_s()
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

	if (outputString[initPos] == '(')
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
	if (outputString[posBinit] == '(')
	{
		posBfinal = searchParenthesis(posBinit);
	}
	else
	{
		posBfinal = posBinit;
	}

	posCinit = posBfinal + 1;
	if (outputString[posCinit] == '(')
	{
		posCfinal = searchParenthesis(posCinit);	

	}
	else
	{
		posCfinal = posCinit;
	}

	posDinit = posCfinal + 1;
	if (outputString[posDinit] == '(')
	{
		posDfinal = searchParenthesis(posDinit);	

	}
	else
	{
		posDfinal = posDinit;
	}

	
	int stringLastPos = 0;
	memcpy(newString + stringLastPos, outputString + posAinit, (posAfinal - posAinit + 1)*sizeof(char));
	stringLastPos += (posAfinal - posAinit + 1);

	memcpy(newString + stringLastPos, "(", sizeof(char));
	stringLastPos++;

	memcpy(newString + stringLastPos, outputString + posBinit, (posBfinal - posBinit + 1)*sizeof(char));
	stringLastPos += (posBfinal - posBinit + 1);

	memcpy(newString + stringLastPos, outputString + posDinit, (posDfinal - posDinit + 1)*sizeof(char));
	stringLastPos += (posDfinal - posDinit + 1);

	memcpy(newString + stringLastPos, ")", sizeof(char));
	stringLastPos++;

	memcpy(newString + stringLastPos, "(", sizeof(char));
	stringLastPos++;

	memcpy(newString + stringLastPos, outputString + posCinit, (posCfinal - posCinit + 1)*sizeof(char));
	stringLastPos += (posCfinal - posCinit + 1);

	memcpy(newString + stringLastPos, outputString + posDinit, (posDfinal - posDinit + 1)*sizeof(char));
	stringLastPos += (posDfinal - posDinit + 1);

	memcpy(newString + stringLastPos, ")", sizeof(char));
	stringLastPos++;

	int tamanhoOutputString = strlen(outputString);

	memcpy(newString + stringLastPos, outputString + posDfinal + 1, (tamanhoOutputString-posDfinal +1)*sizeof(char));

	memcpy(outputString, newString, ((strlen(newString)+1)*sizeof(char)));

}
void substitution_b()
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

	if(outputString[1] == '(')
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
	if(outputString[posBinit] == '(')
	{


		posBfinal = searchParenthesis(posBinit);
	}
	else
	{
		posBfinal = posBinit;
	}
	posCinit = posBfinal + 1;
	if(outputString[posCinit] == '(')
	{
		posCfinal = searchParenthesis(posCinit);
	}
	else
	{
		posCfinal = posCinit;
	}
	posDinit = posCfinal + 1;
	if(outputString[posDinit] == '(')
	{
		posDfinal = searchParenthesis(posDinit);
	}
	else
	{
		posDfinal = posDinit;
	}


	 //(
	//printf("%s\n", newString);
	
	memcpy(newString + stringLastPos, outputString + posAinit, (posAfinal - posAinit +1)*sizeof(char));  //a
	//printf("%s\n",newString );
	stringLastPos += posAfinal - posAinit +1;
	memcpy(newString + stringLastPos, outputString + posBinit, (posBfinal - posBinit +1)*sizeof(char)); //b
	//printf("%s\n",newString);
	stringLastPos += posBfinal - posBinit +1;
	memcpy(newString + stringLastPos, "(", sizeof(char)); //ab(
	//printf("%s\n",newString );
	stringLastPos++;
	//printf("%s\n",newString );
	memcpy(newString + stringLastPos, outputString +posCinit, (posCfinal-posCinit +1)*sizeof(char));//ab(c
	//printf("%s\n",newString );
	stringLastPos += posCfinal-posCinit +1;
	memcpy(newString + stringLastPos ,outputString + posDinit, (posDfinal-posDinit +1)*sizeof(char));//ab(cd
	//printf("%s\n",newString );
	stringLastPos+= posCfinal-posCinit +1;
	memcpy(newString + stringLastPos, ")", sizeof(char));//ab(cd)
	//printf("%s\n",newString );
	stringLastPos++;
	memcpy(newString + stringLastPos, outputString + posDfinal +1, ((strlen(outputString))-posDfinal +1)*sizeof(char));
	//printf("%s\n",newString );

	memcpy(outputString, newString, ARRAY_SIZE*sizeof(char));
}

void substitution_c()
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

	if(outputString[initPos] == '(')
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
	if(outputString[posBinit] == '(')
	{
		posBfinal = searchParenthesis(posBinit);
	}
	else
	{
		posBfinal = posBinit;
	}
	posCinit = posBfinal + 1;
	if(outputString[posCinit] == '(')
	{
		posCfinal = searchParenthesis(posCinit);
	}
	else
	{
		posCfinal = posCinit;
	}
	posDinit = posCfinal + 1;
	if (outputString[posDinit] == '(')
	{
		posDfinal = searchParenthesis(posDinit);
	}
	else
	{
		posDfinal = posDinit;
	}
	
	memcpy(newString + stringLastPos, outputString + posAinit, (posAfinal - posAinit + 1)*sizeof(char));
	
	stringLastPos += (posAfinal - posAinit + 1);
	
	memcpy(newString + stringLastPos, "(", sizeof(char));
	
	stringLastPos++;
	
	memcpy(newString + stringLastPos, outputString + posBinit, (posBfinal - posBinit + 1)*sizeof(char));
	
	stringLastPos += (posBfinal - posBinit + 1);
	
	memcpy(newString + stringLastPos, outputString + posDinit, (posDfinal - posDinit + 1)*sizeof(char));
	
	stringLastPos += (posDfinal - posDinit + 1);
	
	memcpy(newString + stringLastPos, ")", sizeof(char));
	
	stringLastPos++;
	
	memcpy(newString + stringLastPos, outputString + posCinit, (posCfinal - posCinit + 1)*sizeof(char));
	
	stringLastPos += (posCfinal - posCinit + 1);	
	
	int tamanho = strlen(outputString);
	
	memcpy(newString + stringLastPos, outputString + posDfinal + 1, (tamanho - posDfinal + 1)*sizeof(char));
	
	memcpy(outputString, newString, (tamanho + 1)*sizeof(char));
	
	printf("%s\n", outputString);


}


int main()
{

	FILE* fileout;
	fileout = fopen("output.txt", "w");
	int lvl = 0;
	int i = 0;
	int removed = 0;
	int reductible = 1;
    int tamanhoOutputString = 0;
    readFile();

	while(reductible == 1)
	{
		while(outputString[0] == '(')
		{
			removeParenthesis();

		}

		tamanhoOutputString = strlen(outputString);

		if(outputString[0] == 'K' && tamanhoOutputString > 2)
		{
			substitution_K();
			#ifdef COUNTERK
                countK++;
			#endif // COUNTERK
		}
		else if(outputString[0] == 'S' && tamanhoOutputString > 3)
		{
			substitution_S();
			#ifdef COUNTERS
                countS++;
            #endif // COUNTERS
		}
		else if (outputString[0] == 'I' && tamanhoOutputString > 1)
		{	
			substitution_I();
			#ifdef COUNTERI	
				countI++;
			#endif
		}
		else if (outputString[0] == 'B' && tamanhoOutputString > 3)
		{
			substitution_B();
			#ifdef COUNTERB	
				countB++;
			#endif
		}
		else if (outputString[0] == 'C' && tamanhoOutputString > 3)
		{
			substitution_C();
			#ifdef COUNTERC
				countC++;
			#endif
		}
		else if (outputString[0] == 's' && tamanhoOutputString > 4)
		{
			substitution_s();
			#ifdef COUNTERSLINHA
				countSlinha++;
			#endif
		}
		else if(outputString[0] == 'b' && tamanhoOutputString > 4)
		{
			substitution_b();
			#ifdef COUNTERBLINHA
				countBlinha++;
			#endif
		}
		else if(outputString[0] == 'c' && tamanhoOutputString > 4)
		{
			substitution_c();
			#ifdef COUNTERCLINHA
				countClinha++;
			#endif
		}
		else
		{

			reductible = 0;
		}
		#ifdef ITERATIONS
            iterations++;
		#endif // ITERATIONS
	}

	#ifdef COUNTER
        counter = countK + countS + countI;
    #endif // COUNTER
     printf("countK = %d , countS = %d, countI = %d, countB = %d\n", countK, countS, countI, countB);
     printf("%s\n", outputString);

	return 0;
}