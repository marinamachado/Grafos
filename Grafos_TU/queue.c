#include "queue.h"

Queue* create_queue() 
{
	Queue* q = (Queue*) calloc(1, sizeof(Queue));

	if (!q) {
		printf("!! Erro de alocacao\n");
		return NULL;
	}

	q->head = NULL;
	q->size = 0;

	return q;
}

int is_empty(Queue* q) 
{
	if (!q) {
		printf("!! Fila nao alocada\n");
		return 1;
	}

	return !(q->size);
}

Node* get_node(int x) 
{
	Node* n = (Node*) calloc(1, sizeof(Node));
	if (!n) {
		printf("!! Erro de alocacao\n");
		return NULL;
	}

	n->id = x;
	n->next = NULL;
	
	return n;
}

void insert(Queue* q, int x) 
{
	if (!q) {
		printf("!! Fila nao alocada\n");
		return;
	}

	if (is_empty(q)) {
		q->head = get_node(x);
		q->tail = q->head;
	} else {
		q->tail->next = get_node(x);
		q->tail = q->tail->next;
		q->tail->next = NULL;
	}

	(q->size)++;
}

int pop(Queue* q) 
{
	if (!q) {
		printf("!! Fila nao alocada\n");
		return -1;
	}

	if (is_empty(q)) {
		printf("!! Fila vazia\n");
		return -1;
	}

	Node* n = q->head;
	int info = n->id;
	q->head = n->next;
	free(n);
	(q->size)--;

	return info;
}