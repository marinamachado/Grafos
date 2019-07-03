#include <string.h>
#include <stdlib.h>
#include "MaisQueMigos.h"

#define MAX 100
#define FRIEND 3
#define INF 100000

void tarjan(int u, Graph *g, int *t_in, int *low, Stack *s, int *stackMember) {
	int  w;
	static int currTime = 0;

	t_in[u] = ++currTime;
	low[u] = t_in[u];
	stack_push(s, u);
	stackMember[u] = 1;

	for (int v = 0; v < g->numUser; v++) {
		if (g->friendship[u][v] != EMPTY) {
			if (t_in[v] == -1) {
				tarjan(v, g, t_in, low, s, stackMember);
				if (low[v] < low[u])
					low[u] = low[v];
			} else if (stackMember[v]) 
				if (t_in[v] < low[u])
					low[u] = t_in[v];
		}
	}

	w = 0; 
	if (low[u] == t_in[u]) {
        printf("PANELINHA:\n");
		while (s->top->value != u) {
			stack_pop(s, &w);
			printf("- %s\n", g->community[w].id);
			stackMember[w] = 0;
		}

		stack_pop(s, &w);
		printf("- %s\n", g->community[w].id);
		stackMember[w] = 0;
	}
}

void find_group(Graph *g, int u) {
	Stack *s;
	int t_in[g->numUser], low[g->numUser], stackMember[g->numUser];
    
    printf("\n------------- LISTAR PANELINHAS-------------\n");
    printf("Só as amigas online!!!!!!!!\n\n");

	s = stack_create();
	for (int i = 0; i < g->numUser; i++) {
		low[i] = -1;
		t_in[i] = -1;
		stackMember[i] = 0;
	}

	for (int v = 0; v < g->numUser; v++)
		if (t_in[v] == -1)
			tarjan(v, g, t_in, low, s, stackMember);

	stack_destroy(s);
}

void more_info(Graph *g, int user)
{    
    printf("---------- USUARIO %s --------------\n\n", g->community[user].id);
    printf("Nome: %s \n", g->community[user].name);
    printf("Idade: %d\n", g->community[user].age);
    printf("Cor favorita: %s\n", g->community[user].favouriteColor);
    printf("Diva Pop: %s\n", g->community[user].divasPop);
    printf("Filme favorito: %s\n", g->community[user].favouriteMovie);
    printf("Filme odiado: %s\n", g->community[user].hatedMovie);
    printf("Cidade: %s\n", g->community[user].city);
    if (g->community[user].myLove == -1)
        printf("Estado Civil: Solteiro\n");
    else
        printf("Estado Civil: Namorando com %s\n", g->community[g->community[user].myLove].id);
}

void invite_friend(Graph *g, int user1, int user2)
{
    g->friendship[user2][user1] = 2;
}

void find_best_friends(Graph *g, int user)
{    
    int find, n;

    printf("---------------- ENCONTRE MELHORES AMIGOS -------------\n\n");   
    printf("Qual opção você quer?\n");
    printf("Opção 1 : Você quer achar amigos com base nos seus gostos\n");
    printf("Opção 2 : Você quer achar amigos com base nos seus amigos em comum\n");
    
    
    scanf("%d",&n);
    
    find = 0;    
    if (n == 1) {
        printf("----------------- OPÇÃO 1 -----------------\n\n");
        for (int i = 0; i < g->numUser; i++) {
            if (g->similarity[user][i] >= FRIEND && g->friendship[user][i] != 1 && g->community[user].id!= g->community[i].id) {    
                find = 1;
                
                printf("Acreditamos que %s seria um ótimo amigo para você, seu grau de similaridade é %d\n\n", g->community[i].id, g->similarity[user][i]);
                
                more_info(g, i);
                
                printf("Você quer ser amigo delx? Se sim aperte 1, se não aperte 0\n");
                scanf("%d", &n);
                if (n == 1)
                    invite_friend(g, user, i);
                else if (n == 0) {
                    g->friendship[user][i] = 0;
                    g->friendship[i][user] = 0;
                } else
                    printf("Opção inválida.\n");
            }
        }
    } else if (n == 2) {
        printf("----------------- OPÇÃO 2 -----------------\n\n");
        
        bfs(g, user);
        
        for (int i = 0; i < g->numUser; i++) {
            if (g->community[user].dist[i] <=2 && (g->community[user].id!=g->community[i].id) && g->friendship[user][i] == 0) {
                printf("%s tem distância %d de você achamos que seria um bom amigo\n", g->community[i].id, g->community[user].dist[i]);
               
                find = 1;
                more_info(g, i);
                
                printf("Você quer ser amigo delx? Se sim aperte 1, se não aperte 0\n");
                scanf("%d", &n);
                if (n == 1)
                    invite_friend(g, user, i);
                else if (n == 0) {
                    g->friendship[user][i] = 0;
                    g->friendship[i][user] = 0;
                } else
                    printf("Opção inválida.\n");
            }
        }
    }
    
    if (find == 0)
        printf("Não há nenhuma recomendação\n\n");
    principal_menu(g, user);
}


