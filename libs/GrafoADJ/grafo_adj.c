/* Lucas Franchini Baes */
#include "grafo_adj.h"
#include <stdio.h>
#include <stdlib.h>

// forca a saida do programa em caso de erro
static void crash(const char* msg){
    printf("%s\n", msg);
    exit(EXIT_FAILURE);
}

// aloca memoria para o grafo e para a lista de adjacencias
grafoADJ_t* grafo_init(int nv) {
    grafoADJ_t* grafo = malloc(sizeof(grafoADJ_t));
    if (grafo == NULL) crash("Erro ao alocar memoria para o grafoADJ_t em grafo_init()");
    grafo->a = 0;
    grafo->v = nv;

    grafo->lista = malloc(grafo->v * sizeof(node_t*));
    if (grafo->lista == NULL) crash("Erro ao alocar memoria para grafo->lista em grafo_init()");
    for (int i = 0; i < grafo->v; ++i) {
        grafo->lista[i] = NULL;
    }

    return grafo;
}

// insere uma aresta v->w
void insere_aresta(grafoADJ_t* g, int v, int w) {
    g->lista[v] = insert_in_order(g->lista[v], w);
    ++(g->a);
}

// remove uma aresta v->w
void remove_aresta(grafoADJ_t* g, int v, int w) {
    g->lista[v] = remove_node(g->lista[v], find_node(g->lista[v], w));
    --(g->a);
}

// retorna 1 se a aresta v->w existe no grafo g, 0 caso nao exista
int existe_aresta(grafoADJ_t* g, int v, int w) {
    return (find_node(g->lista[v], w) != NULL);
}

// printa o grafo em stdout
void print_grafo(grafoADJ_t* g) {
    for (int i = 0; i < g->v; ++i) {
        printf("%d: ", i);
        print_list(g->lista[i]);
    }
}

// libera a memoria do grafo e da lista de adjacencia;
grafoADJ_t* deletar_grafo(grafoADJ_t* g) {
    for (int i = 0; i < g->v; ++i) {
        g->lista[i] = delete_list(g->lista[i]);
    }
    free(g->lista);
    g->lista = NULL;
    free(g);
    return NULL;
}

// auxiliar para grafo_print_caminho
void grafo_caminho_aux(grafoADJ_t* g, int s, int* visitados) {
    visitados[s] = 1;
    printf("%d->", s);
    for (node_t* adj = g->lista[s]; adj != NULL; adj = adj->next) {
        if (visitados[adj->n] == 0) {
            grafo_caminho_aux(g, adj->n, visitados);
        }
    }
}

// printa o caminho percorrido do vertice 0 até o vertice s
void grafo_caminho(grafoADJ_t* g, int s) {
    int* visitados = calloc(g->v, sizeof(int));
    grafo_caminho_aux(g, s, visitados);
    free(visitados);
    printf("\n");
}

// auxiliar para grafo existe caminho
int grafo_existe_caminho_aux(grafoADJ_t* g, int s, int t, int * visitados){
    visitados[s] = 1;
    if (s == t)
        return 1;
    for (node_t* adj = g->lista[s]; adj != NULL; adj = adj->next) {
        if (visitados[adj->n] == 0) {
            if (grafo_existe_caminho_aux(g, adj->n, t, visitados))
                return 1;
        }
    }
    return 0;
}

// retorna 1 se existe caminho entre os vertices s e t, 0 caso contrario
int grafo_existe_caminho(grafoADJ_t* g, int s, int t){
    int* visitados = calloc(g->v, sizeof(int));
    int ret = grafo_existe_caminho_aux(g, s, t, visitados);
    free(visitados);
    return ret;
}


// cria um grafo a partit de um arquivo fname (foi usado para testes)
grafoADJ_t* grafo_init_arquivo(const char* fname) {
    FILE* fp = fopen(fname, "r");
    int num_vertices;
    fscanf(fp, "%d\n", &num_vertices);
    grafoADJ_t* g = grafo_init(num_vertices);
    int v, adj;
    for (int i = 0; i < num_vertices; i++){
        fscanf(fp, "%d:", &v);
        while ((adj = fgetc(fp)) != ';'){
            if (adj != ',' && adj != '\n')
                insere_aresta(g, v, adj - '0');
        }
    }
    fclose(fp);
    return g;
}


// auxiliar para grafo_toposort
void grafo_toposort_aux(grafoADJ_t* g, int * indegrees){
    node_t * head = NULL;
    for (int i = 0; i < g->v; i++) {
        if (indegrees[i] == 0){
            head = insert_at_head(head, i);
        }
    }

    while (head != NULL){
        int v = head->n;
        printf("%d ", v+1);
        head = remove_node(head, head);

        for (node_t* cur = g->lista[v]; cur != NULL; cur = cur->next){
            indegrees[cur->n] -= 1;
            if (indegrees[cur->n] == 0)
                head = insert_at_head(head, cur->n);
        }
    }
    printf("\n");
    delete_list(head);
}

// printa a ordenacao topologica do grafo g 
void grafo_toposort(grafoADJ_t* g){

    //vetor  com graus de entrada
    int * indegrees = calloc(g->v, sizeof(int));
    for (int i = 0; i < g->v; i++){
        for (node_t* cursor = g->lista[i]; cursor != NULL; cursor = cursor->next){
            indegrees[cursor->n] += 1;
        }
    }

    grafo_toposort_aux(g, indegrees);
    free(indegrees);

}