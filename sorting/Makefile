assert_sort: assert_sort.c bubblesort.c insertion_sort.c selection_sort.c quicksort.c mergesort.c heapsort.c
	gcc $^ -O2 -g -lpthread -o $@ && ./$@

clean:
	rm -f assert_sort