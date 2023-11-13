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

    gralph::search::dfs dfs_algo{graph, 0};
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

    gralph::search::dfs dfs_algo{graph, 0};
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

    gralph::search::dfs dfs_algo{graph, 0};
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

    gralph::search::dfs dfs_algo{graph, 0};
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

    gralph::search::dfs dfs_algo{graph, 0};
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

    gralph::search::dfs dfs_algo{graph, 0};
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

    gralph::search::dfs dfs_algo{graph, 0};
    bool has_cycle = dfs_algo.contains_cycle();
    
    SECTION("DFS correctly does not detect cycles") {
        REQUIRE(has_cycle == false);
    }
}

TEST_CASE( "DFS handles disconnected graphs", "[dfs]" ) {
    gralph::graph::WeightedGraph graph{5, 0}; // 5 vertices, 0 edges

    graph.build_edges({});
    gralph::search::dfs dfs_algo{graph, 0};
    std::unordered_set<int> visited = dfs_algo.get_visited();

    SECTION("DFS finds only the source vertex in a disconnected graph") {
        std::unordered_set<int> expected_visited = {0};
        REQUIRE(visited == expected_visited);
    }

}
