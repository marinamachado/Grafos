#include <stdio.h>
#include <stdlib.h>

/*   Node
 
 Estrutura que representa um nó da fila.
 
    int id - guarda a identificação de cada nó
    node *next: ponteiro para o próximo nó da fila */
typedef struct node 
{
	int id;
	struct node* next;
} Node;

/*   Queue
 
 Estrutura que representa uma fila.
 
    Node *head - nó que aponta para o começo da fila
    Node *tail - nó que aponta para o fim da fila
    int size - inteiro, guarda o tamanho da fila */
typedef struct queue 
{
	Node *head, *tail;
	int size;
} Queue;

/*   create_queue
 
 Função responsável por criar a fila.
 
 Retorno:
    fila criada */
Queue* create_queue();

/*   is_empty
 
 Função que retorna se a fila está vazia.
 
 Argumentos:
        Queue *q - fila
 
 Retorno:
    1 - se está vazia
    0 - se não está vazia */
int is_empty(Queue* q);

/*   get_node
 
 Função que cria um novo nó.
 
 Argumentos:
        int x - id do novo nó
 
 Retorno:
        novo nó */
Node* get_node(int x);

/*   insert
 
 Função responsável por inserir elementos na fila.
 
 Argumentos:
        Queue *q - fila
        int x - elemento que será inserindo na fila */
void insert(Queue* q, int x);

/*   pop
 
 Função responsável por remover elementos da fila.
 
 Argumentos:
        Queue *q - fila */
int pop(Queue* q);