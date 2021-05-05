
/**
	Os parâmetros 'PPM * bitmap' e 'PENC pincel' deverão ser padrão para todas as funções que
	fizerem alteração na imagem, portanto não constarão na documentação da função.
**/

#ifndef FILTROS_H
#define FILTROS_H

/**
*	Função: GRAYSCALE
*	Descrição: Aplica um filtro preto e branco na imagem.
*	Parâmetros: Nenhum parâmetro especial requirido.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int grayscale (PPM * bitmap);

/**
*	Função: SEPIA
*	Descrição: Aplica um filtro sépia na imagem.
*	Parâmetros: Nenhum parâmetro especial requirido.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int sepia (PPM * bitmap);

/**
*	Função: BRIGHTEN
*	Descrição: Aumenta o brilho da imagem.
*	Parâmetros: A função abaixo recebe o percentual que a imagem deverá ter seu brilho aumentado.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int brighten (PPM * bitmap, double scale);

/**
*	Função: DARKEN
*	Descrição: Diminui o brilho da imagem.
*	Parâmetros: A função abaixo recebe o percentual que a imagem deverá ter seu brilho diminuído.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int darken (PPM * bitmap, double scale);

/**
*	Função: NEGATIVE
*	Descrição: Aplica um efeito negativo na imagem.
*	Parâmetros:
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int negative (PPM * bitmap);

/**
*	Função: INTENSITY
*	Descrição: Ajusta a intensidade de vermelho, verde e azul na imagem.
*	Parâmetros: A função abaixo recebe o percentual que os valores de cada cor deverão ser
	intensificados.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int intensity (PPM * bitmap, double red, double green, double blue);

/**
*	Função: REDEQUAL
*	Descrição: Ajusta a intensidade de vermelho, verde e azul na imagem de acordo com os níveis
	originais de vermelho.
*	Parâmetros: A função abaixo recebe o percentual que os valores de cada cor deverão ser
	intensificados.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int redequal (PPM * bitmap, double red, double green, double blue);

/**
*	Função: GREENEQUAL
*	Descrição: Ajusta a intensidade de vermelho, verde e azul na imagem de acordo com os níveis
	originais de verde.
*	Parâmetros: A função abaixo recebe o percentual que os valores de cada cor deverão ser
	intensificados.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int greenequal (PPM * bitmap, double red, double green, double blue);

/**
*	Função: BLUEEQUAL
*	Descrição: Ajusta a intensidade de vermelho, verde e azul na imagem de acordo com os níveis
	originais de azul.
*	Parâmetros: A função abaixo recebe o percentual que os valores de cada cor deverão ser
	intensificados.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int blueequal (PPM * bitmap, double red, double green, double blue);

/**
*	Função: VIBRANCY
*	Descrição: Ajusta a vibração das cores da imagem.
*	Parâmetros: A função abaixo recebe o percentual que a vibração das cores deverá ser modificado.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int vibrancy (PPM * bitmap, double scale);

/**
*	Função: GLITCH
*	Descrição: Aplica um filtro 'glitch' na imagem.
*	Parâmetros: A função abaixo recebe um valor inteiro que corresponderá ao distânciamento entre
	os planos de cores e o ângulo em que o distânciamento deverá ser executado.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int glitch (PPM * bitmap, int scale, double angle);

/**
*	Função: RBGLITCH
*	Descrição: Aplica um filtro 'glitch' preto e branco na imagem.
*	Parâmetros: A função abaixo recebe um valor inteiro que corresponderá ao distânciamento entre
	os planos de cores e o ângulo em que o distânciamento deverá ser executado.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int rbglitch (PPM * bitmap, int scale, double angle);

/**
*	Função: DESATURATE
*	Descrição: Dessatura os níveis de vermelho, verde e azul.
*	Parâmetros: A função abaixo recebe os níveis de	vermelho, verde e azul que servirão de limiar
	para serem dessaturados.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int desaturate (PPM * bitmap, double r, double g, double b);

/**
*	Função: PIXELIZE
*	Descrição: Reduz a resolução da imagem causando um efeito pixelizado.
*	Parâmetros: A função abaixo recebe um valor inteiro 'px' que corresponderá ao total de vezes em
	que a imagem terá sua resolução diminuída. 
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int pixelize (PPM * bitmap, int px);

/**
*	Função: GUEV
*	Descrição: Aplica um filtro Guevara na imagem.
*	Parâmetros: A função abaixo recebe um ponto flutuante que corresponderá ao percentual do limiar
	do efeito.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int guev (PPM * bitmap, double scale);

#endif
