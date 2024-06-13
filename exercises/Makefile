CFLAGS=-Wall -g
clean:
	rm -f ex1 ex3 ex7 ex8 ex9 ex10 ex11 ex12 ex13 ex14 ex15 ex16 ex17 ex18
all:
	make ex1 ex3 ex7 ex8 ex9 ex10 ex11 ex12 ex13 ex14 ex15 ex16 ex17 ex18
	./ex1
	./ex3
	./ex7
	./ex8 Chiara
	./ex9
	./ex10 Chiara
	./ex11
	./ex12
	./ex13 tdw is coming to
	./ex14 wow this is ex14
	./ex15
	./ex16
	./ex17 db.dat c
	./ex18 4 3 1 5 6

test_Database:
	make ex17
	./ex17 db.dat c
	./ex17 db.dat s 1 zed zed@zedshaw.com
	./ex17 db.dat s 2 frank frank@zedshaw.com
	./ex17 db.dat s 3 joe joe@zedshaw.com
	./ex17 db.dat l
	./ex17 db.dat d 3
	./ex17 db.dat l
	./ex17 db.dat g 2
	rm -f ex17
	rm -f db.dat

test:
	make ex18
	./ex18 4 3 1 5 6
	rm -f ex18
