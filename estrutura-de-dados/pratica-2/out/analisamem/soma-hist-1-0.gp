set term png
set output "../out/soma-hist-1-0.png"
set style fill solid 1.0
set title "Distancia de Pilha (Total 400 # 40 Media 10.00) - Fase  1 - ID 0"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:21] "../out/soma-hist-1-0.gpdat" u 3:4 w boxes t ""
