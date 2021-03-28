import networkx as nx 
import matplotlib.pyplot as plt 


g = nx.read_edgelist('graph_tp4.txt',create_using=nx.graph(),nodetype=int)

print nx.info(g)

nx.draw(g)

plt.show()