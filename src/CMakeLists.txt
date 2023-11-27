# Add the source files for the library
add_library(gralph
            graph_repr/WeightedGraph.cpp
            graph_repr/WeightedMultiGraph.cpp
            algorithms/mst/prim.cpp
            algorithms/shortest_path/dijkstra.cpp
            algorithms/search/dfs.cpp
            algorithms/search/bfs.cpp
            algorithms/euler/fleuryCycle.cpp
            algorithms/mst/kruskal.cpp
            problems/chinesePostman.cpp
            problems/travelingSalesman.cpp
            data_structures/disjoinedSet.cpp
)

