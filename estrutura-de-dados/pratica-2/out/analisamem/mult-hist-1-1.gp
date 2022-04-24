set term png
set output "../out/mult-hist-1-1.png"
set style fill solid 1.0
set title "Distancia de Pilha (Total 3025 # 150 Media 20.17) - Fase  1 - ID 1"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:26] "../out/mult-hist-1-1.gpdat" u 3:4 w boxes t ""
