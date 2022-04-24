set term png
set output "../out/mem/internodin/-hist-0-2.png"
set style fill solid 1.0
set title "Distancia de Pilha (Total 0 # 20 Media 0.00) - Fase  0 - ID 2"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:1] "../out/mem/internodin/-hist-0-2.gpdat" u 3:4 w boxes t ""
