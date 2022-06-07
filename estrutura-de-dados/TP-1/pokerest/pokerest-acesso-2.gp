set term png
set output "/tmp/pokerest/pokerest-acesso-2.png"
set title "Grafico de acesso - ID 2"
set xlabel "Acesso"
set ylabel "Endereco"
plot "/tmp/pokerest/pokerest-acesso-0-2.gpdat" u 2:4 w points t "L", "/tmp/pokerest/pokerest-acesso-1-2.gpdat" u 2:4 w points t "E"
