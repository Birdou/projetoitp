
Nesta parte do projeto há dois programas externos: O codgen e o RGLE.

RGLE:
	Esse programa se trata de um algoritmo para compressão de imagens PPM baseado no RLE, na ideia de tratar os valores RGB como um único dado, que pode ser repetido. 'N' vezes.
	
	Exemplo de uso: ./RGLE C exemplo1.ppm exemplo2.ppm
		Neste exemplo, a imagem 'exemplo1.ppm' está sendo comprimida (C) e sendo salva como 'exemplo2.ppm'
		
	Exemplo prático:
	
	P3
	4 4
	255 255 255 255 255 255 255 255 255 255 255 255 
	255 255 255 255 255 255 255 255 255 255 255 255 
	255 255 255 255 255 255 255 255 255 255 255 255 
	255 255 255 255 255 255 255 255 255 255 255 255 
	
	passa a ser:
	
	P3
	4 4
	\016ÿÿÿ
	
	, onde \016 corresponde a um elemento ASCII de valor 16 que indica a quantidade de pixeis, e ÿ o valor 255, repetidos 3 vezes representando os respectivos valores RGB de cada pixel.
	O algoritmo foi melhor compatibilizado e implementado no programa principal, podendo ser utilizado na interface do programa através do comando 'comp'.
	
codgen:
	Esse programa é um auxiliar de construção de algoritmos que exigem repetição. Fornece uma interface simples onde são requiridos alguns valores para a construção do mesmo, tais como o valor inicial de cada parâmetro, seu valor final e o incremento. Tem funcionamento similar a um laço de repetição 'for'.
	Na pasta onde está o programa, há um exemplo de imagem e um exemplo de código onde o programa pode ser útil.
