set terminal pdf
set output "sortperf_all.pdf"
set autoscale
set xlabel "# elements"
set ylabel "Time (microseconds)"
set key left
plot "bubble_random.data" w linespoints lw 2 t "Bubblesort (RANDOM)", "selection_random.data" w linespoints lw 2 t "Selection sort (RANDOM)", "insertion_random.data" w linespoints lw 2 t "Insertion sort (RANDOM)", "insertion_optimized_random.data" w linespoints lw 2 t "Insertion sort optimized (RANDOM)", "bubble_sorted.data" w linespoints lw 2 t "Bubblesort (SORTED)", "selection_sorted.data" w linespoints lw 2 t "Selection sort (SORTED)", "insertion_sorted.data" w linespoints lw 2 t "Insertion sort (SORTED)", "insertion_optimized_sorted.data" w linespoints lw 2 t "Insertion sort optimized (SORTED)", "bubble_reversed.data" w linespoints lw 2 t "Bubblesort (REVERSED)", "selection_reversed.data" w linespoints lw 2 t "Selection sort (REVERSED)", "insertion_reversed.data" w linespoints lw 2 t "Insertion sort (REVERSED)", "insertion_optimized_reversed.data" w linespoints lw 2 t "Insertion sort optimized (REVERSED)"

