set term postscript eps color 14
set output "./out/somadin/somadin-acesso-2.eps"
set title "Grafico de acesso - ID 2"
set xlabel "Acesso"
set ylabel "Endereco"
plot "./out/somadin/somadin-acesso-0-2.gpdat" u 2:4 w points t "L", "./out/somadin/somadin-acesso-1-2.gpdat" u 2:4 w points t "E"
