#include <iostream>
using namespace std;

#define N 8   // change this for N-Queens

int board[N][N];

// Utility function to print board
void printBoard() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << (board[i][j] ? "Q " : ". ");
        }
        cout << endl;
    }
    cout << "----------------------\n";
}

// Check if a queen can be placed at board[row][col]
bool isSafe(int row, int col) {
    // Check this row on the left
    for (int i = 0; i < col; i++)
        if (board[row][i]) return false;

    // Check upper diagonal on the left
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j]) return false;

    // Check lower diagonal on the left
    for (int i = row, j = col; i < N && j >= 0; i++, j--)
        if (board[i][j]) return false;

    return true;
}

// Solve N-Queens using backtracking
bool solveNQUtil(int col) {
    // Base case: all queens are placed
    if (col >= N) {
        printBoard(); // print one solution
        return true;  // return true to stop at first solution
    }

    // Try placing this queen in all rows one by one
    for (int i = 0; i < N; i++) {
        if (isSafe(i, col)) {
            board[i][col] = 1; // place queen

            if (solveNQUtil(col + 1)) 
                return true; // stop at first solution

            board[i][col] = 0; // backtrack
        }
    }
    return false; // no solution in this column
}

// Wrapper function
void solveNQ() {
    if (!solveNQUtil(0))
        cout << "No solution exists.\n";
}

int main() {
    cout << "=== " << N << "-Queens Problem (Backtracking Search) ===\n";
    // initialize board
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = 0;

    solveNQ();
    return 0;
}
