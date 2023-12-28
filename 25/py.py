import networkx as nx
import math
import sys

G = nx.Graph()
for line in sys.stdin:
    line = line.strip()
    line = line.split(' ')
    line[0] = line[0][:-1]
    for n in line[1:]:
        G.add_edge(line[0], n)


G.remove_edges_from(nx.minimum_edge_cut(G))
print(math.prod([len(c) for c in nx.connected_components(G)]))

