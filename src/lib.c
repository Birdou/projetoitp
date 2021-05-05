#include "dependencies.h"

RGB COLOR (int r, int g, int b)
{
	RGB color = {r, g, b};
	return color;
}

PPM IMAGE (int width, int height, RGB ** color)
{
	PPM image = {width, height, color};
	return image;
}

COORD POINT (int x, int y)
{
	COORD point = {x, y};
	return point;
}

RGB RGBPI_SUM (RGB color, double num)
{
	return COLOR (color.r + num, color.g + num, color.b + num);
}

RGB RGBPI_DIFFERENCE (RGB color, double num)
{
	return COLOR (color.r - num, color.g - num, color.b - num);
}

RGB RGBPI_PRODUCT (RGB color, double num)
{
	return COLOR (color.r * num, color.g * num, color.b * num);
}

RGB RGBPI_DIVIDE (RGB color, double num)
{
	return COLOR (color.r / num, color.g / num, color.b / num);
}

RGB RGBPC_SUM (RGB color1, RGB color2)
{
	return COLOR (color1.r + color2.r, color1.g + color2.g, color1.b + color2.b);
}

RGB RGBPC_DIFFERENCE (RGB color1, RGB color2)
{
	return COLOR (color1.r - color2.r, color1.g - color2.g, color1.b - color2.b);
}

RGB RGBPC_PRODUCT (RGB color1, RGB color2)
{
	return COLOR (color1.r * color2.r, color1.g * color2.g, color1.b * color2.b);
}

RGB RGBPC_DIVIDE (RGB color1, RGB color2)
{
	return COLOR (color1.r / color2.r, color1.g / color2.g, color1.b / color2.b);
}

RGB rgbmix (RGB color1, RGB color2)
{
	return RGBPI_DIVIDE (RGBPC_SUM (color1, color2), 2);
}

int clone (PPM * image1, PPM * image2) 
{
	int erro;
	erro = image (image2, image1->width, image1->height);
	if (erro != success)
		return erro;
	for (int i = 0; i < image2->height; i++) 
	{
		for (int j = 0; j < image2->width; j++) 
		{
			image2->color[i][j] = image1->color[i][j];
		}
	}
	return erro;
}

int rgbcmp (RGB color1, RGB color2)
{
	if (color1.r == color2.r && color1.g == color2.g && color1.b == color2.b)
	{
		return 0;
	}
	return 1;
}

int ppmcmp (PPM * image1, PPM * image2)
{
	if (image1->height != image2->height || image1->width != image2->width)
		return 1;
	for (int i = 0; i < image1->height; i++)
	{
		for (int j = 0; j < image1->width; j++)
		{
			if (rgbcmp (image1->color[i][j], image2->color[i][j]))
				return 1;
		}
	}
	return 0;
}

void draw (PPM * image, PENC pincel, int PX, int PY)
{
	double area = (pincel.size - 1) / 2;
	for (int i = PX - area; i <= PX + area; i++)
	{
		for (int j = PY - area; j <= PY + area; j++)
		{
			if (i < 0 || j < 0 || i >= image->height || j >= image->width || rgbcmp (image->color[i][j], pincel.color) == 0)
			{
				continue;
			}
			else
			{
				if (i == PX && j == PY)
				{
					image->color[i][j] = pincel.color;
				}
				else
				{
					image->color[i][j] = rgbmix (pincel.color, image->color[i][j]);
				}
			}
		}
	}
}

long int fat (int num)
{
	if (num == 0)
	{
		return 1;
	}
	for (long int i = num - 1; i > 0; i--)
	{
		num *= i;
	}
	return num;
}

long int bin (int n, int i)
{
	return fat (n) / (fat (i) * fat (n - i) );
}

double rad (double deg)
{
	return deg * M_PI / 180;
}

int cstrcmp (char * string1, char * string2)
{
	if (*string1 == '\0' && *string2 == '\0')
	{
    	return 0;
    }
    else
    {
		if( (*string1 != '\0' && *string2 != '\0') && *string1 == *string2)
		{
		    return cstrcmp (string1 + 1, string2 + 1);
		}
		else
		{
			if(abs (*string1 - *string2) == 32)
			{
				return cstrcmp (string1 + 1, string2 + 1);
			}
			else
			{
				return *string1 - *string2;
			}
		}
	}
}

void ffBuffer ()
{
	int input;
	while ( (input = getchar () ) != EOF && input != '\n');
}

void FREE (PPM * image)
{
	if (image->color == NULL)
		return;
	for (int i = 0; i < image->height; i++)
	{
		if (image->color[i] == NULL)
			return;
		free (image->color[i]);
	}
	free (image->color);
	*image = IMAGE (0, 0, NULL);
}

