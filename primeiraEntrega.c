#include "primeiraEntrega.h"

int main()
{

	FILE* fileout;
	fileout = fopen("output.txt", "w");
	int lvl = 0;
	int i = 0;
	int removed = 0;
	int reductible = 1;

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
			 //printf("%s\n", outputString);
			#ifdef COUNTERK
                countK++;
			#endif // COUNTERK
		}
		else if(outputString[0] == 'S' && strlen(outputString) > 3)
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
     printf("%s\n", outputString);

	return 0;
}
