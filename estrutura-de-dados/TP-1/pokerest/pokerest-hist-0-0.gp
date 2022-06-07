set term png
set output "/tmp/pokerest/pokerest-hist-0-0.png"
set style fill solid 1.0
set title "Distancia de Pilha (Total 675 # 138 Media 4.89) - Fase  0 - ID 0"
set xlabel "Distancia"
set ylabel "Frequencia"
plot [-1:19] "/tmp/pokerest/pokerest-hist-0-0.gpdat" u 3:4 w boxes t ""
