#include "graph.h"

typedef struct users Users;

Graph* create_graph(int n, int d,int numUser)
{
    Graph *g;

    g = (Graph*) calloc(1, sizeof(Graph));

    if (!g) {
        printf("!! Erro de alocacao\n");
        return NULL;
    }

    g->community = (Users*) calloc (MAX, sizeof(Users));

    g->dir = d;
    g->vertices = n;
    g->numUser = numUser;

    for (int i = 0; i < g->vertices; i++){
        for (int j = 0; j < g->vertices; j++){
            g->similarity[i][j] = -1;
            g->friendship[i][j] = EMPTY;
        }
    }
    
    return g;
}

void destroy_graph(Graph* g)
{
    free(g->community);
    free(g);
}