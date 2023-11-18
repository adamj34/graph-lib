#include <catch2/catch_test_macros.hpp>
#include "graph_repr/WeightedGraph.hpp"
#include "algorithms/mst/kruskal.hpp"

TEST_CASE("Kruskal's algorithm finds minimum spanning tree in a connected graph", "[kruskal]") {
    gralph::graph::WeightedGraph graph{5, 5};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 1},
        {1, 2, 2},
        {2, 3, 3},
        {3, 4, 4},
        {4, 0, 5},
    };
    graph.build_edges(coords_tuples);

    gralph::algos::kruskal kruskal_algo{graph};
    kruskal_algo.solve();
    std::map<int, std::vector<int>> mst = kruskal_algo.get_mst();
    int cost = kruskal_algo.get_cost();

    SECTION("Kruskal's algorithm finds minimum spanning tree in a connected graph") {
        std::map<int, std::vector<int>> expected_mst = {
            {0, {1}},
            {1, {2}},
            {2, {3}},
            {3, {4}},
        };
        int expected_cost = 10;
        REQUIRE(mst == expected_mst);
        REQUIRE(cost == expected_cost);
    }
}

TEST_CASE("Kruskal's algorithm handles a graph with multiple connected components (1)", "[kruskal]") {
    gralph::graph::WeightedGraph graph{6, 7};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 1},
        {1, 2, 2},
        {2, 0, 3},
        {3, 4, 4},
        {4, 5, 5},
        {4, 1, 6},
        {5, 3, 2}
    };
    graph.build_edges(coords_tuples);

    gralph::algos::kruskal kruskal_algo{graph};
    kruskal_algo.solve();
    std::map<int, std::vector<int>> mst = kruskal_algo.get_mst();
    int cost = kruskal_algo.get_cost();

    SECTION("Kruskal's algorithm handles a graph with multiple connected components") {
        std::map<int, std::vector<int>> expected_mst = {
            {0, {1}},
            {1, {2, 4}},
            {3, {5, 4}},
        };
        int expected_cost = 15;
        REQUIRE(mst == expected_mst);
        REQUIRE(cost == expected_cost);
    }
}

TEST_CASE("Kruskal's algorithm handles a graph with multiple connected components (2)", "[kruskal]") {
    gralph::graph::WeightedGraph graph{5, 5};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 2},
        {0, 3, 3},
        {3, 2, 4},
        {1, 2, 8},
        {1, 4, 1},
    };
    graph.build_edges(coords_tuples);

    gralph::algos::kruskal kruskal_algo{graph};
    kruskal_algo.solve();
    std::map<int, std::vector<int>> mst = kruskal_algo.get_mst();
    int cost = kruskal_algo.get_cost();

    SECTION("Kruskal's algorithm handles a graph with multiple connected components") {
        std::map<int, std::vector<int>> expected_mst = {
            {0, {1, 3}},
            {1, {4}},
            {2, {3}},
        };
        int expected_cost = 10;
        REQUIRE(mst == expected_mst);
        REQUIRE(cost == expected_cost);
    }
}

TEST_CASE("Kruskal's algorithm handles an empty graph", "[kruskal]") {
    gralph::graph::WeightedGraph graph{0, 0};

    gralph::algos::kruskal kruskal_algo{graph};
    kruskal_algo.solve();
    std::map<int, std::vector<int>> mst = kruskal_algo.get_mst();
    int cost = kruskal_algo.get_cost();

    SECTION("Kruskal's algorithm handles an empty graph") {
        std::map<int, std::vector<int>> expected_mst = {};
        int expected_cost = 0;
        REQUIRE(mst == expected_mst);
        REQUIRE(cost == expected_cost);
    }
}
