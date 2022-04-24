set term png
set output "../out/transp-hist-1-0.png"
set style fill solid 1.0
set title "Distancia de Pilha (Total 279 # 40 Media 6.97) - Fase  1 - ID 0"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:21] "../out/transp-hist-1-0.gpdat" u 3:4 w boxes t ""
