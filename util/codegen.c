#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct parametro
{
	int start, end, per;
	bool peof;
}PARAM;

int main ()
{
	FILE * arquivo = NULL;
	PARAM * pmtrs = NULL;
	int paramc, cont = 0;
	char in[64], comando[64];
	printf ("Arquivo: ");
	scanf ("%[^\n]", in);
	arquivo = fopen (in, "a");
	printf ("Comando: ");
	scanf ("\n%[^\n]", comando);
	printf ("Número de parâmetros: ");
	scanf ("\n%i", &paramc);
	pmtrs = (PARAM *) calloc (paramc, sizeof (PARAM));
	for (int i = 0; i < paramc; i++)
	{
		printf ("----parâmetro %i----\n", i + 1);
		printf ("De: ");
		scanf ("%i", &pmtrs[i].start);
		printf ("Até: ");
		scanf ("%i", &pmtrs[i].end);
		printf ("Incremente: ");
		scanf ("%i", &pmtrs[i].per);
		pmtrs[i].peof = false;
	}
	fprintf (arquivo, "\n");
	while (cont < paramc)
	{
		fprintf (arquivo, "%s ", comando);
		for (int i = 0; i < paramc; i++)
		{
			fprintf (arquivo, "%i ", pmtrs[i].start);
			if ( pmtrs[i].peof == false && ( (pmtrs[i].start >= pmtrs[i].end && pmtrs[i].per >= 0) || (pmtrs[i].start <= pmtrs[i].end && pmtrs[i].per <= 0) ) )
			{
				cont++;
				pmtrs[i].peof = true;
			}
			else if (pmtrs[i].peof == false)
			{
				pmtrs[i].start += pmtrs[i].per;
			}
		}
		fprintf (arquivo, "\n");
	}
}
