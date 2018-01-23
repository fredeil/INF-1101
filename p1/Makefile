LIST_SRC=linkedlist.c
SORTWORDS_SRC=sortwords.c common.c $(LIST_SRC)
REVERSEWORDS_SRC=reversewords.c common.c $(LIST_SRC)
HEADERS=common.h list.h test/lib/tap.h

all: sortwords reversewords tests

sortwords: $(SORTWORDS_SRC) $(HEADERS) Makefile
	gcc -o $@ $(SORTWORDS_SRC)

reversewords: $(REVERSEWORDS_SRC) $(HEADERS) Makefile
	gcc -o $@ $(REVERSEWORDS_SRC)

clean:
	rm -f *~ *.o *.exe *.out sortwords reversewords tests