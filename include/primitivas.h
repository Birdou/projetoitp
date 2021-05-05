
/**
	Os parâmetros 'PPM * bitmap' e 'PENC pincel' deverão ser padrão para todas as funções que
	fizerem alteração na imagem, portanto não constarão na documentação da função.
**/

#ifndef PRIMITIVAS_H
#define PRIMITIVAS_H

/**
*	Função: IMAGE
*	Descrição: Inicializa uma imagem PPM de acordo com a largura e altura especificadas.
*	Parâmetros: A função abaixo recebe a largura e a altura da imagem a ser inicializada.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int image (PPM * bitmap, int width, int height);

/**
*	Função: COLOR
*	Descrição: Modifica a cor do pincel.
*	Parâmetros: A função abaixo recebe uma cor RGB que substituirá a cor do pincel.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int color (PENC * pincel, RGB newcolor);

/**
*	Função: CLEAR
*	Descrição: Limpa a imagem com a cor informada.
*	Parâmetros: A função abaixo recebe uma cor RGB que será aplicada a todos os pixeis da imagem.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int clear (PPM * bitmap, RGB newcolor);

/**
*	Função: LINE
*	Descrição: Desenha uma linha.
*	Parâmetros: A função abaixo recebe dois pares de coordenadas P1 e P2 indicando onde a linha
	deve começar e terminar.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int line (PPM * bitmap, PENC pincel, COORD P1, COORD P2);

/**
*	Função: POLYGON
*	Descrição: Desenha um polígono com quaisquer número de lados.
*	Parâmetros: A função abaixo recebe o número de lados do polígono e um par de coodenadas para
	cada lado.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int polygon (PPM * bitmap, PENC pincel, int lados, COORD * pontos);

/**
*	Função: RECT
*	Descrição: Desenha um retângulo.
*	Parâmetros: A função abaixo recebe a posição 'pos', onde será o centro do retângulo, sua
	largura e altura.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int rect (PPM * bitmap, PENC pincel, COORD pos, int width, int height);

/**
*	Função: CIRCLE
*	Descrição:
*	Parâmetros: A função abaixo recebe a posição 'pos', onde será o centro da circunferência, seu
	raio e um valor 'p' que dirá se a circunferência deverá ser preenchida.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int circle (PPM * bitmap, PENC pincel, COORD pos, int raio, int p);

/**
*	Função: FILL
*	Descrição: Preenche uma região da imagem de cor similar em sua extensão.
*	Parâmetros: A função abaixo recebe um par de coordenadas 'pos'.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int fill (PPM * bitmap, PENC pincel, COORD pos);

/**
*	Função: SAVE
*	Descrição: Salva a imagem.
*	Parâmetros: A função abaixo recebe um valor inteiro magic 3 ou 6 uma string que deverá
	corresponder ao caminho onde a imagem será salva.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int save (PPM * bitmap, int magic, char * arquivo);

/**
*	Função: OPEN
*	Descrição: Carrega uma imagem PPM preexistente.
*	Parâmetros: A função abaixo recebe uma string que deverá corresponder ao caminho da imagem a
	ser aberta.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int open (PPM * bitmap, char * arquivo);

#endif
