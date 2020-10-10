all:
	gcc -o main src/main.c src/lista.c src/site.c -I./includes
run:
	./main