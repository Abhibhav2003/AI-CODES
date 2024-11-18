#include <bits/stdc++.h>
using namespace std;

#define inf 1e9

class Graph {
    int n;
public:
    vector<vector<int> > mat;

    Graph(int vertices) {
        n = vertices;
        mat.resize(n);
        for (int i = 0; i < n; i++) {
            mat[i].resize(n, 0);
        }
        for (int i = 0; i < n; i++) {
            mat[i][i] = inf;
        }
    }

    void initializeGraph() {
        // Predefined adjacency matrix
        vector<vector<int> > predefinedMatrix = 
        {
			{0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
            {1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
            {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
            {0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
            {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0}
        };
        
        // Assign the predefined matrix to the graph
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                mat[i][j] = predefinedMatrix[i][j];
                if (i == j) mat[i][j] = inf; // Keep diagonal as inf
            }
        }
    }
};

vector<int> BFS_level_constant(Graph g1, int width) {
    int n = g1.mat.size();
    queue<int> q;
    vector<int> bfs_traverse, vis(n, 0);
    int start_pt;
    cout << "Enter the start point: ";
    cin >> start_pt;
    if (start_pt >= n) {
        cout << "INVALID START POINT.\n";
        return vector<int>(); // Return an empty vector
    }
    q.push(start_pt);
    vis[start_pt] = 1;
    while (!q.empty()) {
        int vertex = q.front();
        q.pop();
        bfs_traverse.push_back(vertex);
        for (int i = 0; i < n && q.size() < width; i++) {
            if (!vis[i] && g1.mat[vertex][i] == 1) {
                q.push(i);
                vis[i] = 1;
            }
        }
    }
    return bfs_traverse;
}

vector<int> BFS_node_constant(Graph g1, int width) {
    int n = g1.mat.size();
    queue<int> q;
    vector<int> bfs_traverse, vis(n, 0);
    int start_pt;
    cout << "Enter the start point: ";
    cin >> start_pt;
    if (start_pt >= n) {
        cout << "INVALID START POINT.\n";
        return vector<int>(); // Return an empty vector
    }
    q.push(start_pt);
    vis[start_pt] = 1;
    while (!q.empty()) {
        int vertex = q.front();
        q.pop();
        bfs_traverse.push_back(vertex);
        int cnt = 0;
        for (int i = 0; i < n && cnt < width; i++) {
            if (!vis[i] && g1.mat[vertex][i] == 1) {
                q.push(i);
                vis[i] = 1;
                cnt++;
            }
        }
    }
    return bfs_traverse;
}

int main() {
    int n = 12; // Set the number of vertices according to the provided matrix
    Graph g1(n);
    g1.initializeGraph(); // Initialize the graph with the predefined matrix

    while (true) {
        cout << "Choose option:\n";
        cout << "1. Constant width at level,\n";
        cout << "2. Constant width at node,\n";
        cout << "Press any other key to exit!\n";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "\n\nCONSTANT WIDTH AT LEVEL\n\n";
            cout << "Enter width for level: ";
            int width;
            cin >> width;
            vector<int> bfs = BFS_level_constant(g1, width);
            cout << "\n\n";
            if (bfs.size() == 0) break;
            for (int i = 0; i < bfs.size(); i++) {
                cout << bfs[i] << "\t";
            }
            cout << endl << endl << endl;
            break;
        }
        case 2: {
            cout << "CONSTANT WIDTH AT NODE\n";
            cout << "Enter width for node: ";
            int width;
            cin >> width;
            vector<int> bfs_node = BFS_node_constant(g1, width);
            cout << "\n\n";
            if (bfs_node.size() == 0) break;
            for (int i = 0; i < bfs_node.size(); i++) {
                cout << bfs_node[i] << "\t";
            }
            cout << endl << endl << endl;
            break;
        }
        default:
            exit(0);
        }
    }

    return 0;
}