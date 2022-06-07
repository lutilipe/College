set term png
set output "/tmp/pokerest/pokerest-hist-0-1.png"
set style fill solid 1.0
set title "Distancia de Pilha (Total 940 # 193 Media 4.87) - Fase  0 - ID 1"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:17] "/tmp/pokerest/pokerest-hist-0-1.gpdat" u 3:4 w boxes t ""
