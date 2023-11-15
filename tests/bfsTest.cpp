#include <catch2/catch_test_macros.hpp>
#include "graph_repr/WeightedGraph.hpp"
#include "algorithms/search/bfs.hpp"

TEST_CASE("BFS finds all vertices in a connected graph", "[bfs]") {
    gralph::graph::WeightedGraph graph{5, 5};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 1},
        {1, 2, 1},
        {2, 3, 1},
        {3, 4, 1},
        {4, 0, 1},
    };
    graph.build_edges(coords_tuples);

    gralph::search::bfs bfs_algo{graph, 0};
    std::unordered_set<int> visited_vertices = bfs_algo.get_visited();

    SECTION("BFS finds all vertices in a connected graph") {
        std::unordered_set<int> expected_vertices = {0, 1, 2, 3, 4};
        REQUIRE(visited_vertices == expected_vertices);
    }
}

TEST_CASE("BFS finds all vertices in a graph with multiple connected components", "[bfs]") {
    gralph::graph::WeightedGraph graph{6, 5};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 1},
        {1, 2, 1},
        {2, 0, 1},
        {3, 4, 1},
        {4, 5, 1},
    };
    graph.build_edges(coords_tuples);

    gralph::search::bfs bfs_algo{graph, 0};
    std::unordered_set<int> visited_vertices = bfs_algo.get_visited();

    SECTION("BFS finds all vertices in a graph with multiple connected components") {
        std::unordered_set<int> expected_vertices = {0, 1, 2};
        REQUIRE(visited_vertices == expected_vertices);
    }
}

TEST_CASE("BFS correctly handles a disconnected source vertex", "[bfs]") {
    gralph::graph::WeightedGraph graph{6, 5};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 1},
        {1, 2, 1},
        {2, 3, 1},
        {3, 4, 1},
        {4, 0, 1},
    };
    graph.build_edges(coords_tuples);

    gralph::search::bfs bfs_algo{graph, 5};
    std::unordered_set<int> visited_vertices = bfs_algo.get_visited();

    SECTION("BFS correctly handles a disconnected source vertex") {
        std::unordered_set<int> expected_vertices = {5};
        REQUIRE(visited_vertices == expected_vertices);
    }

}
