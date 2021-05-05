#include "dependencies.h"

/*
	A main tem como função: interpretar os comandos pelo usuário e definir as variáveis que serão
	passadas como parâmetros; liberar a memória alocada pelas imagens; automatizar o uso do comando
	'undo'; automatizar o salvamento da prévia da imagem; disponibilizar uma "interface" ao usuário;
	interpretar o retorno das funções e reportá-las ao usuário; limpar o buffer de entrada após cada
	linha de comando.
*/
int main ()
{
	PPM current_image = IMAGE (0, 0, NULL);
	PPM previous_image = IMAGE (0, 0, NULL);
	PENC pincel = {COLOR (0, 0, 0), 1};
	char comando[64];

	printf ("Digite \"help\" para ver lista de comandos\n");
	while (1)
	{
		int erro = 0;
		printf ("> ");
		scanf ("%s", comando);

		if (cstrcmp (comando, "undo") != 0 && ppmcmp (&current_image, &previous_image) != 0)
		{
			clone (&current_image, &previous_image);
		}

		if (cstrcmp (comando, "undo") == 0)
		{
			erro = undo (&current_image, &previous_image);
		}
		else if (cstrcmp (comando, "image") == 0)
		{
			int largura, altura;
			if (scanf ("%i %i", &largura, &altura) < 2)
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
			if (scanf ("%i %i %i", &r, &g, &b) < 3)
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
			if (scanf ("%i", &tamanho) < 1)
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
			if (scanf ("%lf", &escala) < 1)
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
			if (scanf ("%i %i %i", &r, &g, &b) < 3)
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
			if (scanf ("%i %i", &x, &y) < 2)
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
			if (scanf ("%i %i %i %i", &inicio.x, &inicio.y, &fim.x, &fim.y) < 4)
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
			COORD * pontos = NULL;
			if (scanf ("%i", &lados) < 1)
			{
				erro = ex_InvSintax;
			}
			pontos = (COORD *) calloc (lados, sizeof (COORD) );
			for (int i = 0; i < lados; i++)
			{
				if (scanf ("%i %i", &pontos[i].x, &pontos[i].y) < 2)
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
			if (scanf ("%i %i %i %i", &x, &y, &largura, &altura) < 4)
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
			if (scanf ("%i %i %i %i", &x, &y, &raio, &p) < 4)
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
			if (scanf ("%i %i", &x, &y) < 2)
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
			if (scanf ("%i", &tipo) < 1)
			{
				erro = ex_InvSintax;
			}
			else
			{
				scanf (" %[^\n]", arquivo);
				erro = save (&current_image, tipo, arquivo);
			}
		}
		else if (cstrcmp (comando, "fromfile") == 0)
		{
			char in[64];
			if (scanf (" %[^\n]", in) < 1)
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
			scanf (" %[^\n]", arquivo);
			erro = open (&current_image, arquivo);
		}
		else if (cstrcmp (comando, "comp") == 0)
		{
			char fin[64], fout[64];
			scanf ("%s %s", fin, fout);
			erro = comp (fin, fout);
		}
		else if (cstrcmp (comando, "scolor") == 0)
		{
			char cor[32];
			scanf ("%s", cor);
			erro = scolor (&pincel, cor);
		}
		else if (cstrcmp (comando, "sclear") == 0)
		{
			char cor[32];
			scanf ("%s", cor);
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
			if (scanf ("%i %lf", &deslocamento, &angulo) < 2)
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
			if (scanf ("%i %lf", &deslocamento, &angulo) < 2)
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
			if (scanf ("%i", &pixels) < 1)
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
			if (scanf ("%lf", &porcentagem) < 1)
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
			if (scanf ("%lf", &porcentagem) < 1)
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
			if (scanf ("%lf", &porcentagem) < 1)
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
			if (scanf ("%lf %lf %lf", &vermelho, &verde, &azul) < 3)
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
			if (scanf ("%lf %lf %lf", &vermelho, &verde, &azul) < 3)
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
			if (scanf ("%lf %lf %lf", &vermelho, &verde, &azul) < 3)
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
			if (scanf ("%lf %lf %lf", &vermelho, &verde, &azul) < 3)
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
			if (scanf ("%lf %lf %lf", &vermelho, &verde, &azul) < 3)
			{
				erro = ex_InvSintax;
			}
			else
			{
				erro = desaturate (&current_image, vermelho, verde, azul);
			}
		}
		else if (cstrcmp (comando, "listcolor") == 0)
		{
			listcolor ();
		}
		else if (cstrcmp (comando, "curve") == 0)
		{
			int ordem;
			COORD * pontos;
			if (scanf ("%i", &ordem) < 1)
			{
				erro = ex_InvSintax;
			}
			pontos = (COORD*) calloc (ordem, sizeof (COORD) );
			for (int i = 0; i < ordem; i++)
			{
				if (scanf ("%i %i", &pontos[i].x, &pontos[i].y) < 2)
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
			if (scanf ("%i %i %i %i %lf %i", &x, &y, &largura, &altura, &angulo, &p) < 6)
			{
				erro = ex_InvSintax;
			}
			if (erro == success) erro = elipse (&current_image, pincel, POINT (x, y), largura, altura, angulo, p);
		}
		else if (cstrcmp (comando, "help") == 0)
		{
			help ();
		}
		else if (cstrcmp (comando, "purge") == 0)
		{
			CLS;
		}
		else if (cstrcmp (comando, "aim") == 0)
		{
			int x, y;
			scanf ("%i %i", &x, &y);
			erro = aim (&current_image, pincel, POINT(x, y));
		}
		else if (cstrcmp (comando, "exit") == 0)
		{
			break;
		}
		else
		{
			erro = ex_NotFound;
		}
		if (erro != success)
		{
			if (erro == ex_MemInsuf)
			{
				printf ("Operação cancelada:: Memória insuficiente.\n");
			}
			else if (erro == ex_ImgInit)
			{
				printf ("Operação cancelada:: Nenhuma imagem foi inicializada.\n");
			}
			else if (erro == ex_ArcNonex)
			{
				printf ("Operação cancelada:: Arquivo inexistente.\n");
			}
			else if (erro == ex_InvFormat)
			{
				printf ("Operação cancelada:: Formato de arquivo inválido.\n");
			}
			else if (erro == ex_Non24Bit)
			{
				printf ("Operação cancelada:: O arquivo não corresponde a uma imagem de 24 bits.\n");
			}
			else if (erro == ex_InvSintax)
			{
				printf ("Operação cancelada:: Sintaxe do comando incorreta. Consulte \"help\".\n");
			}
			else if (erro == wa_UseColor)
			{
				printf ("Aviso:: Esta cor já estava sendo usada.\n");
			}
			else if (erro == wa_MisPixels)
			{
				printf ("Aviso:: Arquivo corrompido.\n");
			}
			else if (erro == ex_InvArg)
			{
				printf ("Operação cancelada:: Argumento inválido.\n");
			}
			else if (erro == ex_CNotFound)
			{
				printf ("Operação cancelada:: Cor não encontrada, digite \"listcolor\" para ver a lista de cores.\n");
			}
			else if (erro == ex_NotFound)
			{
				printf ("Comando não encontrado, digite \"help\" para ver lista de comandos.\n");
			}
			else
			{
				printf ("Erro desconhecido: (%i)\n", erro);
			}
		}
		else
		{
			rectfy (&current_image);
			save (&current_image, 6, "editview.ppm");
		}
		ffBuffer ();
	}
	remove ("editview.ppm");
	FREE (&current_image);
	FREE (&previous_image);
	return success;
}

