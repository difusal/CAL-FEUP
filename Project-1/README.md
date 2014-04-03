----------------------------------------------------------------------
Tema 2: Suporte para geração de testes a partir de máquinas de estados
----------------------------------------------------------------------

FAQs:
-----

P: Como vão representar as máquinas de estados?
R: Recorrendo a grafos dirigidos.

P: Quais vão ser os elementos dos grafos?
R: Os grafos vão ter:
	. vértices (vertexes) que representam estados;
	. arestas (edges) que representam transições entre estados, causadas por eventos;
	. um único estado inicial;
	. pelo menos um estado final;
	. todos os vértices devem ser atingíveis;
	. não pode haver mais que uma transição com o mesmo evento, mesmo estado de origem e diferentes estados de destino.

P: O que é um caminho ponta-a-ponta e o que é que representa?
R: É um caminho que começa no estado inicial e termina num estado final. Representa uma execução possível da máquina de estados.

P: Como vão ser representados os caminhos ponta-a-ponta?
R: Vão ser representados por uma sequência alternada de nomes de vértices (estados) e arestas (eventos).

P: Como é dado o comprimento de um caminho?
R: Pelo número de arestas.
