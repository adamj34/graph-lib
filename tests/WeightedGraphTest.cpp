#include <catch2/catch_test_macros.hpp>
#include "graph_repr/WeightedGraph.hpp"


TEST_CASE( "WeightedGraph is correctly initialized", "[WeightedGraphTest]" ) {
    gralph::graph::WeightedGraph graph{5, 5};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 2},
        {0, 3, 3},
        {3, 2, 4},
        {1, 2, 8},
        {1, 4, 1},
    };
    graph.build_edges(coords_tuples);

    SECTION("Number of vertices and edges are correct") {
        REQUIRE(graph.get_edge_num() == 5);
        REQUIRE(graph.get_vertex_num() == 5);
    }

    SECTION("Graph matrix is initialized correctly") {
        std::map<int, std::vector<int>> expected_matrix = {
            {0, {0, 2, 0, 3, 0}},
            {1, {2, 0, 8, 0, 1}},
            {2, {0, 8, 0, 4, 0}},
            {3, {3, 0, 4, 0, 0}},
            {4, {0, 1, 0, 0, 0}},
        };
 
        REQUIRE(graph.get_graph() == expected_matrix);
    }
}

TEST_CASE( "WeightedGraph can add and delete vertices", "[WeightedGraphTest]" ) {
    gralph::graph::WeightedGraph graph{3, 2};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 2},
        {1, 2, 3},
    };
    graph.build_edges(coords_tuples);

    SECTION("Adding a vertex increases the number of vertices and adds a row and column to the matrix") {
        graph.add_vertex();
        REQUIRE(graph.get_vertex_num() == 4);
        REQUIRE(graph.get_edge_num() == 2);
        std::map<int, std::vector<int>> expected_matrix = {
            {0, {0, 2, 0, 0}},
            {1, {2, 0, 3, 0}},
            {2, {0, 3, 0, 0}},
            {3, {0, 0, 0, 0}},
        };
        REQUIRE(graph.get_graph() == expected_matrix);
    }

    SECTION("Deleting a vertex decreases the number of vertices and removes the corresponding row and column from the matrix") {
        graph.delete_vertex(1);
        REQUIRE(graph.get_vertex_num() == 2);
        REQUIRE(graph.get_edge_num() == 0);
        std::map<int, std::vector<int>> expected_matrix = {
            {0, {0, 0}},
            {2, {0, 0}},
        };
        REQUIRE(graph.get_graph() == expected_matrix);
    }
}

TEST_CASE( "WeightedGraph can get vertex degree", "[WeightedGraphTest]" ) {
    gralph::graph::WeightedGraph graph{4, 4};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 2},
        {0, 2, 3},
        {1, 2, 4},
        {2, 3, 5},
    };
    graph.build_edges(coords_tuples);
    
    SECTION("Vertex degree is calculated correctly for a node with edges") {
        REQUIRE(graph.get_vertex_deg(0) == 2);
        REQUIRE(graph.get_vertex_deg(1) == 2);
        REQUIRE(graph.get_vertex_deg(2) == 3);
        REQUIRE(graph.get_vertex_deg(3) == 1);
    }

    SECTION("Vertex degree is 0 for a node without edges") {
        graph.add_vertex();
        REQUIRE(graph.get_vertex_deg(4) == 0);
    }
}

TEST_CASE("WeightedGraph delete_vertex works correctly", "[WeightedGraphTest]") {
    gralph::graph::WeightedGraph graph{5, 5};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 2},
        {0, 3, 3},
        {3, 2, 4},
        {1, 2, 8},
        {1, 4, 1},
    };
    graph.build_edges(coords_tuples);

    graph.delete_vertex(1);

    SECTION("Number of vertices and edges are updated correctly after deletion") {
        REQUIRE(graph.get_edge_num() == 2);
        REQUIRE(graph.get_vertex_num() == 4);
    }

    SECTION("Graph matrix is updated correctly after deletion") {
        std::map<int, std::vector<int>> expected_matrix = {
            {0, {0, 0, 3, 0}},
            {2, {0, 0, 4, 0}},
            {3, {3, 4, 0, 0}},
            {4, {0, 0, 0, 0}},
        };
 
        REQUIRE(graph.get_graph() == expected_matrix);
    }
}

TEST_CASE("WeightedGraph get_vertex_deg works correctly", "[WeightedGraphTest]") {
    gralph::graph::WeightedGraph graph{5, 5};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 2},
        {0, 3, 3},
        {3, 2, 4},
        {1, 2, 8},
        {1, 4, 1},
    };
    graph.build_edges(coords_tuples);

    SECTION("Degree of vertices are calculated correctly") {
        REQUIRE(graph.get_vertex_deg(0) == 2);
        REQUIRE(graph.get_vertex_deg(1) == 3);
        REQUIRE(graph.get_vertex_deg(2) == 2);
        REQUIRE(graph.get_vertex_deg(3) == 2);
        REQUIRE(graph.get_vertex_deg(4) == 1);
    }
}
