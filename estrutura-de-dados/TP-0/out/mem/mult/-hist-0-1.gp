set term png
set output "../out/mem/mult/-hist-0-1.png"
set style fill solid 1.0
set title "Distancia de Pilha (Total 625 # 50 Media 12.50) - Fase  0 - ID 1"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:26] "../out/mem/mult/-hist-0-1.gpdat" u 3:4 w boxes t ""
