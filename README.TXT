**Habilitar a quebra de texto**

Por Charles Vitor Bulcão e Felipe Sena de Medeiros.
Última versão: 04/12/2019 às 16:03

** Algumas das imagens feitas durante o projeto estão disponíveis em:
<https://drive.google.com/drive/folders/1G9FjvkwNFZI3x7fNaGHFB6X7fQwaJY0A?usp=sharing>

----------------Descrição geral e recursos----------------

	O programa PaintIt dispõe de todas as primitivas gráficas, mais de 30 funções extras divididas em funções derivadas e filtros, tamanho ajustável do pincel e 145 cores HTML [1] que podem ser chamadas pelo nome pelas funções de prefixo 's' [2];

	Dentre as derivadas foram implementadas funções de desenhos de elipses e curvas, rotação e inversão de imagens, preenchimento global e a função undo [3];

	Os filtros de imagem variam de efeitos a correções de cor. O usuário pode escolher entre preto e branco, sépia e negativo ou ainda ajustar o brilho, a intensidade e a vibração das cores da imagem, dessaturar cores específicas, igualar outras, redimensionar a imagem [4] entre várias outras funções de edição;

	O programa pode fazer a leitura de arquivos P3 ou P6 e arquivos de cabeçalho [5];

	É possível também optar por salvar entre os formatos P3 e P6 com o comando save, pois, apesar de o formato P3 ser legível e mencionado na descrição do projeto, é também o que ocupa mais espaço e mais demora a ser lido;

	Aqui foi desenvolvido um sistema de compressão de imagens simples e automático baseado no RLE. Imagens P3 simples podem ter seu tamanho reduzido em até 500 vezes [6][7]. O efeito pode ocorrer de forma reversa se a imagem dispor de muitas cores/tons;

	O usuário tem acesso a lista de comandos, suas respectivas sintaxes e descrição, e ainda a lista de cores divididas por tons de cinza a pastel;

1 - Disponíveis em: <https://celke.com.br/artigo/tabela-de-cores-html-nome-hexadecimal-rgb>
2 - scolor e sclear
3 - Responsável por desfazer a última alteração feita na imagem
4 - Por enquanto só é possível redimensionar a imagem para resoluções menores
5 - Arquivos de texto com as instruções de criação da imagem
6 - Considerando uma imagem P3 limpa de qualquer resolução
7 - Em imagens P6, a eficiência é 4 vezes menor por ser um arquivo binário

----------------Diretórios----------------

	./source/ contém todos os arquivos com as funções que compõem o programa principal;
	./source/help/ contém alguns arquivos de texto com as sintaxes e descrições das funções e nome de cores. Embora os arquivos possam ser abertos, os mesmos podem ser visualizados pela interface do programa;
	./objects/Windows/ contém os objetos necessários para a compilação para o sistema operacional Windows;
	./objects/Linux/ contém os objetos necessários para a compilação para os sistemas operacionais baseados em Unix;
	./util/ contém alguns programas criados durante o desenvolvimento do projeto que podem auxiliar o usuário na criação/transporte de imagens e arquivos de cabeçalho.

----------------Arquivos----------------
	
	O arquivo 'algoritmo.txt' pode ser usado durante a execução do programa com a função 'fromfile' como exemplo.
	O arquivo 'makefile' é responsável por conter as instruções de compilação do projeto.
	
----------------Modularização----------------

	'exe.c' contém todo o código de interpretação de comandos, retorno de exceções, salvamento automático e passagem de parâmetros;
	'lib.c' contém funções e definições essenciais para o funcionamento de outras funções;
	'primitivas.c' contém as funções exigidas na descrição do projeto;
	'derivadas.c' contém variações das funções primitivas e outras funções à disposição do usuário;
	'help.c' contém procedimentos de suporte ao usuário;
	'filtros.c' possui funções de ajuste de imagem;
	'compress.c' contém um algoritmo de compressão e descompressão de imagens P3 e P6 baseado em RLE dedicado ao formato RGB;
	'fromfile.c' contém o algorítmo de interpretação de comandos baseado na main, dedicado a arquivos.
	
----------------Informações técnicas e extras----------------

	Linguagem: C;
	Compatibilidade: Windows, Linux;
	Requisitos para (re)compilação: Sistema operacional baseado em Unix;
	Compiladores: x86_64-w64-mingw32-gcc (para Windows), gcc;
	Exceções tratadas: 9;
	Tempo médio de desenvolvimento: +120h;
	Funções: 60 +;
	Fim de linha (arquivos salvos): CR (Carriage return, Mac Os);
	Interface: Não;
	Conceitos matemáticos utilizados: Matemática básica, matriz de rotação, fatorial, binômio de Newton, geometria analítica;
	Versão: 1.2.0 +
	
----------------Makefile----------------

	make linux: Constrói o projeto para sistemas operacionais baseados em Unix;
	make windows: Constrói o projeto para o sistema operacional Windows;
	make all: Constrói o projeto para os dois sistemas operacionais simultaneamente.
	make clean: Apaga os arquivos utilizados durante a compilação, assim como seus respectivos binários finais.

