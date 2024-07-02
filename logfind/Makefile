CFLAGS=-Wall -g
logfind : logfind_main.o logfind.o
	cc -o logfind logfind_main.o logfind.o

logfind_main.o : logfind_main.c logfind.h dbg.h
	cc -c logfind_main.c

logfind.o : logfind.c logfind.h dbg.h
	cc -c logfind.c

clean : 
	rm -f logfind logfind_main.o logfind.o
all :
	make logfind_main
