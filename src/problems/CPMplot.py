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
try:
    pos = nx.planar_layout(G)  # This only works for planar graphs
except nx.NetworkXException:
    pos = nx.spring_layout(G, iterations=300)  # Use a high iterations value to approximate a layout with minimal edge crossings

nx.draw(G, pos, with_labels=True, arrows=True, node_color='skyblue', node_size=700, edge_color='gray')

# Create a label for each node that includes all the attributes
labels = {node: f"es={data['es']},\n ef={data['ef']},\n ls={data['ls']},\n lf={data['lf']},\n t={data['time']}" for node, data in G.nodes(data=True)}

# Draw the node attributes
label_pos = {k: (v[0], v[1]-0.05) for k, v in pos.items()}  # Adjust the second value to move the labels further from the nodes
nx.draw_networkx_labels(G, pos=label_pos, labels=labels)

plt.title('CPM')
plt.show()
