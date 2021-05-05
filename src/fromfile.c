#include "dependencies.h"

int fromfile (char * in)
{
	PPM current_image = IMAGE (0, 0, NULL);
	PENC pincel = {COLOR (0, 0, 0), 1};
	char comando[64];
	int erro, lin = 1, pchar;
	FILE * head = fopen (in, "r");

	while (1) 
	{
		erro = 0;
		pchar = fgetc (head);
		if (pchar == '\n')
		{
			lin++;
			continue;
		}
		else
		{
			ungetc (pchar, head);
		}

		if (fscanf (head, "%s", comando) == EOF) break;

		if (cstrcmp (comando, "image") == 0)
		{
			int largura, altura;
			if (fscanf (head, "%i %i", &largura, &altura) < 2)
			{
				erro = ex_InvSintax;
			}
			else
			{
				erro = image (&current_image, largura, altura);
			}
		}
		else if (cstrcmp (comando, "color") == 0)
		{
			int r, g, b;
			if (fscanf (head, "%i %i %i", &r, &g, &b) < 3)
			{
				erro = ex_InvSintax;
			}
			else
			{
				erro = color (&pincel, COLOR (r, g, b));
			}
		}
		else if (cstrcmp (comando, "size") == 0)
		{
			int tamanho;
			if (fscanf (head, "%i", &tamanho) < 1)
			{
				erro = ex_InvSintax;
			}
			else
			{
				erro = size (&pincel, tamanho);
			}
		}
		else if (cstrcmp (comando, "guev") == 0)
		{
			double escala;
			if (fscanf (head, "%lf", &escala) < 1)
			{
				erro = ex_InvSintax;
			}
			else
			{
				erro = guev (&current_image, escala);
			}
		}
		else if (cstrcmp (comando, "clear") == 0)
		{
			int r, g, b;
			if (fscanf (head, "%i %i %i", &r, &g, &b) < 3)
			{
				erro = ex_InvSintax;
			}
			else
			{
				erro = clear (&current_image, COLOR (r, g, b));
			}
		}
		else if (cstrcmp (comando, "global") == 0)
		{
			int x, y;
			if (fscanf (head, "%i %i", &x, &y) < 2)
			{
				erro = ex_InvSintax;
			}
			else
			{
				erro = global (&current_image, pincel, POINT (x, y));
			}
		}
		else if (cstrcmp (comando, "line") == 0)
		{
			COORD inicio, fim;
			if (fscanf (head, "%i %i %i %i", &inicio.x, &inicio.y, &fim.x, &fim.y) < 4)
			{
				erro = ex_InvSintax;
			}
			else
			{
				erro = line (&current_image, pincel, inicio, fim);
			}
		}
		else if (cstrcmp (comando, "polygon") == 0)
		{
			int lados;
			COORD * pontos;
			if (fscanf (head, "%i", &lados) < 1)
			{
				erro = ex_InvSintax;
			}
			pontos = (COORD*) calloc (lados, sizeof (COORD) );
			for (int i = 0; i < lados; i++)
			{
				if (fscanf (head, "%i %i", &pontos[i].x, &pontos[i].y) < 2)
				{
					free (pontos);
					erro = ex_InvSintax;
					break;
				}
			}
			if (erro == success) erro = polygon (&current_image, pincel, lados, pontos);
			free (pontos);
		}
		else if (cstrcmp (comando, "rect") == 0)
		{
			int largura, altura, x, y;
			if (fscanf (head, "%i %i %i %i", &x, &y, &largura, &altura) < 4)
			{
				erro = ex_InvSintax;
			}
			else
			{
				erro = rect (&current_image, pincel, POINT (x, y), largura, altura);
			}
		}
		else if (cstrcmp (comando, "circle") == 0)
		{
			int raio, p, x, y;
			if (fscanf (head, "%i %i %i %i", &x, &y, &raio, &p) < 4)
			{
				erro = ex_InvSintax;
			}
			else
			{
				erro = circle (&current_image, pincel, POINT (x, y), raio, p);
			}
		}
		else if (cstrcmp (comando, "fill") == 0)
		{
			int x, y;
			if (fscanf (head, "%i %i", &x, &y) < 2)
			{
				erro = ex_InvSintax;
			}
			else
			{
				erro = fill (&current_image, pincel, POINT (x, y));
			}
		}
		else if (cstrcmp (comando, "save") == 0)
		{
			int tipo = 6;
			char arquivo[64];
			if (fscanf (head, "%i", &tipo) < 1)
			{
				erro = ex_InvSintax;
			}
			else
			{
				fscanf (head, " %[^\n]", arquivo);
				erro = save (&current_image, tipo, arquivo);
			}
		}
		else if (cstrcmp (comando, "fromfile") == 0)
		{
			char in[64];
			if (fscanf (head, " %[^\n]", in) < 1)
			{
				erro = ex_InvSintax;
			}
			else
			{
				fromfile(in);
			}
		}
		else if (cstrcmp (comando, "open") == 0)
		{
			char arquivo[64];
			fscanf (head, " %[^\n]", arquivo);
			erro = open (&current_image, arquivo);
		}
		else if (cstrcmp (comando, "comp") == 0)
		{
			char fin[64], fout[64];
			fscanf (head, "%s %s", fin, fout);
			erro = comp (fin, fout);
		}
		else if (cstrcmp (comando, "scolor") == 0)
		{
			char cor[32];
			fscanf (head, "%s", cor);
			erro = scolor (&pincel, cor);
		}
		else if (cstrcmp (comando, "sclear") == 0)
		{
			char cor[32];
			fscanf (head, "%s", cor);
			erro = sclear (&current_image, cor);
		}
		else if (cstrcmp (comando, "rotate") == 0)
		{
			erro = rotate (&current_image);
		}
		else if (cstrcmp (comando, "invert") == 0)
		{
			erro = invert (&current_image);
		}
		else if (cstrcmp (comando, "grayscale") == 0)
		{
			erro = grayscale (&current_image);
		}
		else if (cstrcmp (comando, "sepia") == 0)
		{
			erro = sepia (&current_image);
		}
		else if (cstrcmp (comando, "negative") == 0)
		{
			erro = negative (&current_image);
		}
		else if (cstrcmp (comando, "glitch") == 0)
		{
			int deslocamento;
			double angulo;
			if (fscanf (head, "%i %lf", &deslocamento, &angulo) < 2)
			{
				erro = ex_InvSintax;
			}
			else
			{
				erro = glitch (&current_image, deslocamento, angulo);
			}
		}
		else if (cstrcmp (comando, "rbglitch") == 0)
		{
			int deslocamento;
			double angulo;
			if (fscanf (head, "%i %lf", &deslocamento, &angulo) < 2)
			{
				erro = ex_InvSintax;
			}
			else
			{
				erro = rbglitch (&current_image, deslocamento, angulo);
			}
		}
		else if (cstrcmp (comando, "pixelize") == 0)
		{
			int pixels;
			if (fscanf (head, "%i", &pixels) < 1)
			{
				erro = ex_InvSintax;
			}
			else
			{
				erro = pixelize (&current_image, pixels);
			}
		}
		else if (cstrcmp (comando, "darken") == 0)
		{
			double porcentagem;
			if (fscanf (head, "%lf", &porcentagem) < 1)
			{
				erro = ex_InvSintax;
			}
			else
			{
				erro = darken (&current_image, porcentagem);
			}
		}
		else if (cstrcmp (comando, "brighten") == 0)
		{
			double porcentagem;
			if (fscanf (head, "%lf", &porcentagem) < 1)
			{
				erro = ex_InvSintax;
			}
			else
			{
				erro = brighten (&current_image, porcentagem);
			}
		}
		else if (cstrcmp (comando, "vibrancy") == 0)
		{
			double porcentagem;
			if (fscanf (head, "%lf", &porcentagem) < 1)
			{
				erro = ex_InvSintax;
			}
			else
			{
				erro = vibrancy (&current_image, porcentagem);
			}
		}
		else if (cstrcmp (comando, "intensity") == 0)
		{
			double vermelho, verde, azul;
			if (fscanf (head, "%lf %lf %lf", &vermelho, &verde, &azul) < 3)
			{
				erro = ex_InvSintax;
			}
			else
			{
				erro = intensity (&current_image, vermelho, verde, azul);
			}
		}
		else if (cstrcmp (comando, "redequal") == 0)
		{
			double vermelho, verde, azul;
			if (fscanf (head, "%lf %lf %lf", &vermelho, &verde, &azul) < 3)
			{
				erro = ex_InvSintax;
			}
			else
			{
				erro = redequal (&current_image, vermelho, verde, azul);
			}
		}
		else if (cstrcmp (comando, "greenequal") == 0)
		{
			double vermelho, verde, azul;
			if (fscanf (head, "%lf %lf %lf", &vermelho, &verde, &azul) < 3)
			{
				erro = ex_InvSintax;
			}
			else
			{
				erro = greenequal (&current_image, vermelho, verde, azul);
			}
		}
		else if (cstrcmp (comando, "blueequal") == 0)
		{
			double vermelho, verde, azul;
			if (fscanf (head, "%lf %lf %lf", &vermelho, &verde, &azul) < 3)
			{
				erro = ex_InvSintax;
			}
			else
			{
				erro = blueequal (&current_image, vermelho, verde, azul);
			}
		}
		else if (cstrcmp (comando, "desaturate") == 0)
		{
			double vermelho, verde, azul;
			if (fscanf (head, "%lf %lf %lf", &vermelho, &verde, &azul) < 3)
			{
				erro = ex_InvSintax;
			}
			else
			{
				erro = desaturate (&current_image, vermelho, verde, azul);
			}
		}
		else if (cstrcmp (comando, "curve") == 0)
		{
			int ordem;
			COORD * pontos;
			if (fscanf (head, "%i", &ordem) < 1)
			{
				erro = ex_InvSintax;
			}
			pontos = (COORD*) calloc (ordem, sizeof (COORD) );
			for (int i = 0; i < ordem; i++)
			{
				if (fscanf (head, "%i %i", &pontos[i].x, &pontos[i].y) < 2)
				{
					free (pontos);
					erro = ex_InvSintax;
					break;
				}
			}
			if (erro == success) erro = curve (&current_image, pincel, ordem, pontos);
			free (pontos);
		}
		else if (cstrcmp (comando, "elipse") == 0)
		{
			int largura, altura, x, y, p;
			double angulo;
			if (fscanf (head, "%i %i %i %i %lf %i", &x, &y, &largura, &altura, &angulo, &p) < 6)
			{
				erro = ex_InvSintax;
			}
			if (erro == success) erro = elipse (&current_image, pincel, POINT (x, y), largura, altura, angulo, p);
		}
		else
		{
			erro = ex_NotFound;
		}
		if (erro != success)
		{
			printf ("%s:%i: %s: ", in, lin, comando);
			if (erro == ex_MemInsuf)
			{
				printf ("Memória insuficiente.\n");
			}
			else if (erro == ex_ImgInit)
			{
				printf ("Nenhuma imagem foi inicializada.\n");
			}
			else if (erro == ex_ArcNonex)
			{
				printf ("Arquivo inexistente.\n");
			}
			else if (erro == ex_InvFormat)
			{
				printf ("Formato de arquivo inválido.\n");
			}
			else if (erro == ex_Non24Bit)
			{
				printf ("O arquivo não corresponde a uma imagem de 24 bits.\n");
			}
			else if (erro == ex_InvSintax)
			{
				printf ("Sintaxe do comando incorreta. Consulte \"help\".\n");
			}
			else if (erro == ex_InvArg)
			{
				printf ("Argumento inválido.\n");
			}
			else if (erro == ex_CNotFound)
			{
				printf ("Cor não encontrada, digite \"listcolor\" para ver a lista de cores.\n");
			}
			else if (erro == ex_NotFound)
			{
				printf ("Comando não encontrado, digite \"help\" para ver lista de comandos\n");
			}
			else
			{
				printf ("Erro desconhecido (%i)\n", erro);
			}
		}
		else
		{
			rectfy (&current_image);
		}
	}
	FREE (&current_image);
	return success;
}
