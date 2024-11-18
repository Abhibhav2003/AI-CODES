#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> createList() {
    int nodes;
    cout << "Enter Number of Nodes: ";
    cin >> nodes; 
    vector<vector<int>> list(nodes);

    for (int i = 0; i < nodes; i++) {
        cout << "Node " << i << " : ";
        while (true) {
            int neighbor;
            cin >> neighbor;
            if (neighbor == -1)
                break;
            list[i].push_back(neighbor);
        }
    }
    return list;
}

bool DFS(vector<vector<int>>& graph, int node, int depth, int maxdepth, int find) 
{
    if (depth > maxdepth) {
        return false;
    }

    cout << node << " ";

    if (node == find) {
        cout << "\nFound " << find << " at depth: " << depth << "\n";
        return true;
    }

    for (auto neighbor : graph[node]) {
        if (DFS(graph, neighbor, depth + 1, maxdepth, find)) {
            return true;
        }
    }
    return false;
}

void IDDFS(vector<vector<int>>& graph, int start, int maxdepth, int ele) {
    for (int depthLimit = 0; depthLimit <= maxdepth; depthLimit++) {
        cout << "\nDepth " << depthLimit << ": ";
        if (DFS(graph, start, 0, depthLimit, ele)) {
            return;
        }
    }
    cout << "\nElement " << ele << " not found within depth " << maxdepth << "\n";
}

int main() {
    int startNode, maxDepth, find;
    vector<vector<int>> graph = createList();

    cout << "Enter Start Node: ";
    cin >> startNode;
    cout << "Enter Maximum Depth: ";
    cin >> maxDepth;
    cout << "Enter Element to look for: ";
    cin >> find;

    cout << "Iterative Deepening Depth-First Search: ";
    IDDFS(graph, startNode, maxDepth, find);
    return 0;
}