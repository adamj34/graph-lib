# Add the source files for the library
add_library(gralph
            graph_repr/WeightedGraph.cpp
            graph_repr/WeightedMultiGraph.cpp
            algorithms/mst/prim.cpp
            algorithms/shortest_path/dijkstra.cpp
            algorithms/search/dfs.cpp
            algorithms/search/bfs.cpp
            algorithms/euler/fleuryCycle.cpp
            problems/chinesePostman.cpp
            algorithms/mst/kruskal.cpp
            data_structures/disjoinedSet.cpp
)

