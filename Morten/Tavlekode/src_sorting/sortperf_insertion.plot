set terminal pdf
set output "sortperf_insertion.pdf"
set autoscale
set xlabel "# elements"
set ylabel "Time (microseconds)"
set key left
plot "insertion_random.data" w linespoints lw 2 t "Insertion sort (RANDOM)", "insertion_sorted.data" w linespoints lw 2 t "Insertion sort (SORTED)", "insertion_reversed.data" w linespoints lw 2 t "Insertion sort (REVERSED)"
