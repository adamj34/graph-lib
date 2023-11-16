#include <catch2/catch_test_macros.hpp>
#include "graph_repr/WeightedGraph.hpp"
#include "algorithms/shortest_path/dijkstra.hpp"

TEST_CASE( "Dijkstra's algorithm finds the correct shortest path (G4G)", "[DijkstraTest]" ) {
    gralph::graph::WeightedGraph graph{9, 28};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 4},
        {0, 7, 8},
        {1, 0, 4},
        {1, 2, 8},
        {1, 7, 11},
        {2, 1, 8},
        {2, 3, 7},
        {2, 5, 4},
        {2, 8, 2},
        {3, 2, 7},
        {3, 4, 9},
        {3, 5, 14},
        {4, 3, 9},
        {4, 5, 10},
        {5, 2, 4},
        {5, 3, 14},
        {5, 4, 10},
        {5, 6, 2},
        {6, 5, 2},
        {6, 7, 1},
        {6, 8, 6},
        {7, 0, 8},
        {7, 1, 11},
        {7, 6, 1},
        {7, 8, 7},
        {8, 2, 2},
        {8, 6, 6},
        {8, 7, 7}
    };

    graph.build_edges(coords_tuples);

    gralph::algos::dijkstra dijkstra{graph};
    dijkstra.solve(0);
    std::unordered_map<int, int> shortest_paths = dijkstra.get_shortest_path_costs();

    SECTION("Shortest path to each vertex is correct") {
        std::unordered_map<int, int> expected_shortest_paths = {
            {0, 0},
            {1, 4},
            {2, 12},
            {3, 19},
            {4, 21},
            {5, 11},
            {6, 9},
            {7, 8},
            {8, 14}
        };
        REQUIRE(shortest_paths == expected_shortest_paths);
    }
}

TEST_CASE( "Dijkstra's algorithm finds the correct shortest path", "[DijkstraTest]" ) {
    gralph::graph::WeightedGraph graph{5, 6};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 2},
        {0, 3, 3},
        {3, 2, 4},
        {1, 2, 8},
        {1, 4, 1},
        {3, 4, 5}
    };
    graph.build_edges(coords_tuples);

    gralph::algos::dijkstra dijkstra{graph};
    dijkstra.solve(0);
    std::unordered_map<int, int> shortest_paths = dijkstra.get_shortest_path_costs();

    SECTION("Shortest path to each vertex is correct") {
        std::unordered_map<int, int> expected_shortest_paths = {
            {0, 0},
            {1, 2},
            {2, 7},
            {3, 3},
            {4, 3}
        };
        REQUIRE(shortest_paths == expected_shortest_paths);
    }
}

TEST_CASE( "Dijkstra's algorithm reconstructs the correct shortest path", "[DijkstraTest]" ) {
    gralph::graph::WeightedGraph graph{5, 6};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 2},
        {0, 3, 3},
        {3, 2, 4},
        {1, 2, 8},
        {1, 4, 1},
        {3, 4, 5}
    };
    graph.build_edges(coords_tuples);

    gralph::algos::dijkstra dijkstra{graph};
    dijkstra.solve(0);

    SECTION("Shortest path from source to each vertex is correct") {
        std::vector<std::pair<int, int>> expected_path_to_1 = {{0, 1}};
        std::vector<std::pair<int, int>> expected_path_to_2 = {{0, 3}, {3, 2}};
        std::vector<std::pair<int, int>> expected_path_to_3 = {{0, 3}};
        std::vector<std::pair<int, int>> expected_path_to_4 = {{0, 1}, {1, 4}};

        REQUIRE(dijkstra.get_shortest_path(1) == expected_path_to_1);
        REQUIRE(dijkstra.get_shortest_path(2) == expected_path_to_2);
        REQUIRE(dijkstra.get_shortest_path(3) == expected_path_to_3);
        REQUIRE(dijkstra.get_shortest_path(4) == expected_path_to_4);
    }
}
