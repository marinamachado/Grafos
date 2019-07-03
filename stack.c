#include "stack.h"

Stack* stack_create() {
	Stack* s = (Stack*) calloc(1, sizeof(Stack));
	s->top = NULL;
	return s;
}

void stack_destroy(Stack *s) {
	if (s)
		free(s);
}

int stack_isEmpty(Stack* s) {
	return s->top ? 0 : 1;
}

void stack_push(Stack* s, int x) {
	sNode* n;

	n = (sNode*) calloc(1, sizeof(sNode));
	if (!n) 
		return;

	n->value = x;
	n->prev = s->top;
	s->top = n;
}

int stack_pop(Stack* s, int* v) {
	sNode* prev;

	if (stack_isEmpty(s))
		return -1;

	*v = s->top->value;
	prev = s->top->prev;
	
	free(s->top);
	s->top = prev;
	
	return 0;
}