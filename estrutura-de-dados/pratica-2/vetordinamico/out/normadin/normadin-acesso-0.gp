set term postscript eps color 14
set output "./out/normadin/normadin-acesso-0.eps"
set title "Grafico de acesso - ID 0"
set xlabel "Acesso"
set ylabel "Endereco"
plot "./out/normadin/normadin-acesso-0-0.gpdat" u 2:4 w points t "L", "./out/normadin/normadin-acesso-1-0.gpdat" u 2:4 w points t "E"
