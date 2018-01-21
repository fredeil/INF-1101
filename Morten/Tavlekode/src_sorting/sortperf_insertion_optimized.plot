set terminal pdf
set output "sortperf_insertion_optimized.pdf"
set autoscale
set xlabel "# elements"
set ylabel "Time (microseconds)"
set key left
plot "insertion_optimized_random.data" w linespoints lw 2 t "Insertion optimized sort (RANDOM)", "insertion_optimized_sorted.data" w linespoints lw 2 t "Insertion optimized sort (SORTED)", "insertion_optimized_reversed.data" w linespoints lw 2 t "Insertion optimized sort (REVERSED)"
