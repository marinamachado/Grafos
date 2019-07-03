all: 
	gcc stack.c queue.c graph.c MaisQueMigos.c main.c -o main -g -Wall

run: 
	./main
