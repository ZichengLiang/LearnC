CFLAGS=-Wall -g
clean:
	rm -f ex1 ex3 ex7
all:
	make ex1 ex3 ex7
	./ex1
	./ex3
	./ex7
