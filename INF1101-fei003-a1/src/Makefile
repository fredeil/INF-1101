## Author: Steffen Viken Valvaag <steffenv@cs.uit.no> 
LIST_SRC=linkedlist.c
SET_SRC=set_list.c
SPAMFILTER_SRC=spamfilter.c common.c $(LIST_SRC) $(SET_SRC)
NUMBERS_SRC=numbers.c common.c $(LIST_SRC) $(SET_SRC)
ASSERT_SRC=assert_set.c common.c $(LIST_SRC) $(SET_SRC)
HEADERS=common.h list.h set.h

all: spamfilter numbers

spamfilter: $(SPAMFILTER_SRC) $(HEADERS) Makefile
	gcc -o $@ $(SPAMFILTER_SRC) -ggdb

numbers: $(NUMBERS_SRC) $(HEADERS) Makefile
	gcc -o $@ $(NUMBERS_SRC) -ggdb

assert: $(ASSERT_SRC) $(HEADERS) Makefile
	gcc -o $@ $(ASSERT_SRC) -ggdb

clean:
	rm -f *~ *.o *.exe spamfilter numbers assert
