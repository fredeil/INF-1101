all: tests

tests: $(TEST_SRC) $(HEADERS) Makefile
	gcc tests.c ../linkedlist.c ../common.c lib/tap.c -o test

clean:
	rm -f *~ *.o *.exe *.out test