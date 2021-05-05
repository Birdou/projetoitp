#include "dependencies.h"

int grayscale (PPM * bitmap) 
{
	if (bitmap->color == NULL) 
		return ex_ImgInit;
	for (int i = 0; i < bitmap->height; i++) 
	{
		for (int j = 0; j < bitmap->width; j++) 
		{
			bitmap->color[i][j] = bw (bitmap->color[i][j]);
		}
	}
	return success;
}

int sepia (PPM * bitmap) 
{
	if (bitmap->color == NULL) 
		return ex_ImgInit;
	for (int i = 0; i < bitmap->height; i++) 
	{
		for (int j = 0; j < bitmap->width; j++) 
		{
			bitmap->color[i][j] = antigue (bitmap->color[i][j]);
		}
	}
	return success;
}

int brighten (PPM * bitmap, double scale) 
{
	if (bitmap->color == NULL) 
		return ex_ImgInit;
	int value = 255 * (scale / 100);
	for (int i = 0; i < bitmap->height; i++) 
	{
		for (int j = 0; j < bitmap->width; j++) 
		{
			bitmap->color[i][j] = RGBPI_SUM (bitmap->color[i][j], value);
		}
	}
	return success;
}

int darken (PPM * bitmap, double scale) 
{
	if (bitmap->color == NULL) 
		return ex_ImgInit;
	int value = 255 * (scale / 100);
	for (int i = 0; i < bitmap->height; i++) 
	{
		for (int j = 0; j < bitmap->width; j++) 
		{
			bitmap->color[i][j] = RGBPI_DIFFERENCE (bitmap->color[i][j], value);
		}
	}
	return success;
}

int negative (PPM * bitmap) 
{
	if (bitmap->color == NULL) 
		return ex_ImgInit;
	for (int i = 0; i < bitmap->height; i++) 
	{
		for (int j = 0; j < bitmap->width; j++) 
		{
			bitmap->color[i][j] = COLOR (255 - bitmap->color[i][j].r, 255 - bitmap->color[i][j].g, 255 - bitmap->color[i][j].b);
		}
	}
	return success;
}

int intensity (PPM * bitmap, double red, double green, double blue) 
{
	if (bitmap->color == NULL) 
		return ex_ImgInit;
	for (int i = 0; i < bitmap->height; i++) 
	{
		for (int j = 0; j < bitmap->width; j++) 
		{
			bitmap->color[i][j] = RGBPC_SUM (bitmap->color[i][j], COLOR (bitmap->color[i][j].r * (red / 100), bitmap->color[i][j].g * (green / 100), bitmap->color[i][j].b * (blue / 100)));
		}
	}
	return success;
}

int redequal (PPM * bitmap, double red, double green, double blue) 
{
	if (bitmap->color == NULL) 
		return ex_ImgInit;
	for (int i = 0; i < bitmap->height; i++) 
	{
		for (int j = 0; j < bitmap->width; j++) 
		{
			bitmap->color[i][j] = RGBPC_SUM (bitmap->color[i][j], COLOR (bitmap->color[i][j].r * (red / 100), bitmap->color[i][j].r * (green / 100), bitmap->color[i][j].r * (blue / 100)));
		}
	}
	return success;
}

int greenequal (PPM * bitmap, double red, double green, double blue) 
{
	if (bitmap->color == NULL) 
		return ex_ImgInit;
	for (int i = 0; i < bitmap->height; i++) 
	{
		for (int j = 0; j < bitmap->width; j++) 
		{
			bitmap->color[i][j] = RGBPC_SUM (bitmap->color[i][j], COLOR (bitmap->color[i][j].g * (red / 100), bitmap->color[i][j].g * (green / 100), bitmap->color[i][j].g * (blue / 100)));
		}
	}
	return success;
}

int blueequal (PPM * bitmap, double red, double green, double blue) 
{
	if (bitmap->color == NULL) 
		return ex_ImgInit;
	for (int i = 0; i < bitmap->height; i++) 
	{
		for (int j = 0; j < bitmap->width; j++) 
		{
			bitmap->color[i][j] = RGBPC_SUM (bitmap->color[i][j], COLOR (bitmap->color[i][j].b * (red / 100), bitmap->color[i][j].b * (green / 100), bitmap->color[i][j].b * (blue / 100)));
		}
	}
	return success;
}

