#include <bits/stdc++.h>
using namespace std;

void printBoard(const vector<int>& board) {
    for (int i = 0; i < 9; ++i) {
        if (board[i] == 3) cout << "X ";
        else if (board[i] == 5) cout << "O ";
        else cout << ". ";
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

vector<vector<int>> moveGen(const vector<int>& board, int player) 
{
    vector<vector<int>> moves;
    
    for (int i = 0; i < 9; ++i) 
    {
        if (board[i] == 2) {  
            vector<int> newBoard = board;
            newBoard[i] = player;
            moves.push_back(newBoard);
        }
    }

    return moves;
}

int Static_Evaluation(const vector<int>& board, int currentPlayer) 
{
    int score = 0;
    int opponent = (currentPlayer == 3) ? 5 : 3;

    vector<vector<int>> lines = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},  // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},  // Columns
        {0, 4, 8}, {2, 4, 6}              // Diagonals
    };

    for (const auto& line : lines) 
    {
        int countPlayer = 0, countOpponent = 0, empty = 0;

        for (int pos : line) 
        {
            if (board[pos] == currentPlayer) countPlayer++;
            else if (board[pos] == opponent) countOpponent++;
            else empty++;
        }

        if (countOpponent == 2 && empty == 1) {
            score -= 100;  
        }

        if (countPlayer == 2 && empty == 1) {
            score += 50; 
        }

        if (countPlayer == 1 && empty == 2) score += 10;  
        if (countOpponent == 1 && empty == 2) score -= 10;  
    }

    return score;
}


int minimax(vector<int> board, int depth, int maxDepth, int player) 
{
    int score = Check_Win(board);

    if (score != 0 || depth == maxDepth || isDraw(board))
        return score + Static_Evaluation(board,player);

    int bestVal = INT_MIN;
    int opponent = (player == 3) ? 5 : 3;

    for (vector<int> move : moveGen(board, player)) {
        int newVal = -minimax(move, depth + 1, maxDepth, opponent);
        bestVal = max(bestVal, newVal);
    }
    return bestVal;
}

vector<int> ComputerMove(vector<int> board, int maxDepth, int player) 
{
    vector<int> bestBoard = board;
    int bestValue = INT_MIN;
    int opponent = (player == 3) ? 5 : 3;

    for (vector<int> move : moveGen(board, player)) 
    {
        int moveVal = -minimax(move, 1, maxDepth, opponent);

        if (moveVal > bestValue) 
        {
            bestValue = moveVal;
            bestBoard = move;
        }
    }

    return bestBoard;
}

int main() {
    vector<int> board(9, 2);  // Initialize empty board
    int maxDepth;
    string firstPlayerStr;
    int currentPlayer, userPlayer, computerPlayer;

    cout << "Enter maximum search depth for MiniMax: ";
    cin >> maxDepth;

    cout << "Who plays first? (Computer or User): ";
    cin >> firstPlayerStr;

    if (firstPlayerStr == "Computer" || firstPlayerStr == "computer") {
        computerPlayer = 3;  // X
        userPlayer = 5;      // O
        currentPlayer = computerPlayer;
    } else {
        userPlayer = 3;      // X
        computerPlayer = 5;  // O
        currentPlayer = userPlayer;
    }

    bool isPlayerTurn = (currentPlayer == userPlayer);

    while (true) {
        printBoard(board);

        int score = Check_Win(board);
        if (score == 10) {
            cout << "Player X wins!" << endl;
            break;
        } else if (score == -10) {
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
                isPlayerTurn = !isPlayerTurn;
            } else {
                cout << "Invalid move. Try again." << endl;
            }
        } else {
            cout << "Computer is making a move..." << endl;
            board = ComputerMove(board, maxDepth, currentPlayer);
            currentPlayer = (currentPlayer == 3) ? 5 : 3;
            isPlayerTurn = !isPlayerTurn;
        }
    }

    return 0;
}


