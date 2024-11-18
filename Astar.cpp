#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct Node 
{
    char label; 
    int g;     
    int f;      

    Node(char label, int g, int f) : label(label), g(g), f(f) {}

    bool operator<(const Node& other) const {
        return f > other.f; 
    }
};

vector<char> AStar(const vector<vector<int>>& graph, const unordered_map<char, int>& h_values, char start, char goal) 
{
    priority_queue<Node> open_list;          
    unordered_map<char, int> g_costs;            
    unordered_map<char, char> set_up;           
    g_costs[start] = 0;
    open_list.push(Node(start, 0, h_values.at(start)));

    while (!open_list.empty()) {
        Node current_node = open_list.top();
        open_list.pop();

        if (current_node.label == goal) {
            vector<char> path;
            for (char at = goal; at != 0; at = set_up[at]) {
                path.push_back(at);
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (char neighbor = 'A'; neighbor <= 'J'; ++neighbor) {
            int neighbor_index = neighbor - 'A';
            int edge_cost = graph[current_node.label - 'A'][neighbor_index];
            if (edge_cost > 0) {
                int new_g = g_costs[current_node.label] + edge_cost;
                if (!g_costs.count(neighbor) || new_g < g_costs[neighbor]) {
                    g_costs[neighbor] = new_g;
                    int f = new_g + h_values.at(neighbor);
                    open_list.push(Node(neighbor, new_g, f));
                    set_up[neighbor] = current_node.label;
                }
            }
        }
    }
    return {};
}

int main() {
    vector<vector<int>> graph = {
        {0, 6, 3, 1, 0, 0, 0, 0, 0, 0}, // A
        {6, 0, 2, 6, 3, 4, 0, 0, 0, 0}, // B
        {3, 2, 0, 0, 4, 5, 0, 0, 0, 0}, // C
        {1, 6, 0, 0, 7, 8, 9, 0, 0, 0}, // D
        {0, 3, 4, 7, 0, 6, 9, 9, 0, 0}, // E
        {0, 4, 5, 8, 6, 0, 8, 9, 0, 0}, // F
        {0, 0, 0, 9, 9, 8, 0, 11, 12, 14}, // G
        {0, 0, 0, 0, 9, 9, 11, 0, 14, 15}, // H
        {0, 0, 0, 0, 0, 0, 12, 14, 0, 0}, // I
        {0, 0, 0, 0, 0, 0, 14, 15, 0, 0}, // J
    };

    unordered_map<char, int> h_values = {
        {'A', 15}, {'B', 13}, {'C', 13}, {'D', 12}, {'E', 10},
        {'F', 9}, {'G', 7}, {'H', 6}, {'I', 5}, {'J', 0}
    };

    char start = 'A';
    char goal = 'J';

    vector<char> path = AStar(graph, h_values, start, goal);
    if (!path.empty()) {
        cout << "Path found: ";
        for (size_t i = 0; i < path.size(); ++i) {
            if (i != 0) {
                cout << " -> ";
            }
            cout << path[i];
        }
        cout << endl;
    } 
    else 
    {
        cout << "No path found." << endl;
    }
    return 0;
}
