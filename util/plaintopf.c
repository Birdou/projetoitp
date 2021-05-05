#include <stdio.h>


int main(int argc, char * argv[])
{
	if (argc < 3)
	{
		printf("Uso: %s [arquivo] [destino]\n", argv[0]);
		return -1;
	}

	FILE*  fin = fopen(argv[1], "r");
	FILE* fout = fopen(argv[2], "w");

	if(fin == NULL)
	{
		printf("Erro: Arquivo inexistente \"%s\"\n", argv[1]);
		return -1;
	}

	unsigned char c;
	while(c != 0)
	{
		fprintf(fout, "printf(\"");
		for(int i = 0; i < 256; ++i)
		{
			if(fscanf(fin, "%c", &c) < 1)
			{
				c = 0;
				break;
			}
			else if(c == '\\')
			{
				fprintf(fout, "\\\\");
			}
			else if(c == '\'')
			{
				fprintf(fout, "\\\'");
			}
			else if(c == '\"')
			{
				fprintf(fout, "\\\"");
			}
			else if(c == '\n')
			{
				fprintf(fout, "\\n");
			}
			else if(c == '\r')
			{
				fprintf(fout, "\\r");
			}
			else if(c == '\t')
			{
				fprintf(fout, "\\t");
			}
			else
			{
				fprintf(fout, "%c", c);
			}
		}
		fprintf(fout, "\");\n");
	}

	fclose(fin);
	fclose(fout);

	return 0;
}