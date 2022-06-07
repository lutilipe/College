set term png
set output "/tmp/pokerest/pokerest-hist-0-2.png"
set style fill solid 1.0
set title "Distancia de Pilha (Total 994 # 170 Media 5.85) - Fase  0 - ID 2"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:18] "/tmp/pokerest/pokerest-hist-0-2.gpdat" u 3:4 w boxes t ""
