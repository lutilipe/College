set term png
set output "../out/soma-distp-1.png"
set title "Evolucao Distancia de Pilha - ID 1"
set xlabel "Acesso"
set ylabel "Distancia de Pilha"
plot "../out/soma-acesso-2-1.gpdat" u 2:5 w impulses t ""
