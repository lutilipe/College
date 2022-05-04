set term png
set output "../out/mem/sum/-distp-2.png"
set title "Evolucao Distancia de Pilha - ID 2"
set xlabel "Acesso"
set ylabel "Distancia de Pilha"
plot "../out/mem/sum/-acesso-2-2.gpdat" u 2:5 w impulses t ""
