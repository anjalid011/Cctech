set xrange [-1:4]
set yrange [7:15]
set pointsize 1.5
plot '-' using 1:2 with lines title 'Line: y = 4x + 5', \
     '-' using 1:2 with points pt 7 ps 1.5 title 'Points'
-1 1
-0.5 3
0 5
0.5 7
1 9
1.5 11
2 13
2.5 15
3 17
3.5 19
4 21
e
1.11111 9.44444
1.22222 9.88889
1.33333 10.3333
1.44444 10.7778
1.55556 11.2222
1.66667 11.6667
1.77778 12.1111
1.88889 12.5556
e