void bfs(Graph *g, int user)
{    
    Queue *q;
    int visited[MAX];

    q = create_queue();
    
    for (int i = 0; i < g->numUser; i++)
       g->community[user].dist[i] = INF;
    
    for (int i = 0; i < g->numUser; i++)
        visited[i] = 0;
    
    insert(q,user);
    g->community[user].dist[user] = 0;
    visited[user] = 1;
    
    while (is_empty(q) == 0) {
        int currVertex = pop(q);
        
        for (int i = 0; i < g->numUser; i++) {
            if (g->friendship[currVertex][i] && visited[i] == 0) {
                insert(q, i);
                g->community[user].dist[i] = g->community[user].dist[currVertex] + 1;
                visited[i] = 1;
            }
        }
    }

    free(q);   
}

void find_not_friends(Graph *g, int user)
{    
    int findFriend, findNotFriend, n;

    printf("---------------- ENCONTRE POSSÍVEIS DESCONHECIDOS -------------\n\n");
    
    
    findFriend = 0; findNotFriend = 0;
    for (int i = 0; i < g->numUser; i++) {       
        
        if (g->friendship[user][i] == 1 ) {
            findFriend = 1;

            if (g->similarity[user][i] < FRIEND) {
                findNotFriend = 1;
                
                printf("Acreditamos que %s não é muito parecido com você, seu grau de similaridade é baixo e de %d\n", g->community[i].id, g->similarity[user][i]);
                
                printf("Você quer continuar sendo amigo dele? Se sim digite 1, se não digite 0\n");
                scanf("%d", &n);
                
                if (n == 0) {
                    g->friendship[user][i] = 0;
                    g->friendship[i][user] = 0;
                } else if (n != 1)
                    printf("Opção inválida.\n");
            }
        }
    }

    if (findFriend == 0)
        printf("Você não tem amigos\n\n");
    else if (findNotFriend == 0)
        printf("Todos seus amigos tem alta similaridade contigo\n\n");
    
    principal_menu(g, user);
}

void find_love_of_your_life(Graph *g, int user)
{
    int max, n, userMax;

    printf("---------------- ENCONTRE O AMOR DA SUA VIDA -------------\n\n");
    
    max = 0; userMax = -1;
    for (int i = 0 ; i < g->numUser; i++) {
        
        if (g->similarity[user][i] >= max && (g->community[user].id != g->community[i].id)) {
            max = g->similarity[user][i];
            userMax = i;
        }
    }

    if (userMax == -1) {
        printf("Nao há um amor para você\n");
        principal_menu(g, user);
    }
    
    printf("O possível amor da sua vida foi: %s, o grau de similaridade de vocês: %d\n\n", g->community[userMax].id,max);
    more_info(g, userMax);    
   
    printf("Quer enviar uma solicitação de namoro online!S2 Se sim aperte 1, se nao aperte 0\n");
    scanf("%d", &n);
    if (n == 1)
        g->friendship[userMax][user] = 3;
    else if (n != 0)
        printf("Opção inválida.\n");
    
    principal_menu(g, user);
}

void check_match(Graph *g, int user)
{    
    int find, n;
    
    printf("---------------- SOLICITAÇÕES DE WEB NAMORO -------------\n\n");
    
    find = 0;
    for (int i = 0; i < g->numUser; i++) {
        if (g->friendship[user][i] == 3) {
            find = 1;
            printf("Quer ser seu namoradx online\n");
            more_info(g,i);
            
            printf("Você quer ser namorax online  desse usuário? Seu grau de similaridade é %d! Se quiser ser digite 1, se não digite 0\n", g->similarity[user][i]);
            scanf("%d", &n);
            if (n == 1) {
                printf("                  _       _     \n");
                printf("  _ _   _    __ _| |_ ___| |__  \n");
                printf(" | '_ ` _   / _` | __/ __| '_   \n");
                printf(" | | | | | | (_| | || (__| | | | \n");
                printf(" |_| |_| |_| __,_| __ ___|_| |_| \n\n");
                
                g->community[user].myLove = i;
                g->community[i].myLove = user;
                g->friendship[user][i] = 1;
                g->friendship[i][user] = 1;
            } else if (n != 0)
                printf("Opção inválida.\n");
        }
    }

    if (find == 0)
        printf("Não há solicitações de namoro online\n");\
    
    principal_menu(g, user);
}

