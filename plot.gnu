# Usage:
# 
# gnuplot -e "file='<path>'" plot.gnu

set output "plot.png"
set terminal pngcairo enhanced font "Times New Roman,26.0" size 1500,1100

set grid
set style line 12 lc rgb 'grey90' lt 1 lw 2
set style line 13 lc rgb 'grey90' lt 0 lw 2
set grid xtics ytics mxtics mytics ls 12, ls 13
set border 31 lw 2.0

# Fractal dimension
# 
# set title "D(N)"
# set xlabel "N / 10^3"
# set ylabel "D"
# set format y '%.2f'
# set yrange [1.25:1.75]
# set xrange [-1:18]
# set xtics -1,1,18
# set ytics 1.25,0.05,1.75
# plot file using ($1/1000):($2) \
#   with linespoints \
#   linetype 1 \
#   linewidth 3 \
#   pointtype 7 \
#   pointsize 1.5 \
#   title "D(N)"

# Performance
#
set title "N_{steps/s}(N_{threads})"
set xlabel "N_{threads}"
set ylabel "N_{steps/s}"
set format y '%.0f'
set xrange [0:13]
set xtics 0,1,13
plot file using ($1):($2) \
  with linespoints \
  linetype 1 \
  linewidth 3 \
  pointtype 7 \
  pointsize 1.5 \
  title "N_{steps/s}(N_{threads})"
