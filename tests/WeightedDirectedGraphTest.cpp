#include <catch2/catch_test_macros.hpp>
#include "graph_repr/WeightedDirectedGraph.hpp"

TEST_CASE("BuildEdges", "[WeightedDirectedGraph]") {
    gralph::graph::WeightedDirectedGraph graph(3, 0);
    std::vector<std::tuple<int, int, int>> edges = {{0, 1, 2}, {1, 2, 3}, {2, 0, 4}};
    graph.build_edges(edges);

    REQUIRE(graph.check_edge_weight({0, 1}) == 2);
    REQUIRE(graph.check_edge_weight({1, 2}) == 3);
    REQUIRE(graph.check_edge_weight({2, 0}) == 4);
}

TEST_CASE("GetVertexDeg", "[WeightedDirectedGraph]") {
    gralph::graph::WeightedDirectedGraph graph(4, 0);
    std::vector<std::tuple<int, int, int>> edges = {{0, 1, 2}, {1, 2, 3}, {2, 0, 4}, {3, 0, 1}};
    graph.build_edges(edges);

    REQUIRE(graph.get_vertex_deg(0) == 3);
    REQUIRE(graph.get_vertex_deg(1) == 2);
    REQUIRE(graph.get_vertex_deg(2) == 2);
    REQUIRE(graph.get_vertex_deg(3) == 1);
}

TEST_CASE("AddVertex", "[WeightedDirectedGraph]") {
    gralph::graph::WeightedDirectedGraph graph(3, 0);
    std::vector<std::tuple<int, int, int>> edges = {{0, 1, 2}, {1, 2, 3}, {2, 0, 4}};
    graph.build_edges(edges);

    graph.add_vertex();

    REQUIRE(graph.get_all_vertices().size() == 4);
    REQUIRE(graph.get_vertex_deg(3) == 0);
}

TEST_CASE("DeleteVertex", "[WeightedDirectedGraph]") {
    gralph::graph::WeightedDirectedGraph graph(4, 0);
    std::vector<std::tuple<int, int, int>> edges = {{0, 1, 2}, {1, 2, 3}, {2, 0, 4}, {3, 0, 1}};
    graph.build_edges(edges);

    graph.delete_vertex(2);

    REQUIRE(graph.get_all_vertices().size() == 3);
    REQUIRE(graph.get_vertex_deg(0) == 2);
    REQUIRE(graph.get_vertex_deg(1) == 1);
    REQUIRE(graph.get_vertex_deg(3) == 1);
}

TEST_CASE("AddEdge", "[WeightedDirectedGraph]") {
    gralph::graph::WeightedDirectedGraph graph(3, 0);
    std::vector<std::tuple<int, int, int>> edges = {{0, 1, 2}, {1, 2, 3}};
    graph.build_edges(edges);

    graph.add_edge({2, 0, 4});

    REQUIRE(graph.check_edge_weight({2, 0}) == 4);
    REQUIRE(graph.get_vertex_deg(2) == 2);
}

TEST_CASE("DeleteEdge", "[WeightedDirectedGraph]") {
    gralph::graph::WeightedDirectedGraph graph(3, 0);
    std::vector<std::tuple<int, int, int>> edges = {{0, 1, 2}, {1, 2, 3}, {2, 0, 4}};
    graph.build_edges(edges);

    graph.delete_edge({1, 2});

    REQUIRE(graph.check_edge_weight({1, 2}) == 0);
    REQUIRE(graph.get_vertex_deg(1) == 1);
}

TEST_CASE("IsEulerian", "[WeightedDirectedGraph]") {
    gralph::graph::WeightedDirectedGraph graph(4, 0);
    std::vector<std::tuple<int, int, int>> edges = {{0, 1, 2}, {1, 2, 3}, {2, 0, 4}, {3, 0, 1}};
    graph.build_edges(edges);

    REQUIRE_FALSE(graph.is_eulerian());

    graph.add_edge({1, 3, 5});

    REQUIRE(graph.is_eulerian());
}

TEST_CASE("IsSemiEulerian", "[WeightedDirectedGraph]") {
    gralph::graph::WeightedDirectedGraph graph(4, 0);
    std::vector<std::tuple<int, int, int>> edges = {{0, 1, 2}, {1, 2, 3}, {2, 0, 4}, {3, 0, 1}};
    graph.build_edges(edges);

    REQUIRE_FALSE(graph.is_semi_eulerian());

    graph.add_edge({1, 3, 5});

    REQUIRE(graph.is_semi_eulerian());
}

