#include "dependencies.h"

int comp (char * fin, char * fout)
{
	PPM imagem = IMAGE (0, 0, NULL);
	bool isc = false;
	int magic, magicc, c, color, erro;
	FILE *in = fopen (fin, "r"), *out = fopen(fout, "w");

	if (in == NULL)
		return ex_ArcNonex;

	if (fscanf (in, "P%i", &magic) < 1)
	{
		fclose (in);
		fclose (out);
		return ex_InvFormat;
	}
	if (fscanf (in, "%i %i", &imagem.width, &imagem.height) < 2)
	{
		fclose (in);
		fclose (out);
		return ex_InvFormat;
	}
	if (fscanf (in, "%i", &color) < 1)
	{
		fclose (in);
		fclose (out);
		return ex_InvFormat;
	}
	if (fscanf (in, " -t%i\r", &magicc) == 1)
	{
		isc = true;
	}
	else
	{
		isc = false;
		//fscanf (in, "\r");
	}

	if (!isc && (magic == 3 || magic == 6))
	{
		fclose (in);

		fprintf (out, "P6\r");
		fprintf (out, "%i %i\r", imagem.width, imagem.height);
		fprintf (out, "255 -t%i\r", magic);

		erro = open (&imagem, fin);
		if (erro != 0)
			return erro;

		int tmp, rgb;

		c = 0;
		tmp = imagem.color[0][0].r;
		for (int i = 0; i < imagem.height; i++)
		{
			for (int j = 0; j < imagem.width; j++)
			{
				rgb = imagem.color[i][j].r;
				if (tmp == rgb && c < 255 && (i != imagem.height - 1 || j != imagem.width - 1))
				{
					c++;
				}
				else
				{
					fprintf (out, "%c%c", c, tmp);
					c = 1;
				}
				tmp = rgb;
			}
		}

		c = 0;
		tmp = imagem.color[0][0].g;
		for (int i = 0; i < imagem.height; i++)
		{
			for (int j = 0; j < imagem.width; j++)
			{
				rgb = imagem.color[i][j].g;
				if (tmp == rgb && c < 255 && (i != imagem.height - 1 || j != imagem.width - 1))
				{
					c++;
				}
				else
				{
					fprintf (out, "%c%c", c, tmp);
					c = 1;
				}
				tmp = rgb;
			}
		}

		c = 0;
		tmp = imagem.color[0][0].b;
		for (int i = 0; i < imagem.height; i++)
		{
			for (int j = 0; j < imagem.width; j++)
			{
				rgb = imagem.color[i][j].b;
				if (tmp == rgb && c < 255 && (i != imagem.height - 1 || j != imagem.width - 1))
				{
					c++;
				}
				else
				{
					fprintf (out, "%c%c", c, tmp);
					c = 1;
				}
				tmp = rgb;
			}
		}

		fclose (out);
	}
	else if (isc && (magicc == 3 || magicc == 6))
	{
		fclose (out);

		erro = image (&imagem, imagem.width, imagem.height);
		if (erro != 0)
			return erro;

		unsigned char cq, crgb;

		cq = '\0'; c = 0;
		for (int i = 0; i < imagem.height; i++)
		{
			for (int j = 0; j < imagem.width; j++)
			{
				if(c >= cq && (i != imagem.height - 1 || j != imagem.width - 1))
				{
					fscanf (in, "%c%c", &cq, &crgb);
					c = 0;
				}
				imagem.color[i][j].r = crgb;
				c++;
			}
		}

		cq = '\0'; c = 0;
		for (int i = 0; i < imagem.height; i++)
		{
			for (int j = 0; j < imagem.width; j++)
			{
				if(c >= cq && (i != imagem.height - 1 || j != imagem.width - 1))
				{
					fscanf (in, "%c%c", &cq, &crgb);
					c = 0;
				}
				imagem.color[i][j].g = crgb;
				c++;
			}
		}

		cq = '\0'; c = 0;
		for (int i = 0; i < imagem.height; i++)
		{
			for (int j = 0; j < imagem.width; j++)
			{
				if(c >= cq && (i != imagem.height - 1 || j != imagem.width - 1))
				{
					fscanf (in, "%c%c", &cq, &crgb);
					c = 0;
				}
				imagem.color[i][j].b = crgb;
				c++;
			}
		}

		fclose (in);

		erro = save (&imagem, magicc, fout);
		if (erro != 0)
			return erro;
	}
	else
	{
		fclose (in);
		fclose (out);
		return ex_InvFormat;
	}
	FREE (&imagem);
	return success;
}


