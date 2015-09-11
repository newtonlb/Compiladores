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


void removeParenthesis()
{
		int removed = 0;
		int lvl = 1;
		int i = 0;
        //printf("strings[(countVet%2)] = %s\n", strings[(countVet%2)]);
      //  system("PAUSE");
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
                   

                  
                    int teste = strlen(strings[(countVet%2)]);
                 
                    memcpy((strings[(countVet+1)%2] + i -1), (strings[(countVet%2)] + i + 1), (teste - i )*sizeof(char));
                    
                    //memcpy(strings[(countVet%2)], strings[(countVet+1)%2], ARRAY_SIZE*sizeof(char));


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

	//memcpy(strings[(countVet+1)%2], blank, ARRAY_SIZE*sizeof(char));

	if(strings[(countVet%2)][1] == '(')
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
	if(strings[(countVet%2)][posBinit] == '(')
	{
		posBfinal = searchParenthesis(posBinit);

		
	}
	else
	{
		posBfinal = posBinit;
	}
	memcpy(strings[(countVet+1)%2], strings[(countVet%2)] + posAinit, posAfinal*sizeof(char));
	memcpy(strings[(countVet+1)%2] + (posAfinal - posAinit + 1) , strings[(countVet%2)] + posBfinal +1, ((strlen(strings[(countVet%2)])) - posBfinal)*sizeof(char));

	//memcpy(strings[(countVet%2)], strings[(countVet+1)%2], ARRAY_SIZE*sizeof(char));
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
	if(strings[(countVet%2)][posBinit] == '(')
	{


		posBfinal = searchParenthesis(posBinit);
	}
	else
	{
		posBfinal = posBinit;
	}
	posCinit = posBfinal + 1;
	if(strings[(countVet%2)][posCinit] == '(')
	{
		posCfinal = searchParenthesis(posCinit);
	}
	else
	{
		posCfinal = posCinit;
	}

	memcpy(strings[(countVet+1)%2], "(", sizeof(char)); //(
	//printf("%s\n", strings[(countVet+1)%2]);
	stringLastPos++;
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posAinit, (posAfinal - posAinit +1)*sizeof(char));  //(a
	//printf("%s\n",strings[(countVet+1)%2] );
	stringLastPos += posAfinal - posAinit +1;
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posCinit, (posCfinal - posCinit +1)*sizeof(char)); //(ac
	//printf("%s\n",strings[(countVet+1)%2]);
	stringLastPos += posCfinal - posCinit +1;
	memcpy(strings[(countVet+1)%2] + stringLastPos, ")", sizeof(char)); //(ac)
	//printf("%s\n",strings[(countVet+1)%2] );
	stringLastPos++;
	memcpy(strings[(countVet+1)%2] +stringLastPos, "(", sizeof(char));// (ac)(
	//printf("%s\n",strings[(countVet+1)%2] );
	stringLastPos++;
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] +posBinit, (posBfinal-posBinit +1)*sizeof(char));
	//printf("%s\n",strings[(countVet+1)%2] );
	stringLastPos += posBfinal-posBinit +1;
	memcpy(strings[(countVet+1)%2] + stringLastPos ,strings[(countVet%2)] + posCinit, (posCfinal-posCinit +1)*sizeof(char));
	//printf("%s\n",strings[(countVet+1)%2] );
	stringLastPos+= posCfinal-posCinit +1;
	memcpy(strings[(countVet+1)%2] + stringLastPos, ")", sizeof(char));
	//printf("%s\n",strings[(countVet+1)%2] );
	stringLastPos++;
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posCfinal +1, ((strlen(strings[(countVet%2)]))-posCfinal +1)*sizeof(char));
	//printf("%s\n",strings[(countVet+1)%2] );

	//memcpy(strings[(countVet%2)], strings[(countVet+1)%2], ARRAY_SIZE*sizeof(char));
}

