#include "dependencies.h"

int image (PPM * bitmap, int width, int height)
{
	if (width < 1 || height < 1)
		return ex_InvArg;
	FREE (bitmap);
	bitmap->width = width;
	bitmap->height = height;
	bitmap->color = (RGB **) calloc (height, sizeof (RGB *) );
	if (bitmap->color == NULL)
		return ex_MemInsuf;
	for (int i = 0; i < height; i++)
	{
		bitmap->color[i] = (RGB *) calloc (width, sizeof (RGB) );
		if (bitmap->color[i] == NULL)
			return ex_MemInsuf;
	}
	return success;
}

int color (PENC * pincel, RGB newcolor)
{
	pincel->color = newcolor;
	return success;
}

int clear (PPM * bitmap, RGB newcolor)
{
	if (bitmap->color == NULL)
		return ex_ImgInit;
	for (int i = 0; i < bitmap->height; i++)
	{
		for (int j = 0; j < bitmap->width; j++)
		{
			bitmap->color[i][j] = newcolor;
		}
	}
	return success;
}

int line (PPM * bitmap, PENC pincel, COORD P1, COORD P2)
{
	if (bitmap->color == NULL)
		return ex_ImgInit;
	double x = P1.x, y = P1.y, deltax, deltay, passox, passoy;
	deltax = P2.x - P1.x;
	deltay = P2.y - P1.y;
	if (deltax == 0 && deltay == 0)
	{
		if (x >= 0 && y >= 0 && x < bitmap->height && y < bitmap->width)
		{
			draw (bitmap, pincel, x, y);
			return success;
		}
	}
	if (deltax == 0)
	{
		passox = 0;
		passoy = 1;
	}
	else
	{
		if (deltay != 0)
		{
			passoy = deltay / deltax;
		}
	}
	if (deltay == 0)
	{
		passox = 1;
		passoy = 0;
	}
	else
	{
		if (deltax != 0)
		{
			passox = deltax / deltay;
		}
	}
	if (passox > 0 || passoy > 0)
	{
		if (passox > passoy)
		{
			passox = 1;
		}
		else
		{
			passoy = 1;
		}
	}
	else
	{
		if (passox < passoy)
		{
			passox = 1;
		}
		else
		{
			passoy = 1;
		}
	}
	if ( (deltax < 0 && passox > 0) || (deltax > 0 && passox < 0) )
	{
		passox *= - 1;
	}
	if ( (deltay < 0 && passoy > 0) || (deltay > 0 && passoy < 0) )
	{
		passoy *= - 1;
	}
	int ix, iy;
	do
	{
		ix = (int) round (x);
		iy = (int) round (y);
		draw (bitmap, pincel, ix, iy);
		x += passox;
		y += passoy;
	}while ( (ix != P2.x || iy != P2.y) || (deltay == 0 && ix != P2.x) || (deltax == 0 && iy != P2.y) );
	return success;
}

int polygon (PPM * bitmap, PENC pincel, int lados, COORD * pontos)
{
	if (bitmap->color == NULL)
		return ex_ImgInit;
	for (int i = 1; i < lados; i++)
	{
		line (bitmap, pincel, pontos[i - 1], pontos[i]);
	}
	line (bitmap, pincel, pontos[lados - 1], pontos[0]);
	return success;
}

int rect (PPM * bitmap, PENC pincel, COORD pos, int width, int height)
{
	if (bitmap->color == NULL)
		return ex_ImgInit;
	COORD pontos[4] = {{pos.x - (height / 2) , pos.y - (width / 2) }, {pos.x - (height / 2) , pos.y + (width / 2) }, {pos.x + (height / 2) , pos.y + (width / 2) }, {pos.x + (height / 2) , pos.y - (width / 2) }};
	polygon (bitmap, pincel, 4, pontos);
	return success;
}

int circle (PPM * bitmap, PENC pincel, COORD pos, int raio, int p)
{
	if (bitmap->color == NULL)
		return ex_ImgInit;
	if (raio < 1)
		return ex_InvArg;
	for (int i = pos.x - raio; i <= pos.x + raio; i++)
	{
		for (int j = pos.y - raio; j <= pos.y + raio; j++)
		{
			if (p == 0)
			{
				if (round (sqrt (pow (i - pos.x, 2) + pow (j - pos.y, 2) ) ) == raio)
				{
					draw (bitmap, pincel, i, j);
				}
			}
			else
			{
				if (round (sqrt (pow (i - pos.x, 2) + pow (j - pos.y, 2) ) ) <= raio)
				{
					draw (bitmap, pincel, i, j);
				}
			}
		}
	}
	return success;
}

