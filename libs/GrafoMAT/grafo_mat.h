#ifndef GRAFO_MAT_H
#define GRAFO_MAT_H

typedef struct grafoMAT {
    int *mat;
    int v;
    int a;
} grafoMAT_t;


grafoMAT_t * grafoMAT_init(int v);
grafoMAT_t * grafoMAT_delete(grafoMAT_t* g);
void grafoMAT_print(grafoMAT_t*g);


// Grafo não dirigido
void grafoMAT_insere_aresta(grafoMAT_t* g, int v, int w, int val);
void grafoMAT_remove_aresta(grafoMAT_t* g, int v, int w);
grafoMAT_t* grafoMAT_kruskal(grafoMAT_t*g);


// Grafo dirigido
void grafoMAT_insere_aresta_dir(grafoMAT_t *g, int v, int w, int val);
void grafoMAT_remove_aresta_dir(grafoMAT_t *g, int v, int w);


#endif