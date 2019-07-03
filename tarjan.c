// #include "adj_list.h"
#include "adj_matrix.h"
#include "stack.h"

void tarjan_rec(int u, Graph *g, int *t_in, int *low, Stack *s, int *stackMember) {
	int w;
	// Vertex *aux;
	static int currTime = 0;

	t_in[u] = ++currTime;
	low[u] = t_in[u];
	stack_push(s, u);
	stackMember[u] = 1;

	// aux = g->listArr[u].head;
	// while (aux) {
	for (int v = 0; v < g->nVertices; v++) {
		if (g->mat[u][v] != EMPTY) {
			// v = aux->dest;

			if (t_in[v] == -1) {
				tarjan_rec(v, g, t_in, low, s, stackMember);

				if (low[v] < low[u])
					low[u] = low[v];

			} else if (stackMember[v]) {

				if (t_in[v] < low[u])
					low[u] = t_in[v];
			}
	
		}
		
		// aux = aux->next;
	}

	w = 0;
	if (low[u] == t_in[u]) {
		while (s->top->value != u) {
			stack_pop(s, &w);
			printf("%d ", w);
			stackMember[w] = 0;
		}

		stack_pop(s, &w);
		printf("%d\n", w);
		stackMember[w] = 0;
	}
}

void tarjan(Graph *g, int u) {
	Stack *s;
	int t_in[g->nVertices], low[g->nVertices], stackMember[g->nVertices];
	printf("cheguei\n");
	s = stack_create();

	for (int i = 0; i < g->nVertices; i++) {
		low[i] = -1;
		t_in[i] = -1;
		stackMember[i] = 0;
	}

	for (int v = 0; v < g->nVertices; v++) {
		if (t_in[v] == -1)
			tarjan_rec(v, g, t_in, low, s, stackMember);
	}

	stack_destroy(s);
}

int main(int argc, char const *argv[])
{
	Graph *g;

	g = create_graph(13);

	insert_edge(g, 0, 1, 1);
	insert_edge(g, 0, 5, 1);

	insert_edge(g, 2, 0, 1);
	insert_edge(g, 2, 3, 1);

	insert_edge(g, 3, 2, 1);
	insert_edge(g, 3, 5, 1);

	insert_edge(g, 4, 3, 1);
	insert_edge(g, 4, 2, 1);

	insert_edge(g, 5, 4, 1);

	insert_edge(g, 6, 0, 1);
	insert_edge(g, 6, 4, 1);
	insert_edge(g, 6, 9, 1);

	insert_edge(g, 7, 6, 1);
	insert_edge(g, 7, 8, 1);

	insert_edge(g, 8, 7, 1);
	insert_edge(g, 8, 9, 1);

	insert_edge(g, 9, 10, 1);
	insert_edge(g, 9, 11, 1);

	insert_edge(g, 10, 12, 1);

	insert_edge(g, 11, 4, 1);
	insert_edge(g, 11, 12, 1);

	insert_edge(g, 12, 9, 1);

	// insert_edge(g, 0, 1, 1);
	
	// insert_edge(g, 1, 2, 1);
	// insert_edge(g, 1, 4, 1);

	// insert_edge(g, 2, 3, 1);

	// insert_edge(g, 3, 2, 1);
	// insert_edge(g, 3, 7, 1);

	// insert_edge(g, 4, 0, 1);
	// insert_edge(g, 4, 5, 1);

	// insert_edge(g, 5, 6, 1);

	// insert_edge(g, 6, 5, 1);

	// insert_edge(g, 7, 3, 1);
	// insert_edge(g, 7, 6, 1);

	tarjan(g, 0);

	destroy_graph(g);

	return 0;
}