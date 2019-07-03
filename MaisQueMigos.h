#include "graph.h"
#include "queue.h"
#include "stack.h"

#include <stdio.h>

/*      more_info
 
 Função responsável por mostrar o perfil completo do usuário.
 
 Argumentos:
        Graph *g - grafo que respresenta a rede social
        int user - usuário */
void more_info(Graph *g,int user);

/*      invite_friend
 
 Função que permite enviar solicitação de amizade.
 
 Argumentos:
        Graph *g  - grafo que respresenta a rede social
        int user1 - usuário que quer enviou a solicitacao
        int user2 - usuário que vai receber a solicitacao */
void invite_friend(Graph *g,int user1,int user2);

/*      find_best_friend

 Função responsável por encontrar possíveis amizade.
 
 Argumentos:
        Graph *g - grafo que respresenta a rede social
        int user - usuário */
void find_best_friends(Graph *g,int user);

/*      bfs
 
 Busca em largura para calcular a distância entre os usuários.
 
 Argumentos:
        Graph *g - grafo que respresenta a rede social
        int user - usuário */
void bfs(Graph *g,int user);

/*      find_not_friends
 
 Função responsável por encontrar na sua lista de amigos pessoas com
 baixa similidaridade com o usuário.
 
 Argumentos:
        Graph *g - grafo que respresenta a rede social
        int user - usuário */
void find_not_friends(Graph *g,int user);

/*      find_love_of_your_life
 
 Função responsável por encontrar possíveis amor da sua vida.
 
 Argumentos:
        Graph *g - grafo que respresenta a rede social
        int user - usuário */
void find_love_of_your_life(Graph *g,int user);

/*      check_new_friendship
 
 Função que permite verificar as solicitacoes de amizade.
 
 Argumentos:
        Graph *g - grafo que respresenta a rede social
        int user - usuário */
void check_new_friendship(Graph *g,int user);

/*      update_similarity
 
 Função responsável por atualizar a similaridade entre os usuários.
 
 Argumentos:
        Graph *g - grafo que respresenta a rede social
        int user - usuário */
void update_similarity(Graph *g,int user);

/*      update_profile
 
 Função responsável por atualizar o perfil do usuário.
 
 Argumentos:
        Graph *g - grafo que respresenta a rede social
        int user - usuário */
void update_profile(Graph *g, int user);

/*      print_friends
 
 Função responsável por imprimir lista de amigos.
 
 Argumentos:
        Graph *g - grafo que respresenta a rede social
        int user - usuário */
void print_friends(Graph *g, int user);

/*      sign_in
 
 Função que permite o usuário entrar na sua conta.
 
 Argumentos:
        Graph *g - grafo que respresenta a rede social */
void sign_in(Graph *g);

/*      principal_menu
 
 Função mostra para o usuário todas as funcionalidades presente na rede social 
 e permite escolher entre elas.
 
 Argumentos:
        Graph *g - grafo que respresenta a rede social
        int user - usuário */
void principal_menu(Graph *g ,int user);

/*      search_id
 
 Função responsável por procurar o id e retornar o numero de usuário correspondente.
 
 Argumentos:
        Graph *g - grafo que respresenta a rede social
        char id[100] -  id que sera procurado
 Retorno:
        Número do usuário correspondete */
int search_id(Graph *g,char id[100]);

/*      sign_up
 
 Função que permite o usuário se cadastrar na rede social.
 
 Argumentos:
        Graph *g - grafo que respresenta a rede social */
void sign_up(Graph *g);

/*      open_social_midia
 
Função responsável por inicar a rede social.
 
 Argumentos:
        Graph *g - grafo que respresenta a rede social */
void open_social_midia(Graph *g);

/*      load_database
 
 Função responsável por ler um arquivo de texto e adicionar usuário na rede social.
 
 Argumentos:
    Graph *g - grafo que respresenta a rede social */
void load_database(Graph* g);