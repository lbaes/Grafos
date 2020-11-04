#include "grafo_mat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @brief calcula um indice 1D
/// @param g grafo
/// @param v posicao x numa matriz
/// @param w posicao y numa matriz
/// @return posicao [v][w] como um unico indice
static int MATindex(grafoMAT_t *g, int v, int w)
{
    return v * g->v + w;
}

/// @brief Inicializa um grafo usando representacao de matriz de adjacencias.
/// @param v numero de verices
/// @return grafoMAT_t inicializado ou NULL
grafoMAT_t *grafoMAT_init(int v)
{
    grafoMAT_t *grafo = NULL;
    grafo = calloc(1, sizeof(grafoMAT_t));
    if (grafo != NULL)
    {
        grafo->a = 0;
        grafo->v = v;
        grafo->mat = calloc(v * v, sizeof(int));
        if (grafo->mat == NULL)
        {
            free(grafo);
            grafo = NULL;
        }
    }    
    return grafo;
}

/// @brief Libera os recursos usados pelo grafo g
/// @param g grafo que sera deletado
/// @return NULL
grafoMAT_t *grafoMAT_delete(grafoMAT_t *g)
{
    free(g->mat);
    free(g);
    return NULL;
}

/// @brief insere uma aresta dirigida entre os vertices v e w
/// @param v vertice v
/// @param w vertice w
/// @return void
void grafoMAT_insere_aresta_dir(grafoMAT_t *g, int v, int w, int val)
{
    g->mat[MATindex(g, v, w)] = val;
    g->a++;
}

/// @brief insere uma aresta dirigida entre os vertices v e w
/// @param v vertice v
/// @param w vertice w
/// @return void
void grafoMAT_remove_aresta_dir(grafoMAT_t *g, int v, int w)
{
    g->mat[MATindex(g, v, w)] = 0;
    g->a--;
}

/// @brief insere uma aresta nao dirigida entre os vertices v e w
/// @param v vertice v
/// @param w vertice w
/// @return void
void grafoMAT_insere_aresta(grafoMAT_t *g, int v, int w, int val)
{
    g->mat[MATindex(g, w, v)] = val;
    g->mat[MATindex(g, v, w)] = val;
    g->a++;
}

/// @brief insere uma aresta nao dirigida entre os vertices v e w
/// @param v vertice v
/// @param w vertice w
/// @return void
void grafoMAT_remove_aresta(grafoMAT_t *g, int v, int w)
{
    g->mat[MATindex(g, w, v)] = 0;
    g->mat[MATindex(g, v, w)] = 0;
    g->a--;
}

/// @brief printa o grafo em forma de matriz
/// @param g grafo
void grafoMAT_print(grafoMAT_t *g)
{
    int i, j;
    for (i = 0; i < g->v; ++i)
    {
        for (j = 0; j < g->v; ++j)
            printf("%2d ", g->mat[MATindex(g, i, j)]);
        printf("\n");
    }
}


/// @brief estrutura representando uma aresta e seu valor ou custo;
typedef struct aresta
{
    int valor;
    int v;
    int w;
} aresta_t;


/// @brief funcao find da estrutura de dados union-find 
static int find(int *componentes, int i)
{
    if (componentes[i] == -1)
        return i;
    return find(componentes, componentes[i]);
}

/// @brief funcao merge da estrutura de dados union-find
static void merge(int *componentes, int i, int j)
{
    int comp_u = find(componentes, i);
    int comp_v = find(componentes, j);

    if (comp_u != comp_v)
        componentes[comp_u] = comp_v;
}


/// @brief Algoritmo de Kruskal para geração de árvore geradora minima
/// @param g Grafo conexo e não dirigido
/// @param A Vetor de arestas ordenadas crescentemente
/// @return Novo grafo representando arvore geradora minima a partir de g  
static grafoMAT_t *kruskal_aux(grafoMAT_t *g, aresta_t *A)
{
    grafoMAT_t *T = grafoMAT_init(g->v);
    if (T == NULL) {
        printf("Erro ao inicializar um grafoMAT em kruskal_aux()\n");
        return NULL;
    }

    int componentes[g->v];
    memset(componentes, -1, g->v * sizeof(int));
    int ai = 0;
    while (T->a < g->v - 1 && ai < g->a)
    {
        aresta_t menor_aresta = A[ai++];
        int comp_u = find(componentes, menor_aresta.v);
        int comp_v = find(componentes, menor_aresta.w);
        if (comp_u != comp_v)
        {
            merge(componentes, comp_u, comp_v);
            grafoMAT_insere_aresta(T, menor_aresta.v, menor_aresta.w, menor_aresta.valor);
        }
    }

    return T;
}

/// @brief funcao de comparacao entre duas arestas_t para o qsort()
static int comparacao(const void *a, const void *b)
{
    int A = ((aresta_t *)a)->valor;
    int B = ((aresta_t *)b)->valor;

    if (A > B) return 1;
    if (A < B) return -1;
    return 0;
}

/// @brief Arvore geradora minima usando Kruskal, este algoritmo precisa de um grafo nao direcional,
/// ou seja se a aresta v->w existe entao a aresta w->v tambem existirá
/// @param g grafo nao direcionado conexo que será modificado
/// @return novo grafo representando uma arvore geradora minima, lembre de deleta-lo usando grafoMAT_delete() ou NULL em caso de erro
grafoMAT_t *grafoMAT_kruskal(grafoMAT_t *g)
{
    int i, j, k;
    aresta_t *A = malloc(sizeof(aresta_t) * g->a);
    if (A == NULL){
        printf("Erro ao alocar vetor de arestas em grafoMAT_kruskal()\n");
        return NULL;
    }
    k = 0;
    for (i = 0; i < g->v; ++i)
        for (j = i; j < g->v; ++j)
            if (g->mat[MATindex(g, i, j)] != 0)
            {
                A[k].valor = g->mat[MATindex(g, i, j)];
                A[k].v = i;
                A[k].w = j;
                k++;
            }
    qsort(A, g->a, sizeof(*A), comparacao);
    grafoMAT_t *T = kruskal_aux(g, A);
    free(A);
    return T;
}