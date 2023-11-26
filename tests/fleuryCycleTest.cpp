#include <catch2/catch_test_macros.hpp>
#include "graph_repr/WeightedGraph.hpp"
#include "algorithms/euler/fleuryCycle.hpp"

TEST_CASE("Fleury's algorithm finds an Eulerian cycle in a simple graph (1)", "[fleury]") {
    gralph::graph::WeightedGraph graph{5, 5};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 1},
        {1, 2, 1},
        {2, 3, 1},
        {3, 4, 1},
        {4, 0, 1},
    };
    graph.build_edges(coords_tuples);

    gralph::algos::fleuryCycle fleury_algo{};
    fleury_algo.solve(graph, 0);
    std::vector<std::pair<int, int>> eulerian_path = fleury_algo.get_eulerian_cycle();


    SECTION("Fleury's algorithm calculates the correct cost") {
        REQUIRE(fleury_algo.get_cost() == 5);
    }

    SECTION("Fleury's algorithm finds an Eulerian cycle in a simple graph") {
        std::vector<std::pair<int, int>> expected_path = {
            {0, 1},
            {1, 2},
            {2, 3},
            {3, 4},
            {4, 0},
        };
        REQUIRE(eulerian_path == expected_path);
    }
}

TEST_CASE("Fleury's algorithm finds an Eulerian cycle in a simple graph (2)", "[fleury]") {
    gralph::graph::WeightedGraph graph{5, 6};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 1},
        {0, 2, 5},
        {0, 3, 2},
        {0, 4, 2},
        {1, 2, 3},
        {3, 4, 1}
    };
    graph.build_edges(coords_tuples);

    gralph::algos::fleuryCycle fleury_algo{};
    fleury_algo.solve(graph, 2);
    std::vector<std::pair<int, int>> eulerian_path = fleury_algo.get_eulerian_cycle();

    SECTION("Fleury's algorithm calculates the correct cost") {
        REQUIRE(fleury_algo.get_cost() == 14);
    }

    SECTION("Fleury's algorithm finds an Eulerian cycle in a simple graph") {
        std::vector<std::pair<int, int>> expected_path = {
            {2, 0},
            {0, 3},
            {3, 4},
            {4, 0},
            {0, 1},
            {1, 2}
        };
        REQUIRE(eulerian_path == expected_path);
    }
}

TEST_CASE("Fleury's algorithm finds an Eulerian cycle in a simple graph (3)", "[fleury]") {
    gralph::graph::WeightedGraph graph{5, 6};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 1},
        {0, 2, 5},
        {0, 3, 2},
        {0, 4, 2},
        {1, 2, 3},
        {3, 4, 1}
    };
    graph.build_edges(coords_tuples);

    gralph::algos::fleuryCycle fleury_algo{};
    fleury_algo.solve(graph, 0);
    std::vector<std::pair<int, int>> eulerian_path = fleury_algo.get_eulerian_cycle();


    SECTION("Fleury's algorithm calculates the correct cost") {
        REQUIRE(fleury_algo.get_cost() == 14);
    }


    SECTION("Fleury's algorithm finds an Eulerian path in a simple graph") {
        std::vector<std::pair<int, int>> expected_path = {
            {0, 1},
            {1, 2},
            {2, 0},
            {0, 3},
            {3, 4},
            {4, 0}
        };
        REQUIRE(eulerian_path == expected_path);
    }
}

TEST_CASE("Fleury's algorithm finds an Eulerian path in a graph with a bridge", "[fleury]") {
    gralph::graph::WeightedGraph graph{5, 4};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 1},
        {1, 2, 1},
        {2, 3, 1},
        {3, 4, 1},
    };
    graph.build_edges(coords_tuples);

    gralph::algos::fleuryCycle fleury_algo{};
    fleury_algo.solve(graph, 0);
    std::vector<std::pair<int, int>> eulerian_path = fleury_algo.get_eulerian_cycle();

    SECTION("Fleury's algorithm finds an Eulerian path in a graph with a bridge") {
        std::vector<std::pair<int, int>> expected_path = {
            {0, 1},
            {1, 2},
            {2, 3},
            {3, 4},
        };
        REQUIRE(eulerian_path == expected_path);
    }
}

TEST_CASE("Fleury's algorithm correctly handles non-eulerian & semi-eulerian graphs (1)", "[fleury]") {
    gralph::graph::WeightedGraph graph{5, 3};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 1},
        {1, 2, 3},
        {4, 2, 9}
    };
    graph.build_edges(coords_tuples);

    gralph::algos::fleuryCycle fleury_algo{};
    fleury_algo.solve(graph, 0);

    std::vector<std::pair<int, int>> eulerian_path = fleury_algo.get_eulerian_cycle();

    SECTION("Fleury's algorithm calculates the correct cost") {
        REQUIRE(fleury_algo.get_cost() == 13);
    }

    SECTION("Fleury's algorithm correctly handles non-eulerian & semi-eulerian graphs") {
        std::vector<std::pair<int, int>> expected_path = {
            {0, 1},
            {1, 2},
            {2, 4}
        };
        REQUIRE(eulerian_path == expected_path);
    }
}

