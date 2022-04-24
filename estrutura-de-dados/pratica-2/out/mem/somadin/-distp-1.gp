set term png
set output "../out/mem/somadin/-distp-1.png"
set title "Evolucao Distancia de Pilha - ID 1"
set xlabel "Acesso"
set ylabel "Distancia de Pilha"
plot "../out/mem/somadin/-acesso-2-1.gpdat" u 2:5 w impulses t ""
