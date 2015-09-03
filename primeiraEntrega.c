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
                    //printf("%d\n", i);

                  //  printf("NewStrong = %d , OutputString = %d\n",strlen(newString), strlen(outputString));
                   // system("PAUSE");
                    memcpy(newString, outputString + 1,(i-1)*sizeof(char)) ;
                   // printf("NewString : %s\n",newString);
                   // printf("OutputString : %s\n", outputString);
                   // system("PAUSE");

                  //  printf("NewStrong = %d , OutputString = %d\n",strlen(newString), strlen(outputString));
                   // system("PAUSE");
                    int teste = strlen(outputString);
                  //  printf("i = %d\n", i);
                    memcpy((newString + i -1), (outputString + i + 1), (teste - i )*sizeof(char));
                    //memcpy((newString + i -1), (outputString + i + 1), (ARRAY_SIZE - i )*sizeof(char));
                   // printf("NewString : %s\n",newString);
                    //printf("OutputString : %s\n", outputString);
                    //system("PAUSE");
                  //  printf("New String = %s\n", newString);

                  //  printf("NewStrong = %d , OutputString = %d\n",strlen(newString), strlen(outputString));
                  //  system("PAUSE");
                    memcpy(outputString, newString, ARRAY_SIZE*sizeof(char));

                 //   printf("NewStrong = %d , OutputString = %d\n",strlen(newString), strlen(outputString));
                 //   system("PAUSE");

                    //printf("NewString : %s\n",newString);
                   // printf("OutputString : %s\n", outputString);
                    //system("PAUSE");

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
	memcpy(newString + (posAfinal - posAinit + 1) , outputString + posBfinal +1, ((strlen(outputString)) - posBfinal)*sizeof(char));
	//printf("%s\n", newString );

	memcpy(outputString, newString, ARRAY_SIZE*sizeof(char));
}


void substitution_S(){

	int posAinit = 0;
	int posAfinal = 0;
	int posBinit = 0;
	int posBfinal = 0;
	int posCinit = 0;
	int posCfinal = 0;
	int stringLastPos = 0;

	//memcpy(newString, blank, ARRAY_SIZE*sizeof(char));
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
			 //printf("%s\n", outputString);
			#ifdef COUNTERK
                countK++;
			#endif // COUNTERK
		}
		else if(outputString[0] == 'S' && tamanhoOutputString > 3)
		{
			substitution_S();
			 //printf("%s\n", outputString);
			#ifdef COUNTERS
                countS++;
            #endif // COUNTERS
		}
		else
		{

			reductible = 0;
		}
		#ifdef ITERATIONS
            //printf("%s\n", outputString);
            //printf("%lu\n",strlen(outputString));
            iterations++;
		#endif // ITERATIONS
	}

	#ifdef COUNTER
        counter = countK + countS;
    #endif // COUNTER
     printf("countK = %d , countS = %d\n", countK, countS);
     printf("%s\n", outputString);

	return 0;
}




