import matplotlib.pyplot as plt
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

# draw
#  nx.draw(G, with_labels=True)
plt.show()

G.remove_edge('cmj', 'qhd')
G.remove_edge('lnf', 'jll')
G.remove_edge('vtv', 'kkp')

print(math.prod([len(c) for c in nx.connected_components(G)]))

