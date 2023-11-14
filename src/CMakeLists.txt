# Add the source files for the library
add_library(gralph
            algorithms/mst/prim.cpp
            graph_repr/WeightedGraph.cpp
            algorithms/shortest_path/dijkstra.cpp
            algorithms/search/dfs.cpp
            # algorithms/search/bfs.cpp
            algorithms/euler/fleuryCycle.cpp
            algorithms/euler/fleuryPath.cpp)

