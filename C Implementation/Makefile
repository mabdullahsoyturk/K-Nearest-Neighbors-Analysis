output: main.o k-nearest-neighbour.o utilities.o
	gcc main.c utilities.c k-nearest-neighbour.c -o output -lm

main.o: utilities.h k-nearest-neighbour.h
	gcc -c main.c

k-nearest-neighbour.o: k-nearest-neighbour.h utilities.h
	gcc -c k-nearest-neighbour.c

utilities.o: utilities.h
	gcc -c utilities.c

clean: 
	rm *.o output