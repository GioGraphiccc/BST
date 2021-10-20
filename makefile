mainbst: mainbst.o bstsort.o
	gcc mainbst.c bstsort.c -o output

bstsort.o: bstsort.o bstsort.h
	gcc -c bstsort.c 



