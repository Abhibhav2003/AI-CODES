#include <iostream>
using namespace std;

int board[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2}; 
int turn = 0; 
int player = 3; 
int computer = 5;

void displayBoard() {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) cout << endl;
        if (board[i] == 2) cout << ". ";
        else if (board[i] == 3) cout << "X ";
        else cout << "O ";
    }
    cout << endl;
}


void Go(int pos) {
    board[pos - 1] = computer; 
    turn++;
}


int Posswin(int mark) {
    int winPatterns[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
        {0, 4, 8}, {2, 4, 6}             // Diagonals
    };

    for (auto &pattern : winPatterns) {
        int sum = board[pattern[0]] * board[pattern[1]] * board[pattern[2]];
        if (sum == mark * mark * 2) { 
            for (int i : pattern) {
                if (board[i] == 2) return i + 1; 
            }
        }
    }
    return 0; 
}


int Make2() {
    int preferredPositions[8] = {5, 1, 3, 7, 9, 2, 4, 6};
    for (int pos : preferredPositions) {
        if (board[pos - 1] == 2) return pos;
    }
    return 0;
}

// Computer's move logic
void computerMove() {
    switch (turn) {
        case 0:
        case 1:
            if (board[4] == 2) Go(5);
            else Go(1);
            break;
        case 2:
        case 3:
            if (Posswin(5)) Go(Posswin(5));
            else if (Posswin(3)) Go(Posswin(3));
            else Go(Make2());
            break;
        case 4:
        case 5:
            if (Posswin(5)) Go(Posswin(5));
            else if (Posswin(3)) Go(Posswin(3));
            else Go(Make2());
            break;
        case 6:
        case 7:
            if (Posswin(5)) Go(Posswin(5));
            else if (Posswin(3)) Go(Posswin(3));
            else Go(Make2());
            break;
        case 8:
        case 9:
            if (Posswin(5)) Go(Posswin(5));
            else if (Posswin(3)) Go(Posswin(3));
            else Go(Make2());
            break;
        default:
            cout << "Unexpected state in computerMove.\n";
            break;
    }
}

bool isGameOver() {
    int winPatterns[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
        {0, 4, 8}, {2, 4, 6}             // Diagonals
    };

    for (auto &pattern : winPatterns) {
        int sum = board[pattern[0]] * board[pattern[1]] * board[pattern[2]];
        if (sum == 27 || sum == 125) return true; 
    }
    for (int cell : board) {
        if (cell == 2) return false; 
    }
    return true;
}


int main() {
    cout << "Welcome to Tic-Tac-Toe!\n";

    int first;
    cout << "Do you want to go first? (1 for yes, 0 for no): ";
    cin >> first;

    if (first == 0) {
        computerMove(); 
        displayBoard();
    }

    while (!isGameOver())
    {
        // Player's move
        int pos;
        cout << "Enter your move (1-9): ";
        cin >> pos;
        if (board[pos - 1] != 2) {
            cout << "Invalid move! Try again.\n";
            continue;
        }
        board[pos - 1] = player;
        turn++;
        displayBoard();

        if (isGameOver()) break;

        // Computer's move
        computerMove();
        displayBoard();
    }

    cout << "Game Over!\n";
    return 0;
}
