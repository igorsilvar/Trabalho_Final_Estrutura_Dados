# Trabalho_Final_Estrutura_Dados
# Mapa Rodoviário do Piauí com Grafos em C

Este projeto simula um mapa rodoviário entre cidades do estado do Piauí, utilizando a estrutura de **grafos direcionados em linguagem C. Com ele, é possível:

- Representar conexões entre cidades (estradas);
- Listar **todos os caminhos possíveis** de uma cidade de origem até um destino;
- Determinar o **caminho mais curto** entre duas cidades;
- Descobrir o **caminho mais longo** entre duas cidades (sem ciclos).

## Cidades Representadas

As cidades são representadas como vértices em um grafo:

0: Corrente
1: Bom Jesus
2: Floriano
3: Oeiras
4: Teresina
5: Piripiri
6: Parnaíba


---

##  Como o programa funciona

### Estrutura de Dados

- `Graph`: estrutura que contém o número de vértices `V`, número de arestas `A` e a matriz de adjacência `adj`, usada para armazenar as conexões entre as cidades.
- `adj[v][w] = 1`: significa que há um arco (estrada) de `v` para `w`.

### Funções principais

#### `GRAPHinit(int V)`
Cria e inicializa o grafo com `V` vértices e nenhuma aresta.

#### `GRAPHinsertArc(Graph G, vertex v, vertex w)`
Insere uma aresta dirigida (estrada) de `v` para `w` no grafo `G`.

#### `GRAPHshow(Graph G)`
Exibe todas as conexões de cada cidade, como uma lista de adjacência legível.

---

## Caminhos

### `allPaths(Graph G, int u, int dest)`
Imprime **todos os caminhos possíveis** da cidade `u` (origem) até a cidade `dest` (destino), sem repetir vértices.  
Utiliza **backtracking com vetor de visita**.

### `shortestPath(Graph G, int start, int end)`
Calcula e exibe o **caminho mais curto** entre duas cidades usando o algoritmo **BFS (Busca em Largura)**, ideal para grafos não ponderados.

### `findLongestPath(Graph G, int u, int dest, int depth)`
Calcula o **caminho mais longo** de `u` até `dest` sem ciclos, utilizando **DFS (Busca em Profundidade)** com controle de profundidade e vetor de visita.

---

## 🧪 Exemplo de execução

Com as seguintes conexões:

Corrente -> Bom Jesus
Bom Jesus -> Floriano
Floriano -> Oeiras
Oeiras -> Teresina
Teresina -> Piripiri
Piripiri -> Parnaíba
Bom Jesus -> Oeiras
Oeiras -> Piripiri


### Saída :

Mapa Rodoviário:
Corrente -> Bom Jesus
Bom Jesus -> Floriano Oeiras
Floriano -> Oeiras
Oeiras -> Teresina Piripiri
Teresina -> Piripiri
Piripiri -> Parnaíba
Parnaíba ->

Todos os caminhos de Corrente até Parnaíba:
Corrente -> Bom Jesus -> Floriano -> Oeiras -> Teresina -> Piripiri -> Parnaíba
Corrente -> Bom Jesus -> Floriano -> Oeiras -> Piripiri -> Parnaíba
Corrente -> Bom Jesus -> Oeiras -> Teresina -> Piripiri -> Parnaíba
Corrente -> Bom Jesus -> Oeiras -> Piripiri -> Parnaíba

Caminho mais curto de Corrente até Parnaíba:
Caminho mais curto (6 passos): Corrente -> Bom Jesus -> Oeiras -> Piripiri -> Parnaíba

Caminho mais longo de Corrente até Parnaíba:
Corrente -> Bom Jesus -> Floriano -> Oeiras -> Teresina -> Piripiri -> Parnaíba