RGB bw (RGB color) 
{
	RGB grayscale;
	grayscale.r = (0.3 * color.r) + (0.59 * color.g) + (0.11 * color.b);
	grayscale.g = (0.3 * color.r) + (0.59 * color.g) + (0.11 * color.b);
	grayscale.b = (0.3 * color.r) + (0.59 * color.g) + (0.11 * color.b);
	return grayscale;
}

RGB antigue (RGB color) 
{
	RGB sepia;
	sepia.r = (0.393 * color.r) + (0.769 * color.g) + (0.189 * color.b);
	sepia.g = (0.349 * color.r) + (0.686 * color.g) + (0.168 * color.b);
	sepia.b = (0.272 * color.r) + (0.534 * color.g) + (0.131 * color.b);
	return sepia;
}

void rectfy (PPM * image)
{
	for (int i = 0; i < image->height; i++)
	{
		for (int j = 0; j < image->width; j++)
		{
			image->color[i][j].r = image->color[i][j].r <= 255 ? image->color[i][j].r : 255;
			image->color[i][j].g = image->color[i][j].g <= 255 ? image->color[i][j].g : 255;
			image->color[i][j].b = image->color[i][j].b <= 255 ? image->color[i][j].b : 255;
			image->color[i][j].r = image->color[i][j].r >= 0 ? image->color[i][j].r : 0;
			image->color[i][j].g = image->color[i][j].g >= 0 ? image->color[i][j].g : 0;
			image->color[i][j].b = image->color[i][j].b >= 0 ? image->color[i][j].b : 0;
		}
	}
}

