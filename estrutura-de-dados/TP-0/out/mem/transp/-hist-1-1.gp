set term png
set output "../out/mem/transp/-hist-1-1.png"
set style fill solid 1.0
set title "Distancia de Pilha (Total 525 # 75 Media 7.00) - Fase  1 - ID 1"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:26] "../out/mem/transp/-hist-1-1.gpdat" u 3:4 w boxes t ""
