set term png
set output "../out/soma-distp-2.png"
set title "Evolucao Distancia de Pilha - ID 2"
set xlabel "Acesso"
set ylabel "Distancia de Pilha"
plot "../out/soma-acesso-2-2.gpdat" u 2:5 w impulses t ""
