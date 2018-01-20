set terminal pdf
set output "sortperf_sorted.pdf"
set autoscale
set xlabel "# elements"
set ylabel "Time (microseconds)"
set key left
plot "bubble_sorted.data" w linespoints lw 2 t "Bubblesort (SORTED)", "selection_sorted.data" w linespoints lw 2 t "Selection sort (SORTED)", "insertion_sorted.data" w linespoints lw 2 t "Insertion sort (SORTED)", "insertion_optimized_sorted.data" w linespoints lw 2 t "Insertion sort optimized (SORTED)"
