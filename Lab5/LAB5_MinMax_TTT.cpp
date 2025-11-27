#include <iostream>
#include <limits>
using namespace std;

const int N = 3;  // Tic Tac Toe board size
char board[N][N] = {
    { ' ', ' ', ' ' },
    { ' ', ' ', ' ' },
    { ' ', ' ', ' ' }
};

// Print the board
void printBoard() {
    cout << "\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << board[i][j];
            if (j < N - 1) cout << " | ";
        }
        cout << "\n";
        if (i < N - 1) cout << "--+---+--\n";
    }
    cout << "\n";
}

// Check if moves are left
bool movesLeft() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (board[i][j] == ' ')
                return true;
    return false;
}

// Evaluate board: +10 (AI win), -10 (human win), 0 (draw/ongoing)
int evaluate() {
    // Rows
    for (int row = 0; row < N; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == 'O') return +10;
            if (board[row][0] == 'X') return -10;
        }
    }
    // Cols
    for (int col = 0; col < N; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == 'O') return +10;
            if (board[0][col] == 'X') return -10;
        }
    }
    // Diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == 'O') return +10;
        if (board[0][0] == 'X') return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == 'O') return +10;
        if (board[0][2] == 'X') return -10;
    }
    return 0;
}

// Minimax function
int minimax(int depth, bool isMax) {
    int score = evaluate();

    // If maximizer (AI) won
    if (score == 10) return score - depth;

    // If minimizer (human) won
    if (score == -10) return score + depth;

    // If no moves left → draw
    if (!movesLeft()) return 0;

    if (isMax) { // AI's move (maximize score)
        int best = numeric_limits<int>::min();
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    best = max(best, minimax(depth + 1, false));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    } else { // Human's move (minimize score)
        int best = numeric_limits<int>::max();
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    best = min(best, minimax(depth + 1, true));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

// Find the best move for AI
pair<int, int> findBestMove() {
    int bestVal = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int moveVal = minimax(0, false);
                board[i][j] = ' ';
                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

// Main function
int main() {
    cout << "=== Tic Tac Toe with Minimax (AI vs Human) ===\n";
    cout << "You are X, Computer is O.\n";
    printBoard();

    while (true) {
        int row, col;

        // Human move
        cout << "Enter your move (row and col: 0-2): ";
        cin >> row >> col;
        if (row < 0 || row >= N || col < 0 || col >= N || board[row][col] != ' ') {
            cout << "Invalid move. Try again.\n";
            continue;
        }
        board[row][col] = 'X';
        printBoard();

        if (evaluate() == -10) {
            cout << "You win!\n";
            break;
        }
        if (!movesLeft()) {
            cout << "It's a draw!\n";
            break;
        }

        // AI move
        pair<int, int> bestMove = findBestMove();
        board[bestMove.first][bestMove.second] = 'O';
        cout << "Computer chose: (" << bestMove.first << ", " << bestMove.second << ")\n";
        printBoard();

        if (evaluate() == 10) {
            cout << "Computer wins!\n";
            break;
        }
        if (!movesLeft()) {
            cout << "It's a draw!\n";
            break;
        }
    }
    return 0;
}
