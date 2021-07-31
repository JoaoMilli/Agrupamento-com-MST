all:
	make compilar

compilar: 
	gcc -o trab1 *.c -lm 

valexecutar:
	valgrind ./trab1 1.txt 3 saida.txt
	
executar:
	./trab1 entrada.txt 3 saida.txt