void substitution_I()
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

    int tamanhoOutputString = strlen(strings[(countVet%2)]);

	memcpy(strings[(countVet+1)%2] + posAfinal, strings[(countVet%2)] + posAfinal + 1, (tamanhoOutputString-posAfinal +1)*sizeof(char));

	//memcpy(strings[(countVet%2)], strings[(countVet+1)%2], ((strlen(strings[(countVet+1)%2])+1)*sizeof(char)));

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
	//printf("F = %d %d", posFinit, posFfinal);
	posGinit = posFfinal + 1;
	if (strings[(countVet%2)][posGinit] == '(')
	{
		posGfinal = searchParenthesis(posGinit);
	}
	else
	{
		posGfinal = posGinit;
	}
	//printf("G = %d %d", posGinit, posGfinal);

	posXinit = posGfinal + 1;
	if (strings[(countVet%2)][posXinit] == '(')
	{
		posXfinal = searchParenthesis(posXinit);
	}
	else
	{
		posXfinal = posXinit;
	}
	//printf("X = %d %d", posXinit, posXfinal);

	int tamanho = strlen(strings[(countVet%2)]);

	memcpy(strings[(countVet+1)%2], strings[(countVet%2)] + posFinit, (posFfinal - posFinit + 1)*sizeof(char));
	stringLastPos+= (posFfinal - posFinit + 1);
	//printf("strings[(countVet+1)%2] = %s strings[(countVet%2)] = %s\n\n", strings[(countVet+1)%2], strings[(countVet%2)]);
	memcpy(strings[(countVet+1)%2] + stringLastPos, "(", sizeof(char));
	stringLastPos++;
	//printf("strings[(countVet+1)%2] = %s strings[(countVet%2)] = %s\n\n", strings[(countVet+1)%2], strings[(countVet%2)]);
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posGinit, (posGfinal - posGinit +1)*sizeof(char));
	stringLastPos += (posGfinal - posGinit) + 1;
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posXinit, (posXfinal - posXinit + 1)*sizeof(char));
	stringLastPos += (posXfinal - posXinit) + 1;
	memcpy(strings[(countVet+1)%2] + stringLastPos, ")", sizeof(char));
	stringLastPos++;
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posXfinal + 1, (tamanho - posXfinal + 1)*sizeof(char));


	int tamanhoOutputString = strlen(strings[(countVet%2)]);

	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posXfinal + 1, (tamanhoOutputString-posXfinal+1)*sizeof(char));

	//memcpy(strings[(countVet%2)], strings[(countVet+1)%2], ((strlen(strings[(countVet+1)%2])+1)*sizeof(char)));

	//printf("strings[(countVet%2)] = %s\n\n", strings[(countVet%2)]);

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
	if (strings[(countVet%2)][posXinit] == '(')
	{
		posXfinal = searchParenthesis(posXinit);
	}
	else
	{
		posXfinal = posXinit;
	}

	posYinit = posXfinal + 1;
	if (strings[(countVet%2)][posYinit] == '(')
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

	int tamanho = strlen(strings[(countVet%2)]);

	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posYfinal + 1, (tamanho-posYfinal+1)*sizeof(char));

	//memcpy(strings[(countVet%2)], strings[(countVet+1)%2], ((strlen(strings[(countVet+1)%2])+1)*sizeof(char)));
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
	if (strings[(countVet%2)][posBinit] == '(')
	{
		posBfinal = searchParenthesis(posBinit);
	}
	else
	{
		posBfinal = posBinit;
	}

	posCinit = posBfinal + 1;
	if (strings[(countVet%2)][posCinit] == '(')
	{
		posCfinal = searchParenthesis(posCinit);	

	}
	else
	{
		posCfinal = posCinit;
	}

	posDinit = posCfinal + 1;
	if (strings[(countVet%2)][posDinit] == '(')
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

	memcpy(strings[(countVet+1)%2] + stringLastPos, "(", sizeof(char));
	stringLastPos++;

	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posBinit, (posBfinal - posBinit + 1)*sizeof(char));
	stringLastPos += (posBfinal - posBinit + 1);

	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posDinit, (posDfinal - posDinit + 1)*sizeof(char));
	stringLastPos += (posDfinal - posDinit + 1);

	memcpy(strings[(countVet+1)%2] + stringLastPos, ")", sizeof(char));
	stringLastPos++;

	memcpy(strings[(countVet+1)%2] + stringLastPos, "(", sizeof(char));
	stringLastPos++;

	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posCinit, (posCfinal - posCinit + 1)*sizeof(char));
	stringLastPos += (posCfinal - posCinit + 1);

	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posDinit, (posDfinal - posDinit + 1)*sizeof(char));
	stringLastPos += (posDfinal - posDinit + 1);

	memcpy(strings[(countVet+1)%2] + stringLastPos, ")", sizeof(char));
	stringLastPos++;

	int tamanhoOutputString = strlen(strings[(countVet%2)]);

	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posDfinal + 1, (tamanhoOutputString-posDfinal +1)*sizeof(char));

	//memcpy(strings[(countVet%2)], strings[(countVet+1)%2], ((strlen(strings[(countVet+1)%2])+1)*sizeof(char)));

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
	if(strings[(countVet%2)][posBinit] == '(')
	{


		posBfinal = searchParenthesis(posBinit);
	}
	else
	{
		posBfinal = posBinit;
	}
	posCinit = posBfinal + 1;
	if(strings[(countVet%2)][posCinit] == '(')
	{
		posCfinal = searchParenthesis(posCinit);
	}
	else
	{
		posCfinal = posCinit;
	}
	posDinit = posCfinal + 1;
	if(strings[(countVet%2)][posDinit] == '(')
	{
		posDfinal = searchParenthesis(posDinit);
	}
	else
	{
		posDfinal = posDinit;
	}


	 //(
	//printf("%s\n", strings[(countVet+1)%2]);
	
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posAinit, (posAfinal - posAinit +1)*sizeof(char));  //a
	//printf("%s\n",strings[(countVet+1)%2] );
	stringLastPos += posAfinal - posAinit +1;
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posBinit, (posBfinal - posBinit +1)*sizeof(char)); //b
	//printf("%s\n",strings[(countVet+1)%2]);
	stringLastPos += posBfinal - posBinit +1;
	memcpy(strings[(countVet+1)%2] + stringLastPos, "(", sizeof(char)); //ab(
	//printf("%s\n",strings[(countVet+1)%2] );
	stringLastPos++;
	//printf("%s\n",strings[(countVet+1)%2] );
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] +posCinit, (posCfinal-posCinit +1)*sizeof(char));//ab(c
	//printf("%s\n",strings[(countVet+1)%2] );
	stringLastPos += posCfinal-posCinit +1;
	memcpy(strings[(countVet+1)%2] + stringLastPos ,strings[(countVet%2)] + posDinit, (posDfinal-posDinit +1)*sizeof(char));//ab(cd
	//printf("%s\n",strings[(countVet+1)%2] );
	stringLastPos+= posCfinal-posCinit +1;
	memcpy(strings[(countVet+1)%2] + stringLastPos, ")", sizeof(char));//ab(cd)
	//printf("%s\n",strings[(countVet+1)%2] );
	stringLastPos++;
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posDfinal +1, ((strlen(strings[(countVet%2)]))-posDfinal +1)*sizeof(char));
	//printf("%s\n",strings[(countVet+1)%2] );

	//memcpy(strings[(countVet%2)], strings[(countVet+1)%2], ARRAY_SIZE*sizeof(char));
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
	if(strings[(countVet%2)][posBinit] == '(')
	{
		posBfinal = searchParenthesis(posBinit);
	}
	else
	{
		posBfinal = posBinit;
	}
	posCinit = posBfinal + 1;
	if(strings[(countVet%2)][posCinit] == '(')
	{
		posCfinal = searchParenthesis(posCinit);
	}
	else
	{
		posCfinal = posCinit;
	}
	posDinit = posCfinal + 1;
	if (strings[(countVet%2)][posDinit] == '(')
	{
		posDfinal = searchParenthesis(posDinit);
	}
	else
	{
		posDfinal = posDinit;
	}
	
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posAinit, (posAfinal - posAinit + 1)*sizeof(char));
	
	stringLastPos += (posAfinal - posAinit + 1);
	
	memcpy(strings[(countVet+1)%2] + stringLastPos, "(", sizeof(char));
	
	stringLastPos++;
	
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posBinit, (posBfinal - posBinit + 1)*sizeof(char));
	
	stringLastPos += (posBfinal - posBinit + 1);
	
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posDinit, (posDfinal - posDinit + 1)*sizeof(char));
	
	stringLastPos += (posDfinal - posDinit + 1);
	
	memcpy(strings[(countVet+1)%2] + stringLastPos, ")", sizeof(char));
	
	stringLastPos++;
	
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posCinit, (posCfinal - posCinit + 1)*sizeof(char));
	
	stringLastPos += (posCfinal - posCinit + 1);	
	
	int tamanho = strlen(strings[(countVet%2)]);
	
	memcpy(strings[(countVet+1)%2] + stringLastPos, strings[(countVet%2)] + posDfinal + 1, (tamanho - posDfinal + 1)*sizeof(char));
	
	//memcpy(strings[(countVet%2)], strings[(countVet+1)%2], (strlen(strings[(countVet+1)%2]) + 1)*sizeof(char));
	
	//printf("%s\n", strings[(countVet%2)]);


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
		while(strings[countVet%2][0] == '(')
		{
			removeParenthesis();
			countVet++;

		}

		tamanhoOutputString = strlen(strings[(countVet%2)]);

		if(strings[countVet%2][0] == 'K' && tamanhoOutputString > 2)
		{
			substitution_K();
			countVet++;
			//printf("%s\n", strings[(countVet%2)]);
			#ifdef COUNTERK
                countK++;
			#endif // COUNTERK
		}
		else if(strings[countVet%2][0] == 'S' && tamanhoOutputString > 3)
		{
			substitution_S();
			countVet++;
			//printf("%s\n", strings[(countVet%2)]);
			#ifdef COUNTERS
                countS++;
            #endif // COUNTERS
		}
		else if (strings[countVet%2][0] == 'I' && tamanhoOutputString > 1)
		{	
			substitution_I();
			countVet++;
			//printf("%s\n", strings[(countVet%2)]);
			#ifdef COUNTERI	
				countI++;
			#endif
		}
		else if (strings[countVet%2][0] == 'B' && tamanhoOutputString > 3)
		{
			substitution_B();
			countVet++;
			//printf("%s\n", strings[(countVet%2)]);
			#ifdef COUNTERB	
				countB++;
			#endif
		}
		else if (strings[countVet%2][0] == 'C' && tamanhoOutputString > 3)
		{
			substitution_C();
			countVet++;
			//printf("%s\n", strings[(countVet%2)]);
			#ifdef COUNTERC
				countC++;
			#endif
		}
		else if (strings[countVet%2][0] == 's' && tamanhoOutputString > 4)
		{
			substitution_s();
			countVet++;
			//printf("%s\n", strings[(countVet%2)]);
			#ifdef COUNTERSLINHA
				countSlinha++;
			#endif
		}
		else if(strings[countVet%2][0] == 'b' && tamanhoOutputString > 4)
		{
			substitution_b();
			countVet++;
			//printf("%s\n", strings[(countVet%2)]);
			#ifdef COUNTERBLINHA
				countBlinha++;
			#endif
		}
		else if(strings[countVet%2][0] == 'c' && tamanhoOutputString > 4)
		{
			substitution_c();
			countVet++;
			//printf("%s\n", strings[(countVet%2)]);
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
            //printf("\n");
	}

	#ifdef COUNTER
        counter = countK + countS + countI;
    #endif // COUNTER
     //printf("countK = %d , countS = %d, countI = %d, countB = %d\n", countK, countS, countI, countB);
     printf("%s\n", strings[(countVet%2)]);

	return 0;
}