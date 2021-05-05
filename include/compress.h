
#ifndef COMPRESS_H
#define COMPRESS_H

/**
*	Função: COMP
*	Descrição: Comprime uma imagem PPM preexistente.
*	Parâmetros: A função abaixo recebe duas strings que correspondem respectivamente ao caminho do
	arquivo original e o caminho do arquivo processado (comprimido ou descomprimido).
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
**/
int comp (char * fin, char * fout);

#endif
