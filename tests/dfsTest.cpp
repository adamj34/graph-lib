#include <catch2/catch_test_macros.hpp>
#include "graph_repr/WeightedGraph.hpp"
#include "algorithms/search/dfs.hpp"

TEST_CASE( "DFS finds all reachable vertices from source", "[dfs]" ) {
    gralph::graph::WeightedGraph graph{5, 5};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 2},
        {0, 3, 3},
        {3, 2, 4},
        {1, 2, 8},
        {1, 4, 1},
    };
    graph.build_edges(coords_tuples);

    gralph::search::dfs dfs_algo{};
    dfs_algo.solve(graph, 0);
    std::unordered_set<int> visited = dfs_algo.get_visited();

    SECTION("DFS finds all reachable vertices from source") {
        std::unordered_set<int> expected_visited = {0, 1, 2, 3, 4};
        REQUIRE(visited == expected_visited);
    }
}

TEST_CASE("DFS detects cycles in the graph (1)", "[dfs]") {
    gralph::graph::WeightedGraph graph{10, 10}; // 10 vertices, 0 edges

    std::vector<std::tuple<int, int, int>> edges = {
        {0, 1, 1},
        {1, 2, 1},
        {2, 3, 1},
        {3, 4, 1},
        {4, 5, 1},
        {5, 6, 1},
        {6, 7, 1},
        {7, 8, 1},
        {8, 9, 1},
        {9, 0, 1}, // This edge creates a cycle
    };
    graph.build_edges(edges);

    gralph::search::dfs dfs_algo{};
    dfs_algo.solve(graph, 0);
    bool has_cycle = dfs_algo.contains_cycle();

    SECTION("DFS detects cycles in larger graphs") {
        REQUIRE(has_cycle == true);
    }
}

TEST_CASE( "DFS detects cycles in the graph (2)", "[dfs]" ) {
    gralph::graph::WeightedGraph graph{5, 5};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 2},
        {1, 2, 8},
        {2, 3, 4},
        {3, 4, 1},
        {4, 1, 5},
    };
    graph.build_edges(coords_tuples);

    gralph::search::dfs dfs_algo{};
    dfs_algo.solve(graph, 0);
    bool has_cycle = dfs_algo.contains_cycle();

    SECTION("DFS detects cycles in the graph") {
        REQUIRE(has_cycle == true);
    }
}

TEST_CASE( "DFS detects cycles in the graph (3)", "[dfs]") {
    gralph::graph::WeightedGraph graph{6, 6}; 

    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 1},
        {0, 3, 1},
        {1, 2, 1},
        {1, 4, 1},
        {3, 5, 1},
        {2, 4, 5}
    };
    graph.build_edges(coords_tuples);

    gralph::search::dfs dfs_algo{};
    dfs_algo.solve(graph, 0);
    bool has_cycle = dfs_algo.contains_cycle();
    
    SECTION("DFS detects cycles in the graph") {
        REQUIRE(has_cycle == true);
    }
}

TEST_CASE( "DFS detects cycles in the graph (4)", "[dfs]") {
    gralph::graph::WeightedGraph graph{4, 4}; 

    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 1},
        {1, 2, 1},
        {1, 3, 1},
        {3, 2, 5}
    };
    graph.build_edges(coords_tuples);

    gralph::search::dfs dfs_algo{};
    dfs_algo.solve(graph, 0);
    bool has_cycle = dfs_algo.contains_cycle();
    
    SECTION("DFS detects cycles in the graph") {
        REQUIRE(has_cycle == true);
    }
}

TEST_CASE("DFS does not detect cycles in the graph if there's none (1)", "[dfs]") {
    gralph::graph::WeightedGraph graph{6, 5}; 

    std::vector<std::tuple<int, int, int>> edges = {
        {0, 1, 1},
        {0, 3, 1},
        {1, 2, 1},
        {1, 4, 1},
        {3, 5, 1}
    };
    graph.build_edges(edges);

    gralph::search::dfs dfs_algo{};
    dfs_algo.solve(graph, 0);
    bool has_cycle = dfs_algo.contains_cycle();

    SECTION("DFS correctly does not detect cycles") {
        REQUIRE(has_cycle == false);
    }
}

TEST_CASE( "DFS does not detect cycles in the graph if there's none (2)", "[dfs]") {
    gralph::graph::WeightedGraph graph{4, 4}; 

    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 1},
        {1, 2, 1},
        {1, 3, 1},
        {3, 1, 5}
    };
    graph.build_edges(coords_tuples);

    gralph::search::dfs dfs_algo{};
    dfs_algo.solve(graph, 0);
    bool has_cycle = dfs_algo.contains_cycle();
    
    SECTION("DFS correctly does not detect cycles") {
        REQUIRE(has_cycle == false);
    }
}

TEST_CASE( "DFS handles disconnected graphs", "[dfs]" ) {
    gralph::graph::WeightedGraph graph{5, 0}; // 5 vertices, 0 edges

    graph.build_edges({});
    gralph::search::dfs dfs_algo{};
    dfs_algo.solve(graph, 0);
    std::unordered_set<int> visited = dfs_algo.get_visited();

    SECTION("DFS finds only the source vertex in a disconnected graph") {
        std::unordered_set<int> expected_visited = {0};
        REQUIRE(visited == expected_visited);
    }

}

TEST_CASE("DFS correctly identifies a disconnected graph", "[dfs]") {
    gralph::graph::WeightedGraph graph{5, 3};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 2},
        {2, 3, 3},
        {3, 4, 2}
    };
    graph.build_edges(coords_tuples);

    gralph::search::dfs dfs_algo{};
    dfs_algo.solve(graph, 0);
    bool is_disconnected = dfs_algo.is_disconnected(graph);

    SECTION("DFS correctly identifies a disconnected graph") {
        REQUIRE(is_disconnected == true);
    }
}

TEST_CASE("DFS correctly identifies a connected graph", "[dfs]") {
    gralph::graph::WeightedGraph graph{5, 4};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 2},
        {1, 2, 3},
        {2, 3, 4},
        {3, 4, 5},
    };
    graph.build_edges(coords_tuples);

    gralph::search::dfs dfs_algo{};
    dfs_algo.solve(graph, 0);
    bool is_disconnected = dfs_algo.is_disconnected(graph);

    SECTION("DFS correctly identifies a connected graph") {
        REQUIRE(is_disconnected == false);
    }
}


TEST_CASE("DFS handles a WeightedMultiGraph", "[dfs]") {
    gralph::graph::WeightedMultiGraph graph{7, 9};
    std::vector<std::tuple<int, int, int>> coords_tuples = {
        {0, 1, 1},
        {1, 2, 2},
        {2, 0, 3},
        {3, 4, 4},
        {4, 5, 5},
        {4, 1, 6},
        {5, 3, 2},
        {1, 2, 8},
        {6, 4, 2}
    };
    graph.build_edges(coords_tuples);

    gralph::search::dfs dfs_algo{};
    dfs_algo.solve(graph, 0);
    bool is_disconnected = dfs_algo.is_disconnected(graph);

    SECTION("DFS correctly identifies a connected graph") {
        REQUIRE(is_disconnected == false);
    }

    SECTION("DFS yields the correct visited vertices") {
        std::unordered_set<int> expected_visited = {3, 5, 6, 4, 1, 2, 0};
        REQUIRE(dfs_algo.get_visited() == expected_visited);
    }

    SECTION("DFS correctly identifies a cycle") {
        REQUIRE(dfs_algo.contains_cycle() == true);
    }
}
