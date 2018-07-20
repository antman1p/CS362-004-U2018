CFLAGS = -Wall -fpic -coverage -lm -std=c99

randomtest: testme.c 
	gcc -o testme -g testme.c $(CFLAGS)
	echo "Random Testing testme() function"
	./testme >> randomtest.out
	gcov testme.c -b >> randomtest.out
	
clean:
	rm -rf *.o *.gcov *.gcda *.gcno *.so *.out testme