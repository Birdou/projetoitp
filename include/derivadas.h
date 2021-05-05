
/**
	Os parâmetros 'PPM * bitmap' e 'PENC pincel' deverão ser padrão para todas as funções que
	fizerem alteração na imagem, portanto não constarão na documentação da função.
**/

#ifndef DERIVADAS_H
#define DERIVADAS_H

/**
*	Função: SCOLOR
*	Descrição: Modifica a cor do pincel.
*	Parâmetros: A função abaixo recebe o ponteiro de um pincel e o nome de uma cor 'colorname' que
	deverá corresponder a uma cor em getrgbval (lib.h).
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int scolor (PENC * pincel, char * colorname);

/**
*	Função: SCLEAR
*	Descrição: Limpa a imagem com a cor informada.
*	Parâmetros: A função abaixo recebe o nome de uma cor 'colorname' que deverá corresponder a uma
	cor em getrgbval (lib.h).
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int sclear (PPM * bitmap, char * colorname);

/**
*	Função: ROTATE
*	Descrição: Gira a imagem em 90° no sentido horário.
*	Parâmetros: Nenhum parâmetro especial requirido.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int rotate (PPM * bitmap);

/**
*	Função: INVERT
*	Descrição: Inverte a imagem verticalmente.
*	Parâmetros: Nenhum parâmetro especial requirido.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int invert (PPM * bitmap);

/**
*	Função: CURVE
*	Descrição: Desenha uma curva de Bézier de ordem qualquer.
*	Parâmetros: A função abaixo recebe os elementos requiridos para a construção de uma curva de
	Bézier, tais como o número de pontos 'ordem' e suas respectivas coordenadas.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int curve (PPM * bitmap, PENC pincel, int ordem, COORD * pontos);

/**
*	Função: ELIPSE
*	Descrição: Desenha uma elipse.
*	Parâmetros: A função abaixo recebe a posição 'pos', onde será o centro da elipse, sua largura,
	altura, ângulo de inclinação (ou rotação) e um valor 'p' que dirá se a elipse deverá ser
	preenchida.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int elipse (PPM * bitmap, PENC pincel, COORD pos, int width, int height, double angle, int p);

/**
*	Função: UNDO
*	Descrição: Desfaz a última alteração feita na imagem.
*	Parâmetros: A função abaixo recebe o ponteiro da imagem 'prevbitmap', local onde estarão os
	dados da imagem antes da última alteração.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int undo (PPM * bitmap, PPM * prevbitmap);

/**
*	Função: SIZE
*	Descrição: Modifica a grossura do pincel.
*	Parâmetros: Um valor inteiro que corresponderá a grossura do pincel.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int size (PENC * pincel, int size);

/**
*	Função: GLOBAL
*	Descrição: Pinta todos os pixeis de mesma cor em escala global.
*	Parâmetros: A função abaixo recebe a posição 'pos' que aponta para a cor que será substituída
	pela cor do pincel.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int global (PPM * bitmap, PENC pincel, COORD pos);

int aim (PPM * bitmap, PENC pincel, COORD pos);

#endif
