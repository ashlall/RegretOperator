set term postscript eps color
set output "plot-NBA-varyK.eps"
set xlabel 'K'
set ylabel 'Maximum regret ratio'
set key left top
set key box
set size .5,.5
set yrange [0:*]
set format y "%2.0f%%"
plot "Data/nba-varyK-NBA-db4" using 1:(100*$2) title 'Cube' with linespoints lw 2, "Data/nba-varyK-NBA-db4" using 1:(100*$3) title 'Cube LIB' with linespoints lw 2, "Data/nba-varyK-NBA-db4" using 1:(100*$4) title 'Sphere' with linespoints lw 2, "Data/nba-varyK-NBA-db4" using 1:(100*$5) title 'Sphere LIB' with linespoints lw 2, "Data/nba-varyK-NBA-db4" using 1:(100*$6) title 'Imp Greedy' with linespoints lw 2, "Data/nba-varyK-NBA-db4" using 1:(100*$7) title 'Imp Greedy LIB' with linespoints lw 2