TEST_CASE("Fleury's algorithm correctly handles non-eulerian & semi-eulerian graphs (2)", "[fleury]") {
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

    gralph::algos::fleuryCycle fleury_algo{};
    fleury_algo.solve(graph, 0);

    std::vector<std::pair<int, int>> eulerian_path = fleury_algo.get_eulerian_cycle();

    SECTION("Fleury's algorithm calculates the correct cost") {
        REQUIRE(fleury_algo.get_cost() == 17);
    }

    SECTION("Fleury's algorithm correctly handles non-eulerian & semi-eulerian graphs") {
        std::vector<std::pair<int, int>> expected_path = {
            {0, 1},
            {1, 2},
            {2, 3},
            {3, 4},
            {4, 2},
            {2, 6},
            {6, 4},
            {4, 5}
        };
        REQUIRE(eulerian_path == expected_path);
    }
}

TEST_CASE("Fleury's algorithm correctly handles graphs with no Eulerian path (2)", "[fleury]") {
    gralph::graph::WeightedGraph graph{5, 4};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 1},
        {1, 2, 1},
        {2, 3, 1},
        {3, 4, 1},
    };
    graph.build_edges(coords_tuples);

    gralph::algos::fleuryCycle fleury_algo{};
    fleury_algo.solve(graph, 0);
    std::vector<std::pair<int, int>> eulerian_path = fleury_algo.get_eulerian_cycle();


    SECTION("Fleury's algorithm correctly handles graphs with no Eulerian path") {
        std::vector<std::pair<int, int>> expected_path = {
            {0, 1},
            {1, 2},
            {2, 3},
            {3, 4},
        };
        REQUIRE(eulerian_path == expected_path);
    }
}

TEST_CASE("Fleury's algorithm correctly handles disconnected graphs", "[fleury]") {
    gralph::graph::WeightedGraph graph{5, 0};
    graph.build_edges({});

    gralph::algos::fleuryCycle fleury_algo{};
    fleury_algo.solve(graph, 0);
    std::vector<std::pair<int, int>> eulerian_path = fleury_algo.get_eulerian_cycle();

    SECTION("Fleury's algorithm calculates the correct cost") {
        REQUIRE(fleury_algo.get_cost() == 0);
    }    

    SECTION("Fleury's algorithm correctly handles disconnected graphs") {
        std::vector<std::pair<int, int>> expected_path = {};
        REQUIRE(eulerian_path == expected_path);
    }
}


TEST_CASE("Fleury's algorithm finds an Eulerian path in a WeightedMultiGraph", "[fleury]") {
    gralph::graph::WeightedMultiGraph graph{7, 11};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 1},
        {1, 2, 2},
        {2, 0, 3},
        {3, 4, 4},
        {4, 5, 5},
        {4, 1, 6},
        {5, 3, 2},
        {1, 2, 8},
        {6, 4, 2},
        {4, 3, 7},
        {2, 3, 5}
    };
    graph.build_edges(coords_tuples);

    gralph::algos::fleuryCycle fleury_algo{};
    fleury_algo.solve(graph, 0);
    std::vector<std::pair<int, int>> eulerian_path = fleury_algo.get_eulerian_cycle();


    SECTION("Fleury's algorithm calculates the correct cost") {
        REQUIRE(fleury_algo.get_cost() == 45);
    }

    SECTION("Fleury's algorithm finds an Eulerian path in a simple graph") {
        std::vector<std::pair<int, int>> expected_path = {
            {4, 1},
            {1, 0},
            {0, 2},
            {2, 1},
            {1, 2},
            {2, 3},
            {3, 4},
            {4, 3},
            {3, 5},
            {5, 4},
            {4, 6},
        };
        REQUIRE(eulerian_path == expected_path);
    }
}


TEST_CASE("Fleury's algorithm finds an Eulerian cycle in a WeightedMultiGraph", "[fleury]") {
    gralph::graph::WeightedMultiGraph graph{7, 12};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 1},
        {1, 2, 2},
        {2, 0, 3},
        {3, 4, 4},
        {4, 5, 5},
        {4, 1, 6},
        {5, 3, 2},
        {1, 2, 8},
        {6, 4, 2},
        {4, 3, 7},
        {4, 6, 1},
        {2, 3, 5}
    };
    graph.build_edges(coords_tuples);

    gralph::algos::fleuryCycle fleury_algo{};
    fleury_algo.solve(graph, 4);
    std::vector<std::pair<int, int>> eulerian_path = fleury_algo.get_eulerian_cycle();


    SECTION("Fleury's algorithm calculates the correct cost") {
        REQUIRE(fleury_algo.get_cost() == 46);
    }

    SECTION("Fleury's algorithm finds an Eulerian path in a simple graph") {
        std::vector<std::pair<int, int>> expected_path = {
            {4, 1},
            {1, 0},
            {0, 2},
            {2, 1},
            {1, 2},
            {2, 3},
            {3, 4},
            {4, 3},
            {3, 5},
            {5, 4},
            {4, 6},
            {6, 4}
        };
        REQUIRE(eulerian_path == expected_path);
    }
}
