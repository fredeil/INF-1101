LIST_SRC=linkedlist.c
SORTWORDS_SRC=sortwords.c common.c $(LIST_SRC)
REVERSEWORDS_SRC=reversewords.c common.c $(LIST_SRC)
HEADERS=common.h list.h test/lib/tap.h

all: tests sortwords reversewords 

sortwords: $(SORTWORDS_SRC) $(HEADERS) Makefile
	gcc -o $@ $(SORTWORDS_SRC)

reversewords: $(REVERSEWORDS_SRC) $(HEADERS) Makefile
	gcc -o $@ $(REVERSEWORDS_SRC)

tests: Makefile
	cd test && make -s --no-print-directory

clean:
	rm -f  *.txt *~ *.o *.exe *.out sortwords reversewords ./test/test ./test/*.txt