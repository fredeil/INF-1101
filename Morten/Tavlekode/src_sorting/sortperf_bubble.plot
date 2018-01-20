set terminal pdf
set output "sortperf_bubble.pdf"
set autoscale
set xlabel "# elements"
set ylabel "Time (microseconds)"
set key left
plot "bubble_random.data" w linespoints lw 2 t "Bubble sort (RANDOM)", "bubble_sorted.data" w linespoints lw 2 t "Bubble sort (SORTED)", "bubble_reversed.data" w linespoints lw 2 t "Bubble sort (REVERSED)"
