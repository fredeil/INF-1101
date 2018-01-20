set terminal pdf
set output "sortperf_reversed.pdf"
set autoscale
set xlabel "# elements"
set ylabel "Time (microseconds)"
set key left
plot "bubble_reversed.data" w linespoints lw 2 t "Bubblesort (REVERSED)", "selection_reversed.data" w linespoints lw 2 t "Selection sort (REVERSED)", "insertion_reversed.data" w linespoints lw 2 t "Insertion sort (REVERSED)", "insertion_optimized_reversed.data" w linespoints lw 2 t "Insertion sort optimized (REVERSED)"