void check_new_friendship(Graph *g,int user){
    int find, n;

    printf("---------------- SOLICITAÇÕES DE AMIZADE -------------\n\n");
    
    find = 0;
    for (int i = 0; i < g->numUser; i++) {
        if (g->friendship[user][i] == 2) {
            find = 1;
           
            more_info(g, i);
            
            printf("Você quer ser amigo desse usuário? Seu grau de similaridade é %d! Se quiser ser digite 1, se não digite 0\n", g->similarity[user][i]);
            scanf("%d",&n);
            if (n == 1) {
                g->friendship[user][i] = 1;
                g->friendship[i][user] = 1;
            } else if (n == 0) {  
                g->friendship[user][i] = 0;
                g->friendship[i][user] = 0;
            } else
                printf("Opção inválida.\n");
        }
    }
    
    if (find == 0)
        printf("Não há solicitações de amizade\n");
    
    principal_menu(g, user);
}

void update_similarity(Graph *g, int user)
{    
    int similarity;
    for (int i = 0; i < g->numUser ; i++) {
        similarity = 0;
        
        if (g->community[user].age == g->community[i].age)
            similarity++;
        if (strcmp(g->community[user].favouriteColor, g->community[i].favouriteColor) == 0)
            similarity++;
        if (strcmp(g->community[user].favouriteMovie, g->community[i].favouriteMovie) == 0)
            similarity++;
        if (strcmp(g->community[user].divasPop, g->community[i].divasPop) == 0)
            similarity++;
        if (strcmp(g->community[user].hatedMovie, g->community[i].favouriteMovie) == 0)
            similarity--;
        if (strcmp(g->community[user].hatedMovie, g->community[i].hatedMovie) == 0)
            similarity++;
        if (strcmp(g->community[user].city, g->community[i].city) == 0)
            similarity++;
        
        g->similarity[user][i] = similarity;
        g->similarity[i][user] = similarity;
    }
}

void update_profile(Graph *g, int user)
{    
    printf("---------------- ATUALIZAÇÃO -------------\n\n");   
    
    printf("Quais valores dos novos campos\n");
    printf("Nome: ");
    scanf(" %[^\n]s", g->community[user].name);
    printf("Idade: ");
    scanf("%d", &g->community[user].age);
    printf("Cor favorito: ");
    scanf(" %[^\n]s", g->community[user].favouriteColor);
    printf("Diva Pop: ");
    scanf(" %[^\n]s", g->community[user].divasPop);
    printf("Filme favorito: ");
    scanf(" %[^\n]s", g->community[user].favouriteMovie);
    printf("Filme odiado: ");
    scanf(" %[^\n]s", g->community[user].hatedMovie);
    printf("Cidade: ");
    scanf(" %[^\n]s", g->community[user].city);
    update_similarity(g, user);
    
    principal_menu(g, user);
}

void print_friends(Graph *g, int user)
{    
    int find;
    printf("---------------- LISTAS DE AMIGOS -------------\n\n");
    
    find = 0;
    for (int i = 0; i < g->numUser; i++) {
        if (g->friendship[user][i] == 1) {
            find = 1;
            more_info(g,i);
        }
    }

    if (find == 0)
        printf("Você não tem amigos\n");
    
    principal_menu(g, user);
}


void sign_in(Graph *g)
{       
    int user;
    char id[100];
    printf("-----------------SIGN IN------------------\n\n");
    
    printf("Qual seu id de usuário: ");
    scanf("%s",id);
    
    user = search_id(g, id);
    while (user == -1) {
        printf("Usuario nao existe, insira novamente\n");
        scanf("%s",id);
        user = search_id(g, id);
    }
    
    printf("Bem-vindo de volta %s\n\n", g->community[user].name);
    
    principal_menu(g, user);
}

