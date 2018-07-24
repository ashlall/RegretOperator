set term postscript eps color
set output "plot-varyD1.eps"
set xlabel 'D'
set ylabel 'Maximum regret ratio'
set key left top
set key box
set size .5,.5
set xtic 1
set yrange [0:*]
set format y "%2.0f%%"
plot "varyD-e-N10000-k20" using 1:(100*$2) title 'Cube' with linespoints lw 2, "varyD-e-N10000-k20" using 1:(100*$3) title 'Cube LIB' with linespoints lw 2, "varyD-e-N10000-k20" using 1:(100*$4) title 'Sphere' with linespoints lw 2, "varyD-e-N10000-k20" using 1:(100*$5) title 'Sphere LIB' with linespoints lw 2, "varyD-e-N10000-k20" using 1:(100*$6) title 'Imp Greedy' with linespoints lw 2, "varyD-e-N10000-k20" using 1:(100*$7) title 'Imp Greedy LIB' with linespoints lw 2
