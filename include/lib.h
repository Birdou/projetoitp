
#ifndef LIB_H
#define LIB_H

/**
*	Typedef struct: RGB
*	Descrição: Struct de uma cor RGB.
*	Propriedades: Valores de vermelho, verde e azul.
**/
typedef struct color
{
	short r;
	short g;
	short b;
}RGB;

/**
*	Typedef struct: PPM
*	Descrição: Struct de uma imagem PPM.
*	Propriedades: Largura, altura, e uma matriz RGB.
**/
typedef struct parametrosppm
{
	int width;
	int height;
	RGB ** color;
}PPM;

/**
*	Typedef struct: PENC
*	Descrição: Struct de um pincel.
*	Propriedades: Cor e tamanho.
**/
typedef struct pincel
{
	RGB color;
	double size;
}PENC;

/**
*	Typedef struct: COORD
*	Descrição: Struct de um par de coordenadas.
*	Propriedades: Valor no eixo X e valor no eixo Y.
**/
typedef struct coordenadas
{
	int x;
	int y;
}COORD;

/**
*	Função: COLOR (case sensitive)
*	Descrição: Transforma valores inteiros em um dado do tipo RGB
*	Parâmetros: A função abaixo recebe valores de vermelho, verde e azul.
*	Retorno: Retorna uma cor com os valores de vermelho, verde e azul especificados.
**/
RGB COLOR (int r, int g, int b);

/**
*	Função: IMAGE (case sensitive)
*	Descrição: Transforma alguns valores em um dado do tipo PPM
*	Parâmetros: A função abaixo recebe largura, altura, e uma matriz RGB.
*	Retorno: Retorna um protótipo (não alocado) de uma imagem.
**/
PPM IMAGE (int width, int height, RGB ** color);

/**
*	Função: POINT
*	Descrição: Transforma valores inteiros em um dado do tipo COORD
*	Parâmetros: A função abaixo recebe valores no eixo X e Y.
*	Retorno: Retorna uma coordenada ('x', 'y').
**/
COORD POINT (int x, int y);

/**
*	Grupo de funções: RGBPI
*	Descrição: Realiza operações aritméticas e geométricas entre uma cor e um valor numérico.
*	Parâmetros: A função abaixo recebe uma cor RGB e um valor numérico, esse será utilizado na
	operação entre os valores de vermelho, verde e azul da cor.
*	Retorno: Retorna uma cor com os valores operados.
**/
RGB RGBPI_SUM (RGB color, double num);
RGB RGBPI_DIFFERENCE (RGB color, double num);
RGB RGBPI_PRODUCT (RGB color, double num);
RGB RGBPI_DIVIDE (RGB color, double num);

/**
*	Grupo de funções: RGBPC
*	Descrição: Realiza operações aritméticas e geométricas entre duas cores.
*	Parâmetros: A função abaixo recebe duas cores RGB, as quais terão seus valores de vermelho,
	verde e azul operados.
*	Retorno: Retorna uma cor com os valores operados.
**/
RGB RGBPC_SUM (RGB color1, RGB color2);
RGB RGBPC_DIFFERENCE (RGB color1, RGB color2);
RGB RGBPC_PRODUCT (RGB color1, RGB color2);
RGB RGBPC_DIVIDE (RGB color1, RGB color2);

/**
*	Enum: EXCEPTS
*	Descrição: O enum abaixo enumera erros e avisos utilizados nos retorno das funções.
**/
enum excepts
{
	success = 0,
	ex_MemInsuf = -1,
	ex_ImgInit = -2,
	ex_ArcNonex = -3,
	ex_InvFormat = -4,
	ex_Non24Bit = -5,
	ex_InvSintax = -6,
	ex_InvArg = -7,
	ex_NotFound = -8,
	ex_CNotFound = -9,
	wa_UseColor = 1,
	wa_MisPixels = 2,
};