int getrgbval (char * ref, RGB * color)
{
	RGB rgb = *color;
	if (cstrcmp ("Black", ref) == 0) { rgb = COLOR (0, 0, 0); }
	else if (cstrcmp ("White", ref) == 0) { rgb = COLOR (255, 255, 255); }
	else if (cstrcmp ("grey11", ref) == 0) { rgb = COLOR (28, 28, 28); }
	else if (cstrcmp ("grey21", ref) == 0) { rgb = COLOR (54, 54, 54); }
	else if (cstrcmp ("grey31", ref) == 0) { rgb = COLOR (79, 79, 79); }
	else if (cstrcmp ("DimGray", ref) == 0) { rgb = COLOR (105, 105, 105); }
	else if (cstrcmp ("Gray", ref) == 0) { rgb = COLOR (128, 128, 128); }
	else if (cstrcmp ("DarkGray", ref) == 0) { rgb = COLOR (169, 169, 169); }
	else if (cstrcmp ("Silver", ref) == 0) { rgb = COLOR (192, 192, 192); }
	else if (cstrcmp ("LightGrey", ref) == 0) { rgb = COLOR (211, 211, 211); }
	else if (cstrcmp ("Gainsboro", ref) == 0) { rgb = COLOR (220, 220, 220); }
	else if (cstrcmp ("SlateBlue", ref) == 0) { rgb = COLOR (106, 90, 205); }
	else if (cstrcmp ("SlateBlue1", ref) == 0) { rgb = COLOR (131, 111, 255); }
	else if (cstrcmp ("SlateBlue3", ref) == 0) { rgb = COLOR (105, 89, 205); }
	else if (cstrcmp ("DarkSlateBlue", ref) == 0) { rgb = COLOR (72, 61, 139); }
	else if (cstrcmp ("MidnightBlue", ref) == 0) { rgb = COLOR (25, 25, 112); }
	else if (cstrcmp ("Navy", ref) == 0) { rgb = COLOR (0, 0, 128); }
	else if (cstrcmp ("DarkBlue", ref) == 0) { rgb = COLOR (0, 0, 139); }
	else if (cstrcmp ("MediumBlue", ref) == 0) { rgb = COLOR (0, 0, 205); }
	else if (cstrcmp ("Blue", ref) == 0) { rgb = COLOR (0, 0, 255); }
	else if (cstrcmp ("refnflowerBlue", ref) == 0) { rgb = COLOR (100, 149, 237); }
	else if (cstrcmp ("RoyalBlue", ref) == 0) { rgb = COLOR (65, 105, 225); }
	else if (cstrcmp ("DodgerBlue", ref) == 0) { rgb = COLOR (30, 144, 255); }
	else if (cstrcmp ("DeepSkyBlue", ref) == 0) { rgb = COLOR (0, 191, 255); }
	else if (cstrcmp ("LightSkyBlue", ref) == 0) { rgb = COLOR (135, 206, 250); }
	else if (cstrcmp ("SkyBlue", ref) == 0) { rgb = COLOR (135, 206, 235); }
	else if (cstrcmp ("LightBlue", ref) == 0) { rgb = COLOR (173, 216, 230); }
	else if (cstrcmp ("SteelBlue", ref) == 0) { rgb = COLOR (70, 130, 180); }
	else if (cstrcmp ("LightSteelBlue", ref) == 0) { rgb = COLOR (176, 196, 222); }
	else if (cstrcmp ("SlateGray", ref) == 0) { rgb = COLOR (112, 128, 144); }
	else if (cstrcmp ("LightSlateGray", ref) == 0) { rgb = COLOR (119, 136, 153); }
	else if (cstrcmp ("Aqua", ref) == 0) { rgb = COLOR (0, 255, 255); }
	else if (cstrcmp ("Cyan", ref) == 0) { rgb = COLOR (0, 255, 255); }
	else if (cstrcmp ("DarkTurquoise", ref) == 0) { rgb = COLOR (0, 206, 209); }
	else if (cstrcmp ("Turquoise", ref) == 0) { rgb = COLOR (64, 224, 208); }
	else if (cstrcmp ("MediumTurquoise", ref) == 0) { rgb = COLOR (72, 209, 204); }
	else if (cstrcmp ("LightSeaGreen", ref) == 0) { rgb = COLOR (32, 178, 170); }
	else if (cstrcmp ("DarkCyan", ref) == 0) { rgb = COLOR (0, 139, 139); }
	else if (cstrcmp ("Teal", ref) == 0) { rgb = COLOR (0, 128, 128); }
	else if (cstrcmp ("Aquamarine", ref) == 0) { rgb = COLOR (127, 255, 212); }
	else if (cstrcmp ("MediumAquamarine", ref) == 0) { rgb = COLOR (102, 205, 170); }
	else if (cstrcmp ("CadetBlue", ref) == 0) { rgb = COLOR (95, 158, 160); }
	else if (cstrcmp ("DarkSlateGray", ref) == 0) { rgb = COLOR (47, 79, 79); }
	else if (cstrcmp ("MediumSpringGreen", ref) == 0) { rgb = COLOR (0, 250, 154); }
	else if (cstrcmp ("SpringGreen", ref) == 0) { rgb = COLOR (0, 255, 127); }
	else if (cstrcmp ("PaleGreen", ref) == 0) { rgb = COLOR (152, 251, 152); }
	else if (cstrcmp ("LightGreen", ref) == 0) { rgb = COLOR (144, 238, 144); }
	else if (cstrcmp ("DarkSeaGreen", ref) == 0) { rgb = COLOR (143, 188, 143); }
	else if (cstrcmp ("MediumSeaGreen", ref) == 0) { rgb = COLOR (60, 179, 113); }
	else if (cstrcmp ("SeaGreen", ref) == 0) { rgb = COLOR (46, 139, 87); }
	else if (cstrcmp ("DarkGreen", ref) == 0) { rgb = COLOR (0, 100, 0); }
	else if (cstrcmp ("Green", ref) == 0) { rgb = COLOR (0, 128, 0); }
	else if (cstrcmp ("ForestGreen", ref) == 0) { rgb = COLOR (34, 139, 34); }
	else if (cstrcmp ("LimeGreen", ref) == 0) { rgb = COLOR (50, 205, 50); }
	else if (cstrcmp ("Lime", ref) == 0) { rgb = COLOR (0, 255, 0); }
	else if (cstrcmp ("LawnGreen", ref) == 0) { rgb = COLOR (124, 252, 0); }
	else if (cstrcmp ("Chartreuse", ref) == 0) { rgb = COLOR (127, 255, 0); }
	else if (cstrcmp ("GreenYellow", ref) == 0) { rgb = COLOR (173, 255, 47); }
	else if (cstrcmp ("YellowGreen", ref) == 0) { rgb = COLOR (154, 205, 50); }
	else if (cstrcmp ("OliveDrab", ref) == 0) { rgb = COLOR (107, 142, 35); }
	else if (cstrcmp ("DarkOliveGreen", ref) == 0) { rgb = COLOR (85, 107, 47); }
	else if (cstrcmp ("Olive", ref) == 0) { rgb = COLOR (128, 128, 0); }
	else if (cstrcmp ("DarkKhaki", ref) == 0) { rgb = COLOR (189, 83, 107); }
	else if (cstrcmp ("Goldenrod", ref) == 0) { rgb = COLOR (218, 165, 32); }
	else if (cstrcmp ("DarkGoldenrod", ref) == 0) { rgb = COLOR (184, 134, 11); }
	else if (cstrcmp ("SaddleBrown", ref) == 0) { rgb = COLOR (139, 69, 19); }
	else if (cstrcmp ("Sienna", ref) == 0) { rgb = COLOR (160, 82, 45); }
	else if (cstrcmp ("RosyBrown", ref) == 0) { rgb = COLOR (188, 143, 143); }
	else if (cstrcmp ("Peru", ref) == 0) { rgb = COLOR (205, 133, 63); }
	else if (cstrcmp ("Chocolate", ref) == 0) { rgb = COLOR (210, 105, 30); }
	else if (cstrcmp ("SandyBrown", ref) == 0) { rgb = COLOR (244, 164, 96); }
	else if (cstrcmp ("NavajoWhite", ref) == 0) { rgb = COLOR (255, 222, 173); }
	else if (cstrcmp ("Wheat", ref) == 0) { rgb = COLOR (245, 222, 179); }
	else if (cstrcmp ("BurlyWood", ref) == 0) { rgb = COLOR (222, 184, 135); }
	else if (cstrcmp ("Tan", ref) == 0) { rgb = COLOR (210, 180, 140); }
	else if (cstrcmp ("MediumSlateBlue", ref) == 0) { rgb = COLOR (123, 104, 238); }
	else if (cstrcmp ("MediumPurple", ref) == 0) { rgb = COLOR (147, 112, 219); }
	else if (cstrcmp ("BlueViolet", ref) == 0) { rgb = COLOR (138, 43, 226); }
	else if (cstrcmp ("Indigo", ref) == 0) { rgb = COLOR (75, 0, 130); }
	else if (cstrcmp ("DarkViolet", ref) == 0) { rgb = COLOR (148, 0, 211); }
	else if (cstrcmp ("DarkOrchid", ref) == 0) { rgb = COLOR (153, 50, 204); }
	else if (cstrcmp ("MediumOrchid", ref) == 0) { rgb = COLOR (186, 85, 211); }
	else if (cstrcmp ("Purple", ref) == 0) { rgb = COLOR (128, 0, 128); }
	else if (cstrcmp ("DarkMagenta", ref) == 0) { rgb = COLOR (139, 0, 139); }
	else if (cstrcmp ("Fuchsia", ref) == 0) { rgb = COLOR (255, 0, 255); }
	else if (cstrcmp ("Magenta", ref) == 0) { rgb = COLOR (255, 0, 255); }
	else if (cstrcmp ("Violet", ref) == 0) { rgb = COLOR (238, 130, 238); }
	else if (cstrcmp ("Orchid", ref) == 0) { rgb = COLOR (218, 112, 214); }
	else if (cstrcmp ("Plum", ref) == 0) { rgb = COLOR (221, 160, 221); }
	else if (cstrcmp ("MediumVioletRed", ref) == 0) { rgb = COLOR (199, 21, 133); }
	else if (cstrcmp ("DeepPink", ref) == 0) { rgb = COLOR (255, 20, 147); }
	else if (cstrcmp ("HotPink", ref) == 0) { rgb = COLOR (255, 105, 180); }
	else if (cstrcmp ("PaleVioletRed", ref) == 0) { rgb = COLOR (219, 112, 147); }
	else if (cstrcmp ("LightPink", ref) == 0) { rgb = COLOR (255, 182, 193); }
	else if (cstrcmp ("Pink", ref) == 0) { rgb = COLOR (255, 192, 203); }
	else if (cstrcmp ("Lightrefal", ref) == 0) { rgb = COLOR (240, 128, 128); }
	else if (cstrcmp ("IndianRed", ref) == 0) { rgb = COLOR (205, 92, 92); }
	else if (cstrcmp ("Crimson", ref) == 0) { rgb = COLOR (220, 20, 60); }
	else if (cstrcmp ("Maroon", ref) == 0) { rgb = COLOR (128, 0, 0); }
	else if (cstrcmp ("DarkRed", ref) == 0) { rgb = COLOR (139, 0, 0); }
	else if (cstrcmp ("FireBrick", ref) == 0) { rgb = COLOR (178, 34, 34); }
	else if (cstrcmp ("Brown", ref) == 0) { rgb = COLOR (165, 42, 42); }
	else if (cstrcmp ("Salmon", ref) == 0) { rgb = COLOR (250, 128, 114); }
	else if (cstrcmp ("DarkSalmon", ref) == 0) { rgb = COLOR (233, 150, 122); }
	else if (cstrcmp ("LightSalmon", ref) == 0) { rgb = COLOR (255, 160, 122); }
	else if (cstrcmp ("refal", ref) == 0) { rgb = COLOR (255, 127, 80); }
	else if (cstrcmp ("Tomato", ref) == 0) { rgb = COLOR (255, 99, 71); }
	else if (cstrcmp ("Red", ref) == 0) { rgb = COLOR (255, 0, 0); }
	else if (cstrcmp ("OrangeRed", ref) == 0) { rgb = COLOR (255, 69, 0); }
	else if (cstrcmp ("DarkOrange", ref) == 0) { rgb = COLOR (255, 140, 0); }
	else if (cstrcmp ("Orange", ref) == 0) { rgb = COLOR (255, 165, 0); }
	else if (cstrcmp ("Gold", ref) == 0) { rgb = COLOR (255, 215, 0); }
	else if (cstrcmp ("Yellow", ref) == 0) { rgb = COLOR (255, 255, 0); }
	else if (cstrcmp ("Khaki", ref) == 0) { rgb = COLOR (240, 230, 140); }
	else if (cstrcmp ("AliceBlue", ref) == 0) { rgb = COLOR (240, 248, 255); }
	else if (cstrcmp ("GhostWhite", ref) == 0) { rgb = COLOR (248, 248, 255); }
	else if (cstrcmp ("Snow", ref) == 0) { rgb = COLOR (255, 250, 250); }
	else if (cstrcmp ("Seashell", ref) == 0) { rgb = COLOR (255, 245, 238); }
	else if (cstrcmp ("FloralWhite", ref) == 0) { rgb = COLOR (255, 250, 240); }
	else if (cstrcmp ("WhiteSmoke", ref) == 0) { rgb = COLOR (245, 245, 245); }
	else if (cstrcmp ("Beige", ref) == 0) { rgb = COLOR (245, 245, 220); }
	else if (cstrcmp ("OldLace", ref) == 0) { rgb = COLOR (253, 245, 230); }
	else if (cstrcmp ("Ivory", ref) == 0) { rgb = COLOR (255, 255, 240); }
	else if (cstrcmp ("Linen", ref) == 0) { rgb = COLOR (250, 240, 230); }
	else if (cstrcmp ("refnsilk", ref) == 0) { rgb = COLOR (255, 248, 220); }
	else if (cstrcmp ("AntiqueWhite", ref) == 0) { rgb = COLOR (250, 235, 215); }
	else if (cstrcmp ("BlanchedAlmond", ref) == 0) { rgb = COLOR (255, 235, 205); }
	else if (cstrcmp ("Bisque", ref) == 0) { rgb = COLOR (255, 228, 196); }
	else if (cstrcmp ("LightYellow", ref) == 0) { rgb = COLOR (255, 255, 224); }
	else if (cstrcmp ("LemonChiffon", ref) == 0) { rgb = COLOR (255, 250, 205); }
	else if (cstrcmp ("LightGoldenrodYellow", ref) == 0) { rgb = COLOR (250, 250, 210); }
	else if (cstrcmp ("PapayaWhip", ref) == 0) { rgb = COLOR (255, 239, 213); }
	else if (cstrcmp ("PeachPuff", ref) == 0) { rgb = COLOR (255, 218, 185); }
	else if (cstrcmp ("Moccasin", ref) == 0) { rgb = COLOR (255, 228, 181); }
	else if (cstrcmp ("PaleGoldenrod", ref) == 0) { rgb = COLOR (238, 232, 170); }
	else if (cstrcmp ("MistyRose", ref) == 0) { rgb = COLOR (255, 228, 225); }
	else if (cstrcmp ("LavenderBlush", ref) == 0) { rgb = COLOR (255, 240, 245); }
	else if (cstrcmp ("Lavender", ref) == 0) { rgb = COLOR (230, 230, 250); }
	else if (cstrcmp ("Thistle", ref) == 0) { rgb = COLOR (216, 191, 216); }
	else if (cstrcmp ("Azure", ref) == 0) { rgb = COLOR (240, 255, 255); }
	else if (cstrcmp ("LightCyan", ref) == 0) { rgb = COLOR (224, 255, 255); }
	else if (cstrcmp ("PowderBlue", ref) == 0) { rgb = COLOR (176, 224, 230); }
	else if (cstrcmp ("PaleTurquoise", ref) == 0) { rgb = COLOR (175, 238, 238); }
	else if (cstrcmp ("Honeydew", ref) == 0) { rgb = COLOR (240, 255, 240); }
	else if (cstrcmp ("MintCream", ref) == 0) { rgb = COLOR (245, 255, 250); }
	else { return ex_CNotFound; }
	*color = rgb;
	return success;
}

