set term png
set output "../out/mem/sum/-acesso-2.png"
set title "Grafico de acesso - ID 2"
set xlabel "Acesso"
set ylabel "Endereco"
plot "../out/mem/sum/-acesso-0-2.gpdat" u 2:4 w points t "L", "../out/mem/sum/-acesso-1-2.gpdat" u 2:4 w points t "E"
