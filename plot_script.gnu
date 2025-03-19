set title '3D Line using Parametric Equation'
set xlabel 'X-axis'
set ylabel 'Y-axis'
set zlabel 'Z-axis'
set grid
splot 'line_plot.dat' with linespoints title '3D Line' lc rgb 'blue' pt 7
