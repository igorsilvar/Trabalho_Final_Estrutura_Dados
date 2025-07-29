#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define vertex int
#define MAX 100

const char *cidades[] = {
    "Corrente", "Bom Jesus", "Floriano", "Oeiras", "Teresina", "Piripiri", "Parnaíba"
};

typedef struct graph {
    int V;
    int A;
    int **adj;
} *Graph;

static int **MATRIXint(int r, int c, int val) {
    int **m = malloc(r * sizeof(int *));
    for (int i = 0; i < r; i++) {
        m[i] = malloc(c * sizeof(int));
        for (int j = 0; j < c; j++)
            m[i][j] = val;
    }
    return m;
}

Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = MATRIXint(V, V, 0);
    return G;
}

void GRAPHinsertArc(Graph G, vertex v, vertex w) {
    if (G->adj[v][w] == 0) {
        G->adj[v][w] = 1;
        G->A++;
    }
}

void GRAPHshow(Graph G) {
    for (int v = 0; v < G->V; v++) {
        printf("%s ->", cidades[v]);
        for (int w = 0; w < G->V; w++) {
            if (G->adj[v][w])
                printf(" %s", cidades[w]);
        }
        printf("\n");
    }
}

// --------------------- Caminhos ----------------------

int visited[MAX];
int path[MAX];
int pathIndex = 0;

// Mostra todos os caminhos de origem até destino
void allPaths(Graph G, int u, int dest) {
    visited[u] = 1;
    path[pathIndex++] = u;

    if (u == dest) {
        for (int i = 0; i < pathIndex; i++) {
            printf("%s%s", cidades[path[i]], (i < pathIndex - 1) ? " -> " : "\n");
        }
    } else {
        for (int v = 0; v < G->V; v++) {
            if (G->adj[u][v] && !visited[v]) {
                allPaths(G, v, dest);
            }
        }
    }

    pathIndex--;
    visited[u] = 0;
}

// Caminho mais curto
void shortestPath(Graph G, int start, int end) {
    int queue[MAX], front = 0, rear = 0;
    int pred[MAX], dist[MAX];

    for (int i = 0; i < G->V; i++) {
        visited[i] = 0;
        dist[i] = -1;
        pred[i] = -1;
    }

    visited[start] = 1;
    dist[start] = 0;
    queue[rear++] = start;

    while (front < rear) {
        int u = queue[front++];

        for (int v = 0; v < G->V; v++) {
            if (G->adj[u][v] && !visited[v]) {
                visited[v] = 1;
                dist[v] = dist[u] + 1;
                pred[v] = u;
                queue[rear++] = v;

                if (v == end) {
                    int pathStack[MAX], idx = 0;
                    for (int crawl = end; crawl != -1; crawl = pred[crawl])
                        pathStack[idx++] = crawl;

                    printf("Caminho mais curto (%d passos): ", dist[end]);
                    for (int i = idx - 1; i >= 0; i--)
                        printf("%s%s", cidades[pathStack[i]], (i > 0) ? " -> " : "\n");
                    return;
                }
            }
        }
    }
    printf("Sem caminho de %s para %s\n", cidades[start], cidades[end]);
}

// Caminho mais longo
int longest = 0;
int longestPath[MAX];
int currentPath[MAX];

void findLongestPath(Graph G, int u, int dest, int depth) {
    visited[u] = 1;
    currentPath[depth] = u;

    if (u == dest) {
        if (depth > longest) {
            longest = depth;
            memcpy(longestPath, currentPath, sizeof(int) * (depth + 1));
        }
    } else {
        for (int v = 0; v < G->V; v++) {
            if (G->adj[u][v] && !visited[v])
                findLongestPath(G, v, dest, depth + 1);
        }
    }

    visited[u] = 0;
}

// ------------------ Programa Principal --------------------

int main(void) {
    Graph G = GRAPHinit(7);  // 7 cidades

    // Conexões entre cidades
    GRAPHinsertArc(G, 0, 1); // Corrente -> Bom Jesus
    GRAPHinsertArc(G, 1, 2); // Bom Jesus -> Floriano
    GRAPHinsertArc(G, 2, 3); // Floriano -> Oeiras
    GRAPHinsertArc(G, 3, 4); // Oeiras -> Teresina
    GRAPHinsertArc(G, 4, 5); // Teresina -> Piripiri
    GRAPHinsertArc(G, 5, 6); // Piripiri -> Parnaíba
    GRAPHinsertArc(G, 1, 3); // Bom Jesus -> Oeiras
    GRAPHinsertArc(G, 3, 5); // Oeiras -> Piripiri

    printf("Mapa Rodoviário:\n");
    GRAPHshow(G);

    printf("\nTodos os caminhos de Corrente até Parnaíba:\n");
    memset(visited, 0, sizeof(visited));
    allPaths(G, 0, 6);

    printf("\nCaminho mais curto de Corrente até Parnaíba:\n");
    shortestPath(G, 0, 6);

    printf("\nCaminho mais longo de Corrente até Parnaíba:\n");
    memset(visited, 0, sizeof(visited));
    longest = 0;
    findLongestPath(G, 0, 6, 0);
    for (int i = 0; i <= longest; i++) {
        printf("%s%s", cidades[longestPath[i]], (i < longest) ? " -> " : "\n");
    }

    return 0;
}
