/* Lucas Franchini Baes */
#ifndef GRAFO_H
#define GRAFO_H
#include <linked_list.h>

// grafo com lista de adjacencias
typedef struct grafoADJ {
    node_t** lista;
    int v;
    int a;
} grafoADJ_t;

grafoADJ_t* grafo_init(int nv);
void insere_aresta(grafoADJ_t* g, int v, int w);
void remove_aresta(grafoADJ_t* g, int v, int w);
void print_grafo(grafoADJ_t* grafo);
grafoADJ_t* deletar_grafo(grafoADJ_t* g);
void grafo_caminho(grafoADJ_t* g, int s);
grafoADJ_t* grafo_init_arquivo(const char* fname);
int grafo_existe_caminho(grafoADJ_t *g, int s, int t);
int existe_aresta(grafoADJ_t *g, int v, int w);
void grafo_toposort(grafoADJ_t* g);

#endif