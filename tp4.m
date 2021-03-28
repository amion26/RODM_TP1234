load graph_tp4.txt
n = 400;
A = zeros(n,n);

for e = 1:size(graph_tp4,1)
    A(graph_tp4(e,1)+1,graph_tp4(e,2)+1) = 1;
    A(graph_tp4(e,2)+1,graph_tp4(e,1)+1) = 1;
end
g = graph(A);
%%% Affichage du graph complet (pas très lisible)
p = plot(g)
p.NodeColor = 'r';
layout(p,"force")

%%% Affiche les 2 premieres communautés
% h = subgraph(g,[1:100 101:200])
% H = plot(h)
% H.NodeColor = 'r';
% layout(H,"force")