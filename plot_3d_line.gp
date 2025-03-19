set parametric
set xrange [-10:10]
set yrange [-10:10]
set zrange [-10:10]
set xlabel 'X'
set ylabel 'Y'
set zlabel 'Z'
set title '3D Line Plot'
splot 2 + 3*t, 4 + 5*t, 6 + 7*t with lines title 'Line' 
