#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define EMPTY 0

/*   Users
 
 Estrutura que representa um usuário da rede social.
 
     char id[100]             - id do usuário
     char name[200]           - nome do usuário
     int age                  - idade do usuário
     char favouriteColor[200] - cor favorita do usuário
     char divasPop[200]       - diva pop favorita do usuário
     char favouriteMovie[200] - filme favorito do usuário
     char hatedMovie[200]     - filme mais odiado do usuário
     char city                - cidade do usuário
     int myLove               - armazena o ID do(a) namorado(a) do usuário conectado
     int dist[100]            - vetor que guarda a distancia entre cada usuário */
typedef struct users {
    char id[100];
    char name[200];
    int age;
    char favouriteColor[200];
    char divasPop[200];
    char favouriteMovie[200];
    char hatedMovie[200];
    char city[200];
    int myLove;
    int dist[100];
} Users;

/*   Graph
 
 Estrutura em forma de grafo que representa a rede social.
 
    int similarity[100][100] - matriz de adjacencia que guarda a similaridade
    int friendship[100][100] - matriz de adjacencia que guarda as relações de amizade
    int vertices             - número total de vertices do grafo
    int dir                  - armazena se o grafo é direcionado
    int numUser              - número de usuários atual da rede social
    Users **community        - vetor de usuários */
typedef struct graph
{
    int similarity[100][100];
    int friendship[100][100];
    int vertices;
    int dir;
    int numUser;
    Users *community;
} Graph;

/*   create_graph
 
 Função responsável por criar o grafo.
 
 Argumentos:
        int n       - número de vertices
        int d       - armazena se o grafo é direcionado
        int numUser - número de usuários atual da rede social
 
 Retorno:
        grafo criado */
Graph* create_graph(int n, int d,int numUser);

/*   destroy_graph
 
 Função responsável por liberar a memória alocada para o grafo.
 
 Argumentos:
        Graph* g - grafo */
void destroy_graph(Graph* g);