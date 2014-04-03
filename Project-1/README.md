Tema 2: Suporte para geração de testes a partir de máquinas de estados
======================================================================

###FAQs:

**P**: Como vão representar as máquinas de estados?  
**R**: Recorrendo a grafos dirigidos.

**P**: Quais vão ser os elementos dos grafos?  
**R**: Os grafos vão ter:
* vértices (vertexes) que representam estados;
* arestas (edges) que representam transições entre estados, causadas por eventos;
* um único estado inicial;
* pelo menos um estado final;
* todos os vértices devem ser atingíveis;
* não pode haver mais que uma transição com o mesmo evento, mesmo estado de origem e diferentes estados de destino.

**P**: O que é um caminho ponta-a-ponta e o que é que representa?  
**R**: É um caminho que começa no estado inicial e termina num estado final. Representa uma execução possível da máquina de estados.

**P**: Como vão ser representados os caminhos ponta-a-ponta?  
**R**: Vão ser representados por uma sequência alternada de nomes de vértices (estados) e arestas (eventos).

**P**: Como é dado o comprimento de um caminho?  
**R**: É igual ao número de arestas.

###Problemas a resolver:

1. Dada uma máquina de estados, verificar se a mesma é válida (verificar se cumpre as regras acima);
2. Determinar o caminho mais curto para chegar a um determinado estado;
3. Encontrar um conjunto de caminhos ponta-a-ponta de comprimento total mínimo, cobrindo todas as transições;
4. [Opcional] Determinar equivalência entre máquinas de estados.

###Sintaxe dos ficheiros de texto:

nVertexes  
ID stateDescription init final  
ID stateDescription init final  
ID stateDescription init final  
...  
nEdges  
eventDescription srcID destID  
eventDescription srcID destID  
eventDescription srcID destID  
...

######Legenda:

Sobre os vértices:
- nVertexes: int
  - número de estados (vértices)
- ID: int
  - ID do estado
- stateDescription: string
  - etiqueta do estado
- init: bool
  - true se o estado for o inicial
  - false caso contrário
- dest: bool
  - true se o estado for final/ de aceitação
  - false caso contrário

Sobre as arestas:
- nEdges: string
  - número de transições (arestas)
- eventDescription: string
  - etiqueta da transição
- srcID: int
  - ID do vértice de origem
- destID: int
  - ID do vértice de destino
