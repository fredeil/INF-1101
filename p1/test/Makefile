all: tests

tests: $(TEST_SRC) $(HEADERS) Makefile
	gcc tests.c ../linkedlist.c ../common.c lib/tap.c -o test
	./test > ./test.txt
	grep -w 'ok\|error\|failed\|tests' test.txt

clean:
	rm -f *~ *.o *.exe *.out test *.txt