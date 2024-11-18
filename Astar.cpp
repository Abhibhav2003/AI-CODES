#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Define the graph as an adjacency matrix
const int N = 10;
int AdjacencyMatrix[N][N] = {
    {0, 6, 3, 1, 0, 0, 0, 0, 0, 0},
    {6, 0, 2, 6, 3, 4, 0, 0, 0, 0},
    {3, 2, 0, 0, 4, 5, 0, 0, 0, 0},
    {1, 6, 0, 0, 7, 8, 9, 0, 0, 0},
    {0, 3, 4, 7, 0, 6, 9, 9, 0, 0},
    {0, 4, 5, 8, 6, 0, 8, 9, 0, 0},
    {0, 0, 0, 9, 9, 8, 0, 11, 12, 14},
    {0, 0, 0, 0, 9, 9, 11, 0, 14, 15},
    {0, 0, 0, 0, 0, 0, 12, 14, 0, 0},
    {0, 0, 0, 0, 0, 0, 14, 15, 0, 0}
};

// Define heuristic (h-values) for each node
unordered_map<char, int> h_values = {
    {'A', 15}, {'B', 13}, {'C', 13}, {'D', 12},
    {'E', 10}, {'F', 9}, {'G', 7},  {'H', 6},
    {'I', 5},  {'J', 0}
};

// A* algorithm function
vector<char> astar(char start, char goal) {
    // Priority queue to store nodes with their f-values
    priority_queue<pair<int, char>, vector<pair<int, char>>, greater<>> open_set;
    unordered_set<char> closed_set;
    unordered_map<char, int> g_values;    // g-values (cost from start to node)
    unordered_map<char, char> came_from; // Parent nodes for path reconstruction

    open_set.push({h_values[start], start});
    g_values[start] = 0;

    while (!open_set.empty()) {
        char current_node = open_set.top().second;
        open_set.pop();

        // If goal node is reached, reconstruct the path
        if (current_node == goal) {
            vector<char> path;
            while (current_node != start) {
                path.push_back(current_node);
                current_node = came_from[current_node];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }

        closed_set.insert(current_node);

        // Explore neighbors of the current node
        for (int neighbor = 0; neighbor < N; ++neighbor) {
            if (AdjacencyMatrix[current_node - 'A'][neighbor] > 0) {
                char neighbor_char = 'A' + neighbor;

                if (closed_set.find(neighbor_char) != closed_set.end()) {
                    continue; // Already visited this neighbor
                }

                int tentative_g_value = g_values[current_node] +
                                        AdjacencyMatrix[current_node - 'A'][neighbor];

                if (g_values.find(neighbor_char) == g_values.end() ||
                    tentative_g_value < g_values[neighbor_char]) {
                    // Update path information
                    came_from[neighbor_char] = current_node;
                    g_values[neighbor_char] = tentative_g_value;
                    int f_value = tentative_g_value + h_values[neighbor_char];
                    open_set.push({f_value, neighbor_char});
                }
            }
        }
    }

    // No path found
    return {};
}

int main() {
    char start = 'A';
    char goal = 'J';

    vector<char> path = astar(start, goal);

    if (path.empty()) {
        cout << "No path found from " << start << " to " << goal << endl;
    } else {
        cout << "Shortest path from " << start << " to " << goal << ": ";
        for (char node : path) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}
