#include <bits/stdc++.h>
#include<chrono>
using namespace std;

void displayBoard(const vector<vector<int>>& board) {
    for (const auto& row : board) {
        for (int cell : row) {
            cout << (cell == 1 ? "K" : ".") << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool isSafe(vector<vector<int>>& board, int i, int j) {
    int n = board.size(), m = board[0].size();
    vector<pair<int, int>> moves = {
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
        {1, -2}, {1, 2}, {2, -1}, {2, 1}
    };

    for (auto move : moves) {
        int ni = i + move.first;
        int nj = j + move.second;
        if (ni >= 0 && nj >= 0 && ni < n && nj < m && board[ni][nj] == 1)
            return false;
    }

    return true;
}

bool hasValidPosition(const vector<vector<int>>& board, int row) {
    int m = board[0].size();
    for (int j = 0; j < m; j++) 
    {
        if (board[row][j] == 0) 
        {
            return true;  
        }
    }
    return false;  
}

void KN(vector<vector<int>>& board, int k, int row, int col, int& count) {
    if (k == 0) {
        displayBoard(board);
        count++;
        return;
    }

    int n = board.size(), m = board[0].size();
    for (int i = row; i < n; i++) 
    {
        if (!hasValidPosition(board, i)) continue;

        for (int j = (i == row ? col : 0); j < m; j++) 
        {
            if (board[i][j] == 0 && isSafe(board, i, j)) 
            {
                
                board[i][j] = 1;

                KN(board, k - 1, i, j, count);

                board[i][j] = 0;
            }
        }
    }
}

int main() {
    int n, m, k;
    cout << "Enter board size (n x m): ";
    cin >> n >> m;
    cout << "Enter number of knights: ";
    cin >> k;

    vector<vector<int>> board(n, vector<int>(m, 0));
    int count = 0;
    
    auto start = chrono::high_resolution_clock::now();
    KN(board, k, 0, 0, count);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    cout << "Execution Time: " << duration.count() << " ms" << endl;

    cout << "Total configurations: " << count << endl;
    return 0;
}

