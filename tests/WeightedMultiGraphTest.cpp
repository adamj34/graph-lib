#include <catch2/catch_test_macros.hpp>
#include "graph_repr/WeightedMultiGraph.hpp"

TEST_CASE("WeightedMultiGraph initializes correctly", "[WeightedMultiGraph]") {
    gralph::graph::WeightedMultiGraph graph{5, 5};
    REQUIRE(graph.get_all_vertices().size() == 5);
    REQUIRE(graph.get_all_edges().size() == 0);
}

TEST_CASE("WeightedMultiGraph builds edges correctly", "[WeightedMultiGraph]") {
    gralph::graph::WeightedMultiGraph graph(5, 5);
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 2},
        {0, 3, 3},
        {3, 2, 4},
        {1, 2, 8},
        {1, 4, 1},
    };
    graph.build_edges(coords_tuples);

    REQUIRE(graph.get_all_edges().size() == 10);
    REQUIRE(graph.check_edge_weight({0, 1}) == std::unordered_set<int>{2});
    REQUIRE(graph.check_edge_weight({0, 3}) == std::unordered_set<int>{3});
    REQUIRE(graph.check_edge_weight({3, 2}) == std::unordered_set<int>{4});
    REQUIRE(graph.check_edge_weight({1, 2}) == std::unordered_set<int>{8});
    REQUIRE(graph.check_edge_weight({1, 4}) == std::unordered_set<int>{1});
}

TEST_CASE("WeightedMultiGraph adds and deletes vertices correctly", "[WeightedMultiGraph]") {
    gralph::graph::WeightedMultiGraph graph{5, 5};
    graph.add_vertex();
    REQUIRE(graph.get_all_vertices().size() == 6);
    REQUIRE(graph.get_all_edges().size() == 0);

    graph.delete_vertex(0);
    REQUIRE(graph.get_all_vertices().size() == 5);
    REQUIRE(graph.get_all_edges().size() == 0);
}

TEST_CASE("WeightedMultiGraph adds and deletes edges correctly", "[WeightedMultiGraph]") {
    gralph::graph::WeightedMultiGraph graph(5, 5);
    graph.add_edge({0, 1, 2});
    graph.add_edge({0, 3, 3});
    graph.add_edge({3, 2, 4});
    graph.add_edge({1, 2, 8});
    graph.add_edge({1, 4, 1});

    REQUIRE(graph.get_all_edges().size() == 10);
    REQUIRE(graph.check_edge_weight({0, 1}) == std::unordered_set<int>{2});
    REQUIRE(graph.check_edge_weight({0, 3}) == std::unordered_set<int>{3});
    REQUIRE(graph.check_edge_weight({3, 2}) == std::unordered_set<int>{4});
    REQUIRE(graph.check_edge_weight({1, 2}) == std::unordered_set<int>{8});
    REQUIRE(graph.check_edge_weight({1, 4}) == std::unordered_set<int>{1});

    graph.delete_edge({0, 1}, 2);
    graph.delete_edge({0, 3}, 3);
    REQUIRE(graph.get_all_edges().size() == 6);
    REQUIRE(graph.check_edge_weight({0, 1}) == std::unordered_set<int>{});
    REQUIRE(graph.check_edge_weight({0, 3}) == std::unordered_set<int>{});
}

TEST_CASE("WeightedMultiGraph checks if graph is Eulerian correctly", "[WeightedMultiGraph]") {
    gralph::graph::WeightedMultiGraph graph(5, 5);
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 2},
        {0, 3, 3},
        {3, 2, 4},
        {1, 2, 8},
        {1, 4, 1},
    };
    graph.build_edges(coords_tuples);

    REQUIRE(graph.is_eulerian() == false);

    graph.add_edge({1, 4, 5});
    REQUIRE(graph.is_eulerian() == true);
}

TEST_CASE("WeightedMultiGraph checks if graph is semi-Eulerian correctly", "[WeightedMultiGraph]") {
    gralph::graph::WeightedMultiGraph graph(5, 5);
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 2},
        {0, 3, 3},
        {3, 2, 4},
        {1, 2, 8},
        {1, 4, 1},
    };
    graph.build_edges(coords_tuples);

    REQUIRE(graph.is_semi_eulerian() == true);

    graph.add_edge({2, 4, 5});
    REQUIRE(graph.is_semi_eulerian() == true);
}
