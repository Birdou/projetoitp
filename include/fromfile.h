
#ifndef FROMFILE_H
#define FROMFILE_H

/**
*	Função: FROMFILE
*	Descrição: Executa a leitura de um arquivo e interpreta os comandos do mesmo.
*	Parâmetros: A função abaixo recebe uma string que corresponde ao caminho do arquivo que será
	processado.
*	Retorno: Um número inteiro representando o nível de erro. retorna success (0) caso a função 
	tenha realizado o procedimento corretamente.
*	Observações: A função undo e outros procedimentos não serão interpretados durante o processo de
	leitura. A abertura de arquivos dentro da própria função é permitido.
**/
int fromfile (char * in);

#endif
