set output "plot.png"
set terminal pngcairo enhanced font "Times New Roman,26.0" size 1500,1100
# set term pngcairo size 1024,768
# set size ratio 1

set title "D(N)"
set xlabel "N / 10^3"
set ylabel "D"
set grid

set yrange [1.25:1.75]
set xrange [-1:18]

set format y '%.2f'

# set style line 12 lc rgb 'black' lt 1 lw 2
# set style line 13 lc rgb 'gold' lt 1 lw 1
# set grid xtics ytics mxtics mytics ls 12, ls 13
set style line 12 lc rgb 'grey90' lt 1 lw 2
set style line 13 lc rgb 'grey90' lt 0 lw 2
set grid xtics ytics mxtics mytics ls 12, ls 13

set border 31 lw 2.0

set xtics -1,1,18
set ytics 1.25,0.05,1.75

plot file using ($1/1000):($2) \
  with linespoints \
  linetype 1 \
  linewidth 3 \
  pointtype 7 \
  pointsize 1.5 \
  title "D(N)"

# set xrange [-0:16000]
# plot 'out_0/3384.dat' with linespoints title "", \
#      'out_0/8982.dat' with linespoints title "", \
#      'out_0/86440.dat' with linespoints title "", \
#      'out_3/2766.dat' with linespoints title ""
