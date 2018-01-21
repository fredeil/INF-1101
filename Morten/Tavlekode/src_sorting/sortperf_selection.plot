set terminal pdf
set output "sortperf_selection.pdf"
set autoscale
set xlabel "# elements"
set ylabel "Time (microseconds)"
set key left
plot "selection_random.data" w linespoints lw 2 t "Selection sort (RANDOM)", "selection_sorted.data" w linespoints lw 2 t "Selection sort (SORTED)", "selection_reversed.data" w linespoints lw 2 t "Selection sort (REVERSED)"
