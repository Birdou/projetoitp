#include "dependencies.h"

int scolor (PENC * pincel, char * colorname) 
{
	return getrgbval (colorname, &pincel->color);
}

int sclear (PPM * bitmap, char * colorname) 
{
	if (bitmap->color == NULL) 
		return ex_ImgInit;
	RGB newcolor;
	if(getrgbval (colorname, &newcolor) == ex_CNotFound)
		return ex_CNotFound;
	for (int i = 0; i < bitmap->height; i++) 
	{
		for (int j = 0; j < bitmap->width; j++) 
		{
			bitmap->color[i][j] = newcolor;
		}
	}
	return success;
}

int rotate (PPM * bitmap) 
{
	if (bitmap->color == NULL) 
		return ex_ImgInit;
	PPM rotationed_bitmap = IMAGE (0, 0, NULL);
	image (&rotationed_bitmap, bitmap->height, bitmap->width);
	for (int i = 0; i < bitmap->height; i++) 
	{
		for (int j = 0; j < bitmap->width; j++) 
		{
			rotationed_bitmap.color[j][bitmap->height - i - 1] = bitmap->color[i][j];
		}
	}
	clone (&rotationed_bitmap, bitmap);
	FREE (&rotationed_bitmap);
	return success;
}

int invert (PPM * bitmap) 
{
	if (bitmap->color == NULL) 
		return ex_ImgInit;
	for (int i = 0; i < bitmap->height; i++) 
	{
		for (int j = 0; j <= (bitmap->width - 1) / 2; j++) 
		{
			RGB tmp = bitmap->color[i][j];
			bitmap->color[i][j] = bitmap->color[i][bitmap->width - j - 1];
			bitmap->color[i][bitmap->width - j - 1] = tmp;
		}
	}
	return success;
}

int curve (PPM * bitmap, PENC pincel, int ordem, COORD * pontos) 
{
	if (bitmap->color == NULL) 
		return ex_ImgInit;
	int n = ordem - 1;
	for (double t = 0; t <= 1; t += 0.0001) 
	{
		double x = 0, y = 0;
		for (int i = 0; i <= n; i++) 
		{
			x += bin (n, i) * pow (1 - t, n - i) * pow (t, i) * pontos[i].x;
			y += bin (n, i) * pow (1 - t, n - i) * pow (t, i) * pontos[i].y;
		}
		if ( (int) floor (x) < 0 || (int) floor (y) < 0 || (int) floor (x) >= bitmap->height || (int) floor (y) >= bitmap->width) continue;
		draw (bitmap, pincel, (int) x, (int) y);
	}
	return success;
}

int elipse (PPM * bitmap, PENC pincel, COORD pos, int width, int height, double angle, int p) 
{
	if (bitmap->color == NULL) 
		return ex_ImgInit;
	if (width < 1 || height < 1)
		return ex_InvArg;
	double tol = width >= height ? (width / height) * 0.00999 : (height / width) * 0.00999;
	double quadh = pow (height / 2, 2) , quadw = pow (width / 2, 2);
	for (int i = pos.x - height; i <= pos.x + height; i++) 
	{
		for (int j = pos.y - width; j <= pos.y + width; j++) 
		{
			double posx = pow (i - pos.x, 2);
			double posy = pow (j - pos.y, 2);
			double raz = (posx / quadh) + (posy / quadw);
			int x = i - pos.x, y = j - pos.y;
			int xr = (x * cos (rad (angle) ) ) - (y * sin (rad (angle) ) ), yr = (x * sin (rad (angle) ) ) + (y * cos (rad (angle) ) );
			if (p == 0)
			{
				if (raz >= 1 - tol && raz <= 1 + tol)
				{
					draw (bitmap, pincel, xr + pos.x, yr + pos.y);
				}
			}
			else
			{
				if (raz <= 1)
				{
					draw (bitmap, pincel, xr + pos.x, yr + pos.y);
				}
			}
		}
	}
	return success;
}

int undo (PPM * bitmap, PPM * prevbitmap) 
{
	int erro;
	PPM tmp = IMAGE (0, 0, NULL);
	erro = clone (bitmap, &tmp);
	if (erro != success)
	{
		FREE (&tmp);
		return erro;
	}
	erro = clone (prevbitmap, bitmap);
	if (erro != success)
	{
		FREE (&tmp);
		return erro;
	}
	erro = clone (&tmp, prevbitmap);
	if (erro != success)
	{
		FREE (&tmp);
		return erro;
	}
	FREE (&tmp);
	return success;
}

int size (PENC * pincel, int size)
{
	if (size < 1)
	{
		return ex_InvArg;
	}
	pincel->size = size;
	return success;
}

int global (PPM * bitmap, PENC pincel, COORD pos)
{
	if (bitmap->color == NULL) 
		return ex_ImgInit;
	RGB cor = bitmap->color[pos.x][pos.y];
	for (int i = 0; i < bitmap->height; i++)
	{
		for (int j = 0; j < bitmap->width; j++)
		{
			if (rgbcmp (bitmap->color[i][j], cor) == 0)
				bitmap->color[i][j] = pincel.color;
		}
	}
	return success;
}

int aim (PPM * bitmap, PENC pincel, COORD pos)
{
	PPM image = IMAGE (0, 0, NULL);
	short raio = bitmap->height >= bitmap->width ? bitmap->height : bitmap->width, erro;

	raio /= 10;

	erro = clone (bitmap, &image);
	if (erro != 0)
	{
		FREE (&image);
		return erro;
	}
	
	erro = line (&image, pincel, POINT (pos.x, 0), POINT (pos.x, image.width));
	if (erro != 0)
	{
		FREE (&image);
		return erro;
	}

	erro = line (&image, pincel, POINT (0, pos.y), POINT (image.height, pos.y));
	if (erro != 0)
	{
		FREE (&image);
		return erro;
	}

	erro = circle (&image, pincel, pos, raio, false);
	if (erro != 0)
	{
		FREE (&image);
		return erro;
	}
	image.color[pos.x][pos.y] = bitmap->color[pos.x][pos.y];
	erro = save (&image, 6, "aimview.ppm");
	FREE (&image);
	return success;
}
