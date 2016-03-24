CC=gcc
proj2: proj2.o queue.o stats.o 
	gcc -lm proj2.c queue.c stats.c -o proj2
proj2: proj2.c

test: test1 test2 test3
test1:
	./proj2
	./proj2 
	./proj2
test2:
	./proj2 proj21.dat 
	./proj2 proj21.dat
	./proj2 proj21.dat 
test3:
	./proj2 proj22.dat 
	./proj2 proj22.dat 
	./proj2 proj22.dat 
