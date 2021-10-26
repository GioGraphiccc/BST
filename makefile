bstsort: bstsort.o
	gcc bstsort.c -o bstsort

bstsort.o: bstsort.h
	gcc -c bstsort.c 

clean: 
	rm *.o bstsort