/**
*	Função: RGBMIX
*	Descrição: Mistura duas cores
*	Parâmetros: A função abaixo recebe duas cores RGB.
*	Retorno: Retorna uma cor com os valores RGB correspondentes a média	entre os valores RGB das
	cores fornecidas.
**/
RGB rgbmix (RGB color1, RGB color2);

/**
*	Função: CLONE
*	Descrição: Copia uma imagem.
*	Parâmetros: A função abaixo recebe duas imagens PPM. A segunda será a cópia da primeira.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int clone (PPM * image1, PPM * image2);

/**
*	Função: RGBCMP
*	Descrição: Compara duas cores.
*	Parâmetros: A função abaixo recebe duas cores color1 e color2.
*	Retorno: Se as cores forem idênticas, a função retorna 0, senão, 1.
**/
int rgbcmp (RGB color1, RGB color2);

/**
*	Função: PPMCMP
*	Descrição: Compara duas imagens.
*	Parâmetros: A função abaixo recebe duas imagens image1 e image2. 
*	Retorno: Se as imagens forem idênticas, a função retorna 0, senão, 1.
**/
int ppmcmp (PPM * image1, PPM * image2);

/**
*	Procedimento: DRAW
*	Descrição: Modifica os pixeis da imagem de acordo com as propriedades do pincel.
*	Parâmetros: A função abaixo recebe valores no eixo X e Y.
**/
void draw (PPM * image, PENC pincel, int PX, int PY);

/**
*	Função: FAT
*	Descrição: Calcula o fatorial de um número.
*	Parâmetros: A função abaixo recebe um número inteiro, o qual terá seu fatorial calculado.
*	Retorno: Retorna o fatorial de 'num'.
**/
long int fat (int num);

/**
*	Função: BIN
*	Descrição: Calcula o binômio de Newton ('n' 'i').
*	Parâmetros: A função abaixo recebe dois números inteiros n e i
*	Retorno: Retorna o valor do binômio de Newton ('n' 'i').
**/
long int bin (int n, int i);

/**
*	Função: RAD
*	Descrição: Converte graus em radianos.
*	Parâmetros: A função abaixo recebe um ponto flutuante em graus.
*	Retorno: Retorna o valor de 'degrees' em radianos.
**/
double rad (double degrees);

/**
*	Função: CSTRCMP
*	Descrição: Compara duas strings não diferenciando maiúsculas e minúsculas.
*	Parâmetros: A função abaixo recebe duas strings.
*	Retorno: Se as strings forem idênticas, retorna 0, senão, a diferênça entre os caracteres entre
	elas.
**/
int cstrcmp (char * string1, char * string2);

/**
*	Procedimento: FFBUFFER
*	Descrição: Limpa o buffer de entrada.
*	Parâmetros: -.
**/
void ffBuffer ();

/**
*	Procedimento: FREE (case sensitive)
*	Descrição: Libera a memória ocupada por uma imagem.
*	Parâmetros: O procedimento abaixo recebe uma imagem PPM.
**/
void FREE (PPM * image);

/**
*	Função: BW
*	Descrição: Transforma uma cor em escala de cinza.
*	Parâmetros: A função abaixo recebe uma cor 'color'.
*	Retorno: Retorna uma cor na escala de cinza.
**/
RGB bw (RGB color);

/**
*	Função: ANTIGUE
*	Descrição: Transforma uma cor em escala sépia.
*	Parâmetros: A função abaixo recebe uma cor 'color'.
*	Retorno: Retorna uma cor na escala sépia.
**/
RGB antigue (RGB color);

/**
*	Procedimento: RECTFY
*	Descrição: Retifica os valores de vermelho, verde e azul da imagem.
*	Parâmetros: O procedimento abaixo recebe uma imagem PPM.
**/
void rectfy (PPM * image);

/**
*	Função: GETRGBVAL
*	Descrição: Associa o nome de uma cor ao seu respectivo valor RGB e aplica ao pincel.
*	Parâmetros: A função abaixo recebe uma string que deverá corresponder ao nome da cor.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int getrgbval (char * cor, RGB * pincel);

#endif
