#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "./source/lib.h"

int main (int argc, char * argv[])
{
	if (argc < 4 || argc > 4)
	{
		printf ("Uso: [C ou D] [in] [out]\r");
		return -1;
	}
	
	int magic, w, h, c, count = 0;
	RGB tmp, cor;
	unsigned char q;
	FILE *in =  fopen (argv[2], "r"), *out = fopen(argv[3], "w");

	if (in == NULL)
	{
		printf ("Arquivo inexistente '%s'\r", argv[2]);
		return -1;
	}
	
	fscanf (in,   "P%i\r", &magic);
	fprintf (out, "P%i\r", magic);

	fscanf (in,   "%i %i\r%i\r", &w, &h, &c);
	fprintf (out, "%i %i\r%i\r", w, h, c);
	
	if (*argv[1] == 'C')
	{
		if (magic == 6)
		{
			unsigned char r, g, b;
			if(fscanf (in, "%c%c%c", &r, &g, &b) < 3)
			{
				return 0;
			}
			while (1)
			{
				tmp.r = r;
				tmp.g = g;
				tmp.b = b;
				if(fscanf (in, "%c%c%c", &r, &g, &b) < 3)
				{
					fprintf (out, "%c%c%c%c", count, tmp.r, tmp.g, tmp.b);
					break;
				}
				else
				{
					if(tmp.r == r && tmp.g == g && tmp.b == b && count < 255)
					{
						count++;
					}
					else
					{
						fprintf (out, "%c%c%c%c", count, tmp.r, tmp.g, tmp.b);
						count = 0;
					}
				}
			}
		}
		else if (magic == 3)
		{
			unsigned int r, g, b;
			if(fscanf (in, "%i %i %i", &r, &g, &b) < 3)
			{
				return 0;
			}
			while (1)
			{
				tmp.r = r;
				tmp.g = g;
				tmp.b = b;
				if(fscanf (in, "%i %i %i", &r, &g, &b) < 3)
				{
					fprintf (out, "%c%c%c%c", count, tmp.r, tmp.g, tmp.b);
					break;
				}
				else
				{
					if(tmp.r == r && tmp.g == g && tmp.b == b && count < 255)
					{
						count++;
					}
					else
					{
						fprintf (out, "%c%c%c%c", count, tmp.r, tmp.g, tmp.b);
						count = 0;
					}
				}
			}
		}
	}
	else if (*argv[1] == 'D')
	{
		unsigned char r, g, b;
		if (magic == 6)
		{
			while (1)
			{
				if(fscanf (in, "%c%c%c%c", &q, &r, &g, &b) < 4)
				{
					fclose(in);
					fclose(out);
					return 0;
				}
				for(int i = 0; i <= q; i++)
				{
					fprintf (out, "%c%c%c", r, g, b);
				}
			}
		}
		else if (magic == 3)
		{
			int c = 0;
			while (1)
			{
				if(fscanf (in, "%c%c%c%c", &q, &r, &g, &b) < 4)
				{
					fclose(in);
					fclose(out);
					return 0;
				}
				for(int i = 0; i <= q; i++)
				{
					fprintf (out, "%i %i %i ", r, g, b);
					c++;
					if (c % w == 0) fprintf (out, "\r");
				}
			}
		}
	}
	else
	{
		printf ("Argumento inválido '%s'\r", argv[1]);
		return -1;
	}
	fclose (in);
	fclose (out);
	return 0;
}
