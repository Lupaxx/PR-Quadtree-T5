# PR-Quadtree-T5

(MAE 016) Top. Eng. Dados B: Estruturas de Dados e seus Algoritmos
Tarefa de programação 5: PR-Quadtree

Referência e base do código: https://github.com/ProfRamirez/TEDB.ED.2023.2/tree/main/Exemplos/Exemplo_PR_Quadtree_001

## Struct Point2D
Cria uma estrutura inicial para um ponto em um ambiente bidimensional contendo coordenada em x e y.

## Struct Reg_Node
Cria uma estrutura de nó para a quadtree, contendo a posição do nó e dados associados. 

## Classe no_PR_Quadtree
Contém construtores diferentes dependendo da entrada: entrada nula, entrada somente contendo as restrições de área da quadtree e entrada com as restrições e o primeiro conjunto de dados a ser inserido na quadtree
A classe contém 5 métodos:

### Void Insert
Insere um nó na quadtree, inserindo no quadrante apropriado, descendo na árvore até encontrar um quadrante vazio. 

### Reg_Node* Search
Busca um nó com base em uma posição, percorrendo recursivamente a árvore até encontrá-lo. Caso não encontre, retorna nulo. 

### bool inBoundary
Verifica se uma posição esta dentro do quadrante de um nó. 

### vector<Reg_Node> searchInArea
Procura e retorna uma lista de nós dentro de uma área, fazendo uma verificação recursiva nos quadrantes contidos na área.

### Reg_Node* findNearestPoint
Busca o ponto mais próximo de uma posição especificada dentro de um raio de busca, fazendo uma verificação recursiva nos quadrantes contidos na área e guardando o ponto encontrado mais próximo para retorná-lo. 
