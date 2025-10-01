set terminal pngcairo size 900,900

set title "Расчётная кривая зависимости времени выполнения от длины вектора"
set xlabel "Длина вектора" 
set ylabel "Время (t, мс)"
set grid

set xrange [10000:10000000]

set output "plots/pictures/time-long.png"
plot "plots/files/time-long.dat" using 1:2 with linespoints
