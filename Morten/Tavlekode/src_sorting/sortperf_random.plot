set terminal pdf
set output "sortperf_random.pdf"
set autoscale
set xlabel "# elements"
set ylabel "Time (microseconds)"
set key left
plot "bubble_random.data" w linespoints lw 2 t "Bubblesort (RANDOM)", "selection_random.data" w linespoints lw 2 t "Selection sort (RANDOM)", "insertion_random.data" w linespoints lw 2 t "Insertion sort (RANDOM)", "insertion_optimized_random.data" w linespoints lw 2 t "Insertion sort optimized (RANDOM)"