void principal_menu(Graph *g, int user)
{    
    int n;

    printf("---------------- MENU DE OPÇÕES -------------\n\n");
    printf("Quais das opções abaixo você quer realizar? Digite o número da opção\n");
    printf("Opção 1: Encontrar possíveis melhores amigos\n");
    printf("Opção 2: Listar panelinha\n");
    printf("Opção 3: Encontrar possíveis desconhecidos\n");
    printf("Opção 4: Encontrar possível amor da sua vida\n");
    printf("Opção 5: Checar solicitações de amizade\n");
    printf("Opção 6: Atualizar suas informações\n");
    printf("Opção 7: Lista de amigos\n");
    printf("Opção 8: Enviar solicitacao de amizade\n");
    printf("Opção 9: Checar solicitações de namoro online\n");
    printf("Opção 10: Mostra meu perfil\n");
    printf("Opção 11: Sair da minha conta\n");
    
    scanf("%d",&n);
    
    switch (n) {
        case 1:
            find_best_friends(g, user);
            break;
        case 2:
            find_group(g, user);
            break;
        case 3:
            find_not_friends(g, user);
            break;
        case 4:
            find_love_of_your_life(g, user);
            break;
        case 5:
            check_new_friendship(g, user);
            break;
        case 6:
            update_profile(g, user);
            break;
        case 7:
            print_friends(g, user);
            break;
        case 8:
            printf("----------------- ENVIE UMA SOLICITAÇÃO DE AMIZADE ------------------\n\n");
            printf("Qual o nome do usuário do seu amigo?");
            
            char id[100];
            scanf("%s", id);
            n = search_id(g, id);

            if (n == -1) {
                printf("Usuario nao existe\n");
                principal_menu(g, user);
            }

            invite_friend(g, user, n);
            principal_menu(g, user);
            
            break;
        case 9:
            check_match(g, user);
            break;
        case 10:
            more_info(g, user);
            principal_menu(g, user);
            break;
        case 11:
            printf("BYE BYE\n");
            open_social_midia(g);
            break;
        default:
            printf("Opção inválida.\n");
            break;
    }
}

int search_id(Graph *g, char id[100])
{
    for (int i = 0 ; i < g->numUser; i++) {
        if (strcmp(g->community[i].id, id) == 0)
            return i;
    }
 
    return -1;
}

void sign_up(Graph *g) {
    int flag, n, user;
    
    user = g->numUser;
    n = user + 1;
    
    // g->community[user] = (Users*) calloc(1, sizeof(Users));
    
    for (int i = 0; i < n; i++) 
        g->friendship[user][i] = 0;
    
    g->community[user].myLove = -1;
    
    printf("-----------------SIGN UP------------------\n\n");
    printf("Quais valores dos novos campos?\n\n");
    printf("Crie seu nome de usuário: ");
    
    flag = 0;
    while (flag != -1) {
        scanf("%s", g->community[user].id);
        flag = search_id(g, g->community[user].id);
        if (flag != -1)
          printf("Esse usuario já existe, insira outro\n");
    }

    printf("Nome: ");
    scanf(" %[^\n]s", g->community[user].name);
    printf("Idade: ");
    scanf("%d",&g->community[user].age);
    printf("Cor favorito: ");
    scanf(" %[^\n]s", g->community[user].favouriteColor);
    printf("Diva Pop: ");
    scanf(" %[^\n]s", g->community[user].divasPop);
    printf("Filme favorito: ");
    scanf(" %[^\n]s", g->community[user].favouriteMovie);
    printf("Filme odiado: ");
    scanf(" %[^\n]s", g->community[user].hatedMovie);
    printf("Cidade: ");
    scanf(" %[^\n]s", g->community[user].city);
    
    update_similarity(g, g->numUser);
    
    g->numUser++;
    
    printf("Agora você pode entrar na nossa rede social!!!!!!\n\n");
    
    principal_menu(g, user);
}

void open_social_midia(Graph *g)
{    
    int n;

    printf("\n------------- BEM VINDO MAIS QUE MIGOS, FRIENDS ---------------------\n\n");    
    printf("Se você já tiver uma conta digite 1, caso não e queira criar seu perfil digite 2\n");
    scanf("%d", &n);
    
    switch(n) {
        case 1:
            sign_in(g);
            break;
        case 2:
            sign_up(g);
            break;
        default:
            printf("Opção inválida.!\nSaindo da rede...\n");
            return;
    }

    // if (n == 1)
    //     sign_in(g);
    // else if (n == 2)
    //     sign_up(g);
    // else
    //     printf("Opção inválida.\n");
}

void load_database(Graph* g) {
    int id;
    FILE* input;
    
    input = fopen("tst.txt", "r");
    fseek(input, 0, SEEK_END);
    long long int fileSize = ftell(input);
    rewind(input);
    
    while (ftell(input) != fileSize) {
        id = g->numUser++;
        // g->community[id] = (Users*) calloc(1, sizeof(Users));
        fscanf(input, " %[^,],%[^,],%d,%[^,],%[^,],%[^,],%[^,],%[^,\n]", g->community[id].id, g->community[id].name, &g->community[id].age, g->community[id].favouriteColor, g->community[id].divasPop, g->community[id].favouriteMovie, g->community[id].hatedMovie, g->community[id].city);
        g->community[id].myLove = -1;
        update_similarity(g, id);
    }  
}