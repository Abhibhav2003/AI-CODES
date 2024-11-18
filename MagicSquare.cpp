#include <iostream>
#include <array>
using namespace std;

array<int, 10> grid{2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
int moveCount = 1;
bool isPlayerFirst = false; 


int findWinningMove(int mark) {
    int product;
    array<array<int, 3>, 8> winPatterns = {{
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9},
        {1, 4, 7}, {2, 5, 8}, {3, 6, 9},
        {1, 5, 9}, {3, 5, 7}
    }};

    for (const auto& pattern : winPatterns) {
        product = grid[pattern[0]] * grid[pattern[1]] * grid[pattern[2]];
        if (product == mark * mark * 2) {
            for (int pos : pattern) {
                if (grid[pos] == 2) return pos;
            }
        }
    }
    return 0;
}


void displayGrid() {
    for (int i = 1; i < 10; i++) {
        if (grid[i] == 3) cout << "X ";
        else if (grid[i] == 5) cout << "O ";
        else cout << ". ";
        
        if (i % 3 == 0) cout << "\n";
    }
    cout << endl;
}


bool isWinner(int mark) {
    array<array<int, 3>, 8> winPatterns = {{
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9},
        {1, 4, 7}, {2, 5, 8}, {3, 6, 9},
        {1, 5, 9}, {3, 5, 7}
    }};
    
    for (const auto& pattern : winPatterns) {
        int product = grid[pattern[0]] * grid[pattern[1]] * grid[pattern[2]];
        if (product == mark * mark * mark) {
            return true; 
        }
    }
    return false;
}


int findAlternateMove() {
    if (grid[5] == 2) return 5;
    for (int pos : {2, 4, 6, 8}) {
        if (grid[pos] == 2) return pos;
    }
    return -1;
}


void makeMove(int pos) {
    if (moveCount % 2 == 1) {
        grid[pos] = 3;  // Player's mark 'X'
    } else {
        grid[pos] = 5;  // Computer's mark 'O'
    }
    moveCount++;
}

void playerTurn() {
    int choice;
    cout << "Enter your move (1-9): ";
    cin >> choice;

    while (choice < 1 || choice > 9 || grid[choice] != 2) {
        cout << "Invalid input! Try again: ";
        cin >> choice;
    }

    makeMove(choice);
}

void startGame() {
    while (moveCount <= 9) {
        displayGrid();

        if (isPlayerFirst) {
            if (moveCount % 2 == 1) {  
                playerTurn();
                if (isWinner(5)) {  
                    displayGrid();
                    cout << "Player wins!" << endl;
                    return;
                }
            } else {  
                switch (moveCount) {
                    case 2: grid[5] == 2 ? makeMove(5) : makeMove(1); break;
                    case 4: findWinningMove(3) ? makeMove(findWinningMove(3)) : makeMove(findAlternateMove()); break;
                    case 6: 
                        if (findWinningMove(5)) {
                            makeMove(findWinningMove(5));
                        } else if (findWinningMove(3)) {
                            makeMove(findWinningMove(3));
                        } else {
                            makeMove(findAlternateMove());
                        }
                        break;
                    default: 
                        if (findWinningMove(3)) {
                            makeMove(findWinningMove(3));
                        } else if (findWinningMove(5)) {
                            makeMove(findWinningMove(5));
                        } else {
                            for (int i = 1; i <= 9; i++) {
                                if (grid[i] == 2) {
                                    makeMove(i);
                                    break;
                                }
                            }
                        }
                        break;
                }
                if (isWinner(3)) {  
                    displayGrid();
                    cout << "Computer wins!" << endl;
                    return;
                }
            }
        } else { 
            if (moveCount % 2 == 1) {  
                switch (moveCount) {
                    case 1: makeMove(1); break;
                    case 3: grid[9] == 2 ? makeMove(9) : makeMove(3); break;
                    case 5: 
                        if (findWinningMove(3)) {
                            makeMove(findWinningMove(3));
                        } else if (findWinningMove(5)) {
                            makeMove(findWinningMove(5));
                        } else {
                            grid[7] == 2 ? makeMove(7) : makeMove(3);
                        }
                        break;
                    default: 
                        if (findWinningMove(3)) {
                            makeMove(findWinningMove(3));
                        } else if (findWinningMove(5)) {
                            makeMove(findWinningMove(5));
                        } else {
                            for (int i = 1; i <= 9; i++) {
                                if (grid[i] == 2) {
                                    makeMove(i);
                                    break;
                                }
                            }
                        }
                        break;
                }
                if (isWinner(3)) {
                    displayGrid();
                    cout << "Computer wins!" << endl;
                    return;
                }
            } else {  
                playerTurn();
                if (isWinner(5)) {  
                    displayGrid();
                    cout << "Player wins!" << endl;
                    return;
                }
            }
        }
    }
    displayGrid();
    cout << "Game over! It's a tie!" << endl;
}


void askWhoGoesFirst() {
    char choice;
    cout << "Do you want to go first? (y/n): ";
    cin >> choice;
    isPlayerFirst = (choice == 'y' || choice == 'Y');
}

int main() {
    askWhoGoesFirst(); 
    startGame();
    return 0;
}