int vibrancy (PPM * bitmap, double scale) 
{
	if (bitmap->color == NULL) 
		return ex_ImgInit;
	double value = 1 + (scale / 100);
	for (int i = 0; i < bitmap->height; i++) 
	{
		for (int j = 0; j < bitmap->width; j++) 
		{
			bitmap->color[i][j] = RGBPI_PRODUCT (bitmap->color[i][j], value);
		}
	}
	return success;
}

int glitch (PPM * bitmap, int scale, double angle) 
{
	if (bitmap->color == NULL) 
		return ex_ImgInit;
	PPM prevbitmap = IMAGE (0, 0, NULL);
	clone (bitmap, &prevbitmap);
	int xr = - scale * sin (rad (angle) ) , yr = scale * cos (rad (angle) );
	for (int i = 0; i < bitmap->height; i++) 
	{
		for (int j = 0; j < bitmap->width; j++) 
		{
			COORD p, m;
			p = POINT (i + xr, j + yr);
			m = POINT (i - xr, j - yr);
			if (p.x < bitmap->height && p.y < bitmap->width && p.x >= 0 && p.y >= 0) 
			{
				bitmap->color[i][j].r = prevbitmap.color[p.x][p.y].r;
			}
			if (m.x >= 0 && m.y >= 0 && m.x < bitmap->height && m.y < bitmap->width) 
			{
				bitmap->color[i][j].b = prevbitmap.color[m.x][m.y].b;
			}
		}
	}
	FREE (&prevbitmap);
	return success;
}

int rbglitch (PPM * bitmap, int scale, double angle) 
{
	if (bitmap->color == NULL) 
		return ex_ImgInit;
	grayscale (bitmap);
	return glitch (bitmap, scale, angle);
}

int desaturate (PPM * bitmap, double r, double g, double b) 
{
	if (bitmap->color == NULL) 
		return ex_ImgInit;
	int rtol = 255 - (255 * r / 100) , gtol = 255 - (255 * g / 100) , btol = 255 - (255 * b / 100);
	for (int i = 0; i < bitmap->height; i++) 
	{
		for (int j = 0; j < bitmap->width; j++) 
		{
			if (bitmap->color[i][j].r > rtol && (bitmap->color[i][j].r >= bitmap->color[i][j].g && bitmap->color[i][j].r >= bitmap->color[i][j].b) ) 
				bitmap->color[i][j] = bw (bitmap->color[i][j]);
			if (bitmap->color[i][j].g > gtol && (bitmap->color[i][j].g >= bitmap->color[i][j].b && bitmap->color[i][j].g >= bitmap->color[i][j].r) ) 
				bitmap->color[i][j] = bw (bitmap->color[i][j]);
			if (bitmap->color[i][j].b > btol && (bitmap->color[i][j].b >= bitmap->color[i][j].r && bitmap->color[i][j].b >= bitmap->color[i][j].g) ) 
				bitmap->color[i][j] = bw (bitmap->color[i][j]);
		}
	}
	return success;

}

int pixelize (PPM * bitmap, int px)
{
	if (bitmap->color == NULL) 
		return ex_ImgInit;
	if (px < 1) 
		return ex_InvArg;

	PPM resized = IMAGE (0, 0, NULL);
	resized.width = bitmap->width % px == 0 ? bitmap->width / px : (bitmap->width / px) + 1;
	resized.height = bitmap->height % px == 0 ? bitmap->height / px : (bitmap->height / px) + 1;

	image (&resized, resized.width, resized.height);

	for(int i = 0; i < bitmap->height; i+=px)
	{
		for(int j = 0; j < bitmap->width; j+=px)
		{
			RGB color = COLOR (0, 0, 0);
			int pix = 0;
			for(int k = 0; k < px; k++)
			{
				for(int l = 0; l < px; l++)
				{
					if(k+i < bitmap->height && l+j < bitmap->width)
					{
						color = RGBPC_SUM (color, bitmap->color[k+i][l+j]);
						pix++;
					}
				}
			}
			color = RGBPI_DIVIDE (color, pix);
			resized.color[i/px][j/px] = color;
		}
	}
	clone (&resized, bitmap);
	FREE (&resized);
	return success;
}

int guev (PPM * bitmap, double scale)
{
	int lim = 255 * (scale / 100);
	for (int i = 0; i < bitmap->height; i++)
	{
		for (int j = 0; j < bitmap->width; j++)
		{
			if ( (bitmap->color[i][j].r + bitmap->color[i][j].g + bitmap->color[i][j].b) / 3 > lim)
			{
				bitmap->color[i][j] = COLOR (255, 255, 255);
			}
			else
			{
				bitmap->color[i][j] = COLOR (0, 0, 0);
			}
		}
	}
	return success;
}





