#include <catch2/catch_test_macros.hpp>
#include "graph_repr/WeightedGraph.hpp"
#include "algorithms/shortest_path/dijkstra.hpp"
#include "algorithms/euler/fleuryCycle.hpp"
#include "problems/chinesePostman.hpp"

#include <iostream>

TEST_CASE("Chinese Postman finds the optimal solution for an Eulerian graph", "[chinesePostman]") {
    gralph::graph::WeightedGraph graph{5, 5};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 1},
        {1, 2, 1},
        {2, 3, 1},
        {3, 4, 1},
        {4, 0, 1},
    };
    graph.build_edges(coords_tuples);

    gralph::algos::fleuryCycle euler_cycle_finder{graph};
    gralph::algos::dijkstra path_finder{graph};

    gralph::problems::chinesePostman cp{graph, path_finder, euler_cycle_finder};
    cp.solve();
    std::vector<std::pair<int, int>> solution = cp.get_solution();
    int cost = cp.get_cost();

    SECTION("Chinese Postman finds the optimal solution for an Eulerian graph") {
        std::vector<std::pair<int, int>> expected_solution = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}};
        int expected_cost = 5;
        REQUIRE(solution == expected_solution);
        REQUIRE(cost == expected_cost);
    }
}

TEST_CASE("Chinese Postman finds the optimal solution for a semi-Eulerian graph (1)", "[chinesePostman]") {
    gralph::graph::WeightedGraph graph{5, 4};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 5},
        {1, 2, 1},
        {2, 3, 3},
        {3, 4, 2},
    };
    graph.build_edges(coords_tuples);

    gralph::algos::fleuryCycle euler_cycle_finder{graph};
    gralph::algos::dijkstra path_finder{graph};

    gralph::problems::chinesePostman cp{graph, path_finder, euler_cycle_finder};
    cp.solve();
    std::vector<std::pair<int, int>> solution = cp.get_solution();

    int cost = cp.get_cost();

    SECTION("Chinese Postman finds the optimal solution for a semi-Eulerian graph") {
        std::vector<std::pair<int, int>> expected_solution = {
            {0, 1}, {1, 2}, {2, 3}, {3, 4}, {3, 4}, {2, 3}, {1, 2}, {0, 1}
        };
        int expected_cost = 22;
        REQUIRE(solution == expected_solution);
        REQUIRE(cost == expected_cost);
    }
}

TEST_CASE("Chinese Postman finds the optimal solution for a semi-Eulerian graph (2)", "[chinesePostman]") {
    gralph::graph::WeightedGraph graph{7, 8};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 5},
        {1, 2, 1},
        {2, 3, 3},
        {3, 4, 2},
        {2, 4, 1},
        {4, 5, 2},
        {2, 6, 1},
        {6, 4, 2}
    };
    graph.build_edges(coords_tuples);

    gralph::algos::fleuryCycle euler_cycle_finder{graph};
    gralph::algos::dijkstra path_finder{graph};

    gralph::problems::chinesePostman cp{graph, path_finder, euler_cycle_finder};
    cp.solve();
    std::vector<std::pair<int, int>> solution = cp.get_solution();

    int cost = cp.get_cost();

    SECTION("Chinese Postman finds the optimal solution for a semi-Eulerian graph") {
        std::vector<std::pair<int, int>> expected_solution = {
            {0, 1},
            {1, 2},
            {2, 3},
            {3, 4},
            {4, 2},
            {2, 6},
            {6, 4},
            {4, 5},
            {4, 5},
            {2, 4},
            {1, 2},
            {0, 1}
        };
        int expected_cost = 26;
        REQUIRE(solution == expected_solution);
        REQUIRE(cost == expected_cost);
    }
}

TEST_CASE("Chinese Postman finds the optimal solution for a graph with multiple connected components", "[chinesePostman]") {
    gralph::graph::WeightedGraph graph{6, 5};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 1},
        {1, 2, 1},
        {2, 3, 1},
        {3, 4, 1},
        {4, 5, 1},
    };
    graph.build_edges(coords_tuples);

    gralph::algos::fleuryCycle euler_cycle_finder{graph};
    gralph::algos::dijkstra path_finder{graph};

    gralph::problems::chinesePostman cp{graph, path_finder, euler_cycle_finder};
    cp.solve();
    std::vector<std::pair<int, int>> solution = cp.get_solution();
    int cost = cp.get_cost();

    SECTION("Chinese Postman finds the optimal solution for a graph with multiple connected components") {
        std::vector<std::pair<int, int>> expected_solution = {
            {0, 1},
            {1, 2},
            {2, 3},
            {3, 4},
            {4, 5},
            {4, 5},
            {3, 4},
            {2, 3},
            {1, 2},
            {0, 1}
        };
        int expected_cost = 10;
        REQUIRE(solution == expected_solution);
        REQUIRE(cost == expected_cost);
    }
}

TEST_CASE("Chinese Postman finds the optimal solution for a non-eulerian and non-semi-eulerian graph", "[chinesePostman]") {
    gralph::graph::WeightedGraph graph{8, 9};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 5},
        {1, 2, 1},
        {2, 3, 3},
        {3, 4, 2},
        {2, 4, 1},
        {4, 5, 2},
        {2, 6, 1},
        {6, 4, 2},
        {1, 7, 3}
    };
    graph.build_edges(coords_tuples);

    gralph::algos::fleuryCycle euler_cycle_finder{graph};
    gralph::algos::dijkstra path_finder{graph};

    gralph::problems::chinesePostman cp{graph, path_finder, euler_cycle_finder};
    cp.solve();
    std::vector<std::pair<int, int>> solution = cp.get_solution();

    int cost = cp.get_cost();

    SECTION("Chinese Postman finds the optimal solution for a non-eulerian and non-semi-eulerian graph") {
        std::vector<std::pair<int, int>> expected_solution = {
            {0, 1},
            {1, 2},
            {2, 3},
            {3, 4},
            {4, 2},
            {2, 6},
            {6, 4},
            {4, 5},
            {5, 1},
            {1, 7},
            {7, 0}
        };
        int expected_cost = 32;
        REQUIRE(solution == expected_solution);
        REQUIRE(cost == expected_cost);
    }
}
