test: test.out
	./test.out --ascii

test.out: test/test.c Controller/traverse.ino
	gcc -o test.out test/test.c -lcriterion

.PHONY: test	
