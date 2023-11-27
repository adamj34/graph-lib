#include <catch2/catch_test_macros.hpp>
#include "problems/travelingSalesman.hpp"
#include "algorithms/euler/fleuryCycle.hpp"
#include "algorithms/mst/prim.hpp"

TEST_CASE("TravelingSalesman solves correctly (1)", "[TravelingSalesman]") {
    gralph::graph::WeightedGraph graph{5, 10};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 2},
        {0, 2, 1},
        {0, 3, 3},
        {0, 4, 1},
        {1, 2, 1},
        {1, 3, 2},
        {1, 4, 2},
        {2, 3, 1},
        {2, 4, 2},
        {3, 4, 1}
    };
    graph.build_edges(coords_tuples);
    graph.print_matrix();

    gralph::algos::fleuryCycle eulerCycleFinder;
    gralph::algos::prim mstFinder;
    gralph::problems::travelingSalesman tsp(graph, eulerCycleFinder, mstFinder);
    tsp.solve();

    SECTION("Cost is correct") {
        REQUIRE(tsp.get_cost() == 6);
    }

    SECTION("Hamiltonian path is correct") {
        REQUIRE(tsp.get_solution() == std::vector<std::pair<int, int>>{{0, 2}, {2, 1}, {1, 3}, {3, 4}, {4, 0}});
    }

}

TEST_CASE("TravelingSalesman solves correctly (2)", "[TravelingSalesman]") {
    gralph::graph::WeightedGraph graph{4, 6};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 2},
        {0, 2, 9},
        {0, 3, 3},
        {1, 2, 5},
        {1, 3, 2},
        {2, 3, 1},
    };
    graph.build_edges(coords_tuples);
    graph.print_matrix();

    gralph::algos::fleuryCycle eulerCycleFinder;
    gralph::algos::prim mstFinder;
    gralph::problems::travelingSalesman tsp(graph, eulerCycleFinder, mstFinder);
    tsp.solve();

    SECTION("Cost is correct") {
        REQUIRE(tsp.get_cost() == 14);
    }

    SECTION("Hamiltonian path is correct") {
        REQUIRE(tsp.get_solution() == std::vector<std::pair<int, int>>{{0, 1}, {1, 3}, {3, 2}, {2, 0}});
    }

}

TEST_CASE("TravelingSalesman solves correctly (3)", "[TravelingSalesman]") {
    gralph::graph::WeightedGraph graph{7, 21};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 2},
        {0, 2, 1},
        {0, 3, 3},
        {0, 4, 1},
        {0, 5, 8},
        {0, 6, 2},
        {1, 2, 1},
        {1, 3, 2},
        {1, 4, 2},
        {1, 5, 5},
        {1, 6, 1},
        {2, 3, 1},
        {2, 4, 2},
        {2, 5, 1},
        {2, 6, 2},
        {3, 4, 1},
        {3, 5, 2},
        {3, 6, 1},
        {4, 5, 1},
        {4, 6, 2},
        {5, 6, 1}
    };
    graph.build_edges(coords_tuples);
    graph.print_matrix();

    gralph::algos::fleuryCycle eulerCycleFinder;
    gralph::algos::prim mstFinder;
    gralph::problems::travelingSalesman tsp(graph, eulerCycleFinder, mstFinder);
    tsp.solve();

    SECTION("Cost is correct") {
        REQUIRE(tsp.get_cost() == 6);
    }

    SECTION("Hamiltonian path is correct") {
        REQUIRE(tsp.get_solution() == std::vector<std::pair<int, int>>{
            {3, 4}, {4, 0}, {0, 2}, {2, 1}, {1, 6}, {6, 5}, {5, 3}});
    }

}
