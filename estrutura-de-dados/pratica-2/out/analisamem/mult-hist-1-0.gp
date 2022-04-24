set term png
set output "../out/mult-hist-1-0.png"
set style fill solid 1.0
set title "Distancia de Pilha (Total 1125 # 150 Media 7.50) - Fase  1 - ID 0"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:26] "../out/mult-hist-1-0.gpdat" u 3:4 w boxes t ""
