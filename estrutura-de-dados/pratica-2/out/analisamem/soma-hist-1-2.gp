set term png
set output "../out/soma-hist-1-2.png"
set style fill solid 1.0
set title "Distancia de Pilha (Total 900 # 65 Media 13.85) - Fase  1 - ID 2"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:26] "../out/soma-hist-1-2.gpdat" u 3:4 w boxes t ""
