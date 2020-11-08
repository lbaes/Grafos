#include <stdio.h>
#include <stdlib.h>
#include <grafo_adj.h>
#include <grafo_mat.h>

int main(int argc, char const *argv[])
{
    grafoMAT_t *g = grafoMAT_init(7);
    grafoMAT_t *g2 = grafoMAT_init(7);
    if (g && g2){

        // Grafo teste
        grafoMAT_insere_aresta(g, 0, 1, 1);
        grafoMAT_insere_aresta(g, 0, 3, 4);
       
        grafoMAT_insere_aresta(g, 1, 2, 2);
        grafoMAT_insere_aresta(g, 1, 3, 6);
        grafoMAT_insere_aresta(g, 1, 4, 4);

        grafoMAT_insere_aresta(g, 2, 4, 5);
        grafoMAT_insere_aresta(g, 2, 5, 6);

        grafoMAT_insere_aresta(g, 3, 4, 3);
        grafoMAT_insere_aresta(g, 3, 6, 4);

        grafoMAT_insere_aresta(g, 4, 5, 8);
        grafoMAT_insere_aresta(g, 4, 6, 7);

        grafoMAT_insere_aresta(g, 5, 6, 3);



        
        grafoMAT_insere_aresta(g2, 0, 2, 5);
        grafoMAT_insere_aresta(g2, 0, 3, 8);

        grafoMAT_insere_aresta(g2, 2, 1, 16);
        grafoMAT_insere_aresta(g2, 2, 3, 10);
        grafoMAT_insere_aresta(g2, 2, 4, 3);

        grafoMAT_insere_aresta(g2, 3, 4, 2);
        grafoMAT_insere_aresta(g2, 3, 5, 18);

        grafoMAT_insere_aresta(g2, 4, 1, 30);
        grafoMAT_insere_aresta(g2, 4, 5, 12);
        grafoMAT_insere_aresta(g2, 4, 6, 14);

        grafoMAT_insere_aresta(g2, 1, 6, 26);
        grafoMAT_insere_aresta(g2, 5, 6, 4);
        

        grafoMAT_t* AGM = grafoMAT_kruskal(g);
        g = grafoMAT_delete(g);
        if (AGM) {
            printf("AGM teste:\n");
            grafoMAT_print(AGM);
            AGM = grafoMAT_delete(AGM);
        }

        printf("\n\n");
        grafoMAT_t* AGM2 = grafoMAT_kruskal(g2);
        g2 = grafoMAT_delete(g2);
        if (AGM2) {
            printf("AGM exercicio H:\n");
            grafoMAT_print(AGM2);
            AGM2 = grafoMAT_delete(AGM2);
        }

    }else {
        printf("Houve um erro\n");
    }
    
    return 0;
}
