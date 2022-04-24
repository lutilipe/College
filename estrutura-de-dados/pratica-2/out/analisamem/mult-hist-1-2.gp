set term png
set output "../out/mult-hist-1-2.png"
set style fill solid 1.0
set title "Distancia de Pilha (Total 1350 # 175 Media 7.71) - Fase  1 - ID 2"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:26] "../out/mult-hist-1-2.gpdat" u 3:4 w boxes t ""
