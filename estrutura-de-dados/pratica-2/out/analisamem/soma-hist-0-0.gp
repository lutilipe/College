set term png
set output "../out/soma-hist-0-0.png"
set style fill solid 1.0
set title "Distancia de Pilha (Total 500 # 45 Media 11.11) - Fase  0 - ID 0"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:26] "../out/soma-hist-0-0.gpdat" u 3:4 w boxes t ""
