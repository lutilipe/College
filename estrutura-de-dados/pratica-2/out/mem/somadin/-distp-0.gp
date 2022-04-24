set term png
set output "../out/mem/somadin/-distp-0.png"
set title "Evolucao Distancia de Pilha - ID 0"
set xlabel "Acesso"
set ylabel "Distancia de Pilha"
plot "../out/mem/somadin/-acesso-2-0.gpdat" u 2:5 w impulses t ""
