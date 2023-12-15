import networkx as nx
import matplotlib.pyplot as plt

# Read the graph from the file
G = nx.read_edgelist('graph.txt', create_using=nx.DiGraph(), nodetype=int)

# Read the node attributes from the file
with open('nodes.txt') as f:
    for line in f:
        node, es, ef, ls, lf, weight = map(int, line.split())
        G.nodes[node]['es'] = es
        G.nodes[node]['ef'] = ef
        G.nodes[node]['ls'] = ls
        G.nodes[node]['lf'] = lf
        G.nodes[node]['time'] = weight

# Draw the graph
pos = nx.spring_layout(G)
nx.draw(G, pos, with_labels=True, arrows=True)

# Create a label for each node that includes all the attributes
labels = {node: f"es={data['es']},\n ef={data['ef']},\n ls={data['ls']},\n lf={data['lf']},\n t={data['time']}" for node, data in G.nodes(data=True)}

# Draw the node attributes
nx.draw_networkx_labels(G, pos, labels=labels, verticalalignment='bottom')

plt.show()
