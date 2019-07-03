#include <stdio.h>
#include <stdlib.h>

typedef struct stackNode {
	int value;
	struct stackNode* prev;
} sNode;

typedef struct stack {
	sNode* top;
} Stack;

Stack* stack_create();
void stack_destroy(Stack *s);

int stack_isEmpty(Stack* s);

void stack_push(Stack* s, int x);
int stack_pop(Stack* s, int* v);