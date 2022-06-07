set term png
set output "/tmp/pokerest/pokerest-acesso-1.png"
set title "Grafico de acesso - ID 1"
set xlabel "Acesso"
set ylabel "Endereco"
plot "/tmp/pokerest/pokerest-acesso-0-1.gpdat" u 2:4 w points t "L", "/tmp/pokerest/pokerest-acesso-1-1.gpdat" u 2:4 w points t "E"
