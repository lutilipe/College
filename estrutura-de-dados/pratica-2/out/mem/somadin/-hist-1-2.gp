set term png
set output "../out/mem/somadin/-hist-1-2.png"
set style fill solid 1.0
set title "Distancia de Pilha (Total 400 # 60 Media 6.67) - Fase  1 - ID 2"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:21] "../out/mem/somadin/-hist-1-2.gpdat" u 3:4 w boxes t ""
