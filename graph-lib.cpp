
#include <iostream>
#include 
using namespace std;
using namespace gralph;


int main() {
    WeightedGraph graph{5, 5};
    vector<tuple<int, int, int>> coords_tuples = {
        {0, 1, 2},
        {0, 3, 3},
        {3, 2, 4},
        {1, 2, 8},
        {1, 4, 1},
    };
    graph.build_edges(coords_tuples);
    graph.print_matrix();

    pair<map<int, vector<int>>, int> res = prim(graph);

    cout << "cost: " << res.second << endl;
    for (const auto& [k, v] : res.first) {
        cout << k << ": ";
        for (const auto& elem : v) {
            cout << elem << " ";
        }
        cout << endl;
    }

}