int fill (PPM * bitmap, PENC pincel, COORD pos)
{
	if (bitmap->color == NULL)
		return ex_ImgInit;
	if (pos.x >= 0 && pos.y >= 0 && pos.x < bitmap->height && pos.y < bitmap->width)
	{
		RGB cor = bitmap->color[pos.x][pos.y];
		COORD * map = NULL;
		int current_x, current_y, cont = 1;
		map = (COORD *) calloc (bitmap->height * bitmap->width, sizeof (COORD) );
		if (map == NULL)
			return ex_MemInsuf;
		map[0] = POINT (pos.x, pos.y);
		bitmap->color[map[0].x][map[0].y] = pincel.color;
		for (int pixel = 0; pixel < cont; pixel++)
		{
			current_x = map[pixel].x;
			current_y = map[pixel].y;

			if (current_x - 1 >= 0 && current_y >= 0 && current_x - 1 < bitmap->height && current_y < bitmap->width)
			{
				if (rgbcmp (bitmap->color[current_x - 1][current_y], cor) == 0 && rgbcmp (bitmap->color[current_x - 1][current_y], pincel.color) == 1)
				{
					map[cont] = POINT (current_x - 1, current_y);
					bitmap->color[current_x - 1][current_y] = pincel.color;
					cont++;
				}
			}
			if (current_x + 1 >= 0 && current_y >= 0 && current_x + 1 < bitmap->height && current_y < bitmap->width)
			{
				if (rgbcmp (bitmap->color[current_x + 1][current_y], cor) == 0 && rgbcmp (bitmap->color[current_x + 1][current_y], pincel.color) == 1)
				{
					map[cont] = POINT (current_x + 1, current_y);
					bitmap->color[current_x + 1][current_y] = pincel.color;
					cont++;
				}
			}
			if (current_x >= 0 && current_y - 1 >= 0 && current_x < bitmap->height && current_y - 1 < bitmap->width)
			{
				if (rgbcmp (bitmap->color[current_x][current_y - 1], cor) == 0 && rgbcmp (bitmap->color[current_x][current_y - 1], pincel.color) == 1)
				{
					map[cont] = POINT (current_x, current_y - 1);
					bitmap->color[current_x][current_y - 1] = pincel.color;
					cont++;
				}
			}
			if (current_x >= 0 && current_y + 1 >= 0 && current_x < bitmap->height && current_y + 1 < bitmap->width)
			{
				if (rgbcmp (bitmap->color[current_x][current_y + 1], cor) == 0 && rgbcmp (bitmap->color[current_x][current_y + 1], pincel.color) == 1)
				{
					map[cont] = POINT (current_x, current_y + 1);
					bitmap->color[current_x][current_y + 1] = pincel.color;
					cont++;
				}
			}
		}
		free (map);
	}
	return success;
}

int save (PPM * bitmap, int magic, char * arquivo)
{
	if (bitmap->color == NULL)
		return ex_ImgInit;
	if (magic == 6)
	{
		FILE * save = fopen (arquivo, "w");
		fprintf (save, "P6\r");
		fprintf (save, "%i %i\r", bitmap->width, bitmap->height);
		fprintf (save, "255\r");
		for (int i = 0; i < bitmap->height; i++)
		{
			for (int j = 0; j < bitmap->width; j++)
			{
				fprintf (save, "%c%c%c", bitmap->color[i][j].r, bitmap->color[i][j].g, bitmap->color[i][j].b);
			}
		}
		fclose (save);
	}
	else if (magic == 3)
	{
		FILE * save = fopen (arquivo, "w");
		fprintf (save, "P3\r");
		fprintf (save, "%i %i\r", bitmap->width, bitmap->height);
		fprintf (save, "255\r");
		for (int i = 0; i < bitmap->height; i++)
		{
			for (int j = 0; j < bitmap->width; j++)
			{
				fprintf (save, "%03i %03i %03i\r", bitmap->color[i][j].r, bitmap->color[i][j].g, bitmap->color[i][j].b);
			}
		}
		fclose (save);
	}
	else
	{
		return ex_InvFormat;
	}
	return success;
}

int open (PPM * bitmap, char * arquivo)
{
	FILE * open = fopen (arquivo, "r");
	int colors, magic;
	char P;

	if (open == NULL)
		return ex_ArcNonex;

	if (fscanf (open, "%c%i", &P, &magic) != 2 || P != 'P')
	{
		fclose (open);
		return ex_InvFormat;
	}

	if (fscanf (open, "%i %i", &bitmap->width, &bitmap->height) < 2)
	{
		fclose (open);
		return ex_InvFormat;
	}

	if(fscanf (open, "%i\r", &colors) < 1)
	{
		fclose (open);
		return ex_InvFormat;
	}
	if (colors != 255)
	{
		fclose (open);
		return ex_Non24Bit;
	}
	printf ("%c%i, %i x %i\n", P, magic, bitmap->width, bitmap->height);
	image (bitmap, bitmap->width, bitmap->height);
	if (magic == 3)
	{
		for (int i = 0; i < bitmap->height; i++)
		{
			for (int j = 0; j < bitmap->width; j++)
			{
				short r = 0, g = 0, b = 0;
				if (fscanf (open, "%hd%hd%hd",  &r, &g, &b) < 3)
				{
					fclose (open);
					return wa_MisPixels;
				}
				bitmap->color[i][j] = COLOR (r, g, b);
			}
		}
		fclose (open);
	}
	else if (magic == 6)
	{
		for (int i = 0; i < bitmap->height; i++)
		{
			for (int j = 0; j < bitmap->width; j++)
			{
				unsigned char r, g, b;
				if (fscanf (open, "%c%c%c", &r, &g, &b) < 3)
				{
					fclose (open);
					return wa_MisPixels;
				}
				bitmap->color[i][j] = COLOR (r, g, b);
			}
		}
		fclose (open);
	}
	else
	{
		fclose (open);
		return ex_InvFormat;
	}
	return success;
}


