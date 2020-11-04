#include <stdio.h>
#include <stdlib.h>
#include <grafo_adj.h>
#include <grafo_mat.h>

int main(int argc, char const *argv[])
{
    grafoMAT_t *g = grafoMAT_init(7);
    if (g){
        grafoMAT_insere_aresta(g, 0, 2, 5);
        grafoMAT_insere_aresta(g, 0, 3, 8);

        grafoMAT_insere_aresta(g, 2, 1, 16);
        grafoMAT_insere_aresta(g, 2, 3, 10);
        grafoMAT_insere_aresta(g, 2, 4, 3);

        grafoMAT_insere_aresta(g, 3, 4, 2);
        grafoMAT_insere_aresta(g, 3, 5, 18);

        grafoMAT_insere_aresta(g, 4, 1, 30);
        grafoMAT_insere_aresta(g, 4, 5, 12);
        grafoMAT_insere_aresta(g, 4, 6, 14);

        grafoMAT_insere_aresta(g, 1, 6, 26);
        grafoMAT_insere_aresta(g, 5, 6, 4);
    
        grafoMAT_t* AGM = grafoMAT_kruskal(g);
        g = grafoMAT_delete(g);

        if (AGM) {
            grafoMAT_print(AGM);
            AGM = grafoMAT_delete(AGM);
        }
    }else {
        printf("Houve um erro\n");
    }
    
    return 0;
}
