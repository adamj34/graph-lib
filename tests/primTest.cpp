#include <catch2/catch_test_macros.hpp>
#include "graph_repr/WeightedGraph.hpp"
#include "algorithms/mst/prim.hpp"

TEST_CASE( "Prim's algorithm finds the correct minimal spanning tree", "[PrimTest]" ) {
    gralph::graph::WeightedGraph graph{5, 5};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 2},
        {0, 3, 3},
        {3, 2, 4},
        {1, 2, 8},
        {1, 4, 1},
    };
    graph.build_edges(coords_tuples);

    gralph::algos::prim prim_algo{graph};
    std::map<int, std::vector<int>> mst = { prim_algo.get_mst() };

    SECTION("Number of edges in MST is correct") {
        int num_edges = 0;
        for (const auto& [vertex, neighbors] : mst) {
            num_edges += ssize(neighbors);
        }
        REQUIRE(num_edges == 4);
    }

    SECTION("MST has the correct edges") {
        std::map<int, std::vector<int>> expected_mst = {
            {0, {1, 3}},
            {1, {4}},
            {2, {}},
            {3, {2}},
            {4, {}},
        };
        REQUIRE(mst == expected_mst);
    }

    SECTION("MST has the correct cost") {
        REQUIRE(prim_algo.get_cost() == 10);
    }
}

TEST_CASE( "Prim's algorithm handles a graph with no edges", "[PrimTest]" ) {
    gralph::graph::WeightedGraph graph{5, 0}; // 5 vertices, 0 edges

    gralph::algos::prim prim_algo{graph};
    std::map<int, std::vector<int>> mst = { prim_algo.get_mst() };

    SECTION("Number of edges in MST is correct") {
        int num_edges = 0;
        for (const auto& [vertex, neighbors] : mst) {
            num_edges += ssize(neighbors);
        }
        REQUIRE(num_edges == 0);
    }

    SECTION("MST has no edges") {
        std::map<int, std::vector<int>> expected_mst = {
            {0, {}},
            {1, {}},
            {2, {}},
            {3, {}},
            {4, {}},
        };
        REQUIRE(mst == expected_mst);
    }

    SECTION("MST has no cost") {
        REQUIRE(prim_algo.get_cost() == 0);
    }
}
