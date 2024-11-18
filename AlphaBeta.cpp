#include <bits/stdc++.h>
using namespace std;

void printBoard(const vector<int>& board) {
    for (int i = 0; i < 9; ++i) {
        if (board[i] == 3) cout << "X ";
        else if (board[i] == 5) cout << "O ";
        else cout << char('.') << " ";
        if (i % 3 == 2) cout << endl;
    }
}

int Check_Win(const vector<int>& board) {
    vector<vector<int>> lines = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},  // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},  // Columns
        {0, 4, 8}, {2, 4, 6}              // Diagonals
    };

    for (auto& line : lines) {
        int a = line[0], b = line[1], c = line[2];
        if (board[a] == board[b] && board[b] == board[c]) {
            if (board[a] == 3) return 10; 
            else if (board[a] == 5) return -10;
        }
    }
    return 0;  // No win or loss
}

bool isDraw(const vector<int>& board) {
    for (int cell : board)
        if (cell == 2) 
            return false;
    return true;
}

vector<vector<int>> moveGen(const vector<int>& board, int player) {
    vector<vector<int>> moves;
    for (int i = 0; i < 9; ++i) {
        if (board[i] == 2) {  
            vector<int> newBoard = board;
            newBoard[i] = player;
            moves.push_back(newBoard);
        }
    }
    return moves;
}

int Static_Evaluation(const vector<int>& board, int currentPlayer) {
    int score = 0;
    int opponent = (currentPlayer == 3) ? 5 : 3;

    vector<int> corners = {0, 2, 6, 8};
    vector<int> edges = {1, 3, 5, 7};

    vector<vector<int>> lines = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},  // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},  // Columns
        {0, 4, 8}, {2, 4, 6}              // Diagonals
    };

    for (const auto& line : lines) {
        int countCurrent = 0, countOpponent = 0, empty = 0;

        for (int pos : line) {
            if (board[pos] == currentPlayer) countCurrent++; 
            else if (board[pos] == opponent) countOpponent++; 
            else empty++; 
        }

        if (countCurrent == 2 && countOpponent == 0 && empty == 1) {
            score += 5; 
        }

        if (countOpponent == 2 && countCurrent == 0 && empty == 1) {
            score -= 5; 
        }
    }

    for (int pos : corners) {
        if (board[pos] == currentPlayer) score += 2;
        else if (board[pos] == opponent) score -= 2;
    }

    if (board[4] == currentPlayer) score += 3;
    else if (board[4] == opponent) score -= 3;

    for (int pos : edges) {
        if (board[pos] == currentPlayer) score += 1;
        else if (board[pos] == opponent) score -= 1;
    }

    return score;
}

int minimax(vector<int> board, int depth, int maxDepth, int player, int alpha, int beta) {
    int score = Check_Win(board);
    if (score != 0 || depth == maxDepth || isDraw(board))
        return score + Static_Evaluation(board, player);

    int bestVal = INT_MIN;
    int opponent = (player == 3) ? 5 : 3;

    for (vector<int> move : moveGen(board, player)) {
        int newVal = -minimax(move, depth + 1, maxDepth, opponent, -beta, -alpha);
        bestVal = max(bestVal, newVal);
        alpha = max(alpha, newVal);
        if (beta <= alpha) break;  // Beta cut-off
    }

    return bestVal;
}

vector<int> ComputerMove(vector<int> board, int maxDepth, int player) {
    vector<int> bestBoard = board;
    int bestValue = INT_MIN;

    int alpha = INT_MIN;
    int beta = INT_MAX;
    int opponent = (player == 3) ? 5 : 3;
    
    for (vector<int> move : moveGen(board, player)) {
        int moveVal = -minimax(move, 1, maxDepth, opponent, -beta, -alpha);
        if (moveVal > bestValue) {
            bestValue = moveVal;
            bestBoard = move;
        }
    }
    return bestBoard;
}

int main() {
    vector<int> board(9, 2);  
    int maxDepth;
    int firstPlayer;

    cout << "Enter maximum search depth for MiniMax: ";
    cin >> maxDepth;

    cout << "Who plays first? (3 for X, 5 for O): ";
    cin >> firstPlayer;

    int currentPlayer = firstPlayer;
    bool isPlayerTurn = true;

    while (true) {
        printBoard(board);

        int score = Check_Win(board);
        if (score == 10) {
            cout << "Player X wins!" << endl;
            break;
        } 
        else if (score == -10) {
            cout << "Player O wins!" << endl;
            break;
        } else if (isDraw(board)) {
            cout << "It's a draw!" << endl;
            break;
        }

        if (isPlayerTurn) {
            int choice;
            cout << "Choose a position (1-9): ";
            cin >> choice;
            choice--;  
            if (choice >= 0 && choice < 9 && board[choice] == 2) {  
                board[choice] = currentPlayer;
                currentPlayer = (currentPlayer == 3) ? 5 : 3;
                isPlayerTurn = false;
            } else {
                cout << "Invalid move. Try again." << endl;
            }
        } 
        else {
            cout << "Computer is making a move..." << endl;
            board = ComputerMove(board, maxDepth, currentPlayer);
            currentPlayer = (currentPlayer == 3) ? 5 : 3;
            isPlayerTurn = true;
        }
    }

    return 0;
}
