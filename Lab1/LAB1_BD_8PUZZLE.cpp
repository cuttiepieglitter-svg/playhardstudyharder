#include <iostream>
#include <queue>
#include <stack>
#include <set>
#include <utility> // for std::pair
#include <cstring> // for memcmp and memcpy

using namespace std;

#define DIM 3 // You can change this for other puzzle sizes

typedef int PuzzleState[DIM][DIM];

struct PuzzleNode {
    PuzzleState state;
};

// Helper to print puzzle state
void printState(PuzzleState state) {
    for (int i = 0; i < DIM; ++i) {
        for (int j = 0; j < DIM; ++j) {
            cout << state[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

// Compare two puzzle states
bool isSame(PuzzleState a, PuzzleState b) {
    return memcmp(a, b, sizeof(PuzzleState)) == 0;
}

// Find position of 0
pair<int, int> findZero(PuzzleState state) {
    for (int i = 0; i < DIM; ++i)
        for (int j = 0; j < DIM; ++j)
            if (state[i][j] == 0)
                return make_pair(i, j);
    return make_pair(-1, -1); // should not reach here
}

// Generate a unique key for visited set
string stateKey(PuzzleState state) {
    string key = "";
    for (int i = 0; i < DIM; ++i)
        for (int j = 0; j < DIM; ++j)
            key += to_string(state[i][j]);
    return key;
}

// Check if move is valid
bool isValid(int x, int y) {
    return x >= 0 && x < DIM && y >= 0 && y < DIM;
}

// Move directions: Up, Down, Left, Right
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void solveBFS(PuzzleState initial, PuzzleState goal) {
    queue<PuzzleNode> q;
    set<string> visited;

    PuzzleNode start;
    memcpy(start.state, initial, sizeof(PuzzleState));
    q.push(start);
    visited.insert(stateKey(start.state));

    while (!q.empty()) {
        PuzzleNode curr = q.front(); q.pop();

        if (isSame(curr.state, goal)) {
            cout << "Goal state reached using BFS:\n";
            printState(curr.state);
            return;
        }

        pair<int, int> pos = findZero(curr.state);
        int x = pos.first;
        int y = pos.second;

        for (int dir = 0; dir < 4; ++dir) {
            int newX = x + dx[dir];
            int newY = y + dy[dir];

            if (isValid(newX, newY)) {
                PuzzleNode next;
                memcpy(next.state, curr.state, sizeof(PuzzleState));
                swap(next.state[x][y], next.state[newX][newY]);

                string key = stateKey(next.state);
                if (visited.find(key) == visited.end()) {
                    visited.insert(key);
                    q.push(next);
                }
            }
        }
    }

    cout << "Goal state not reachable using BFS.\n";
}

void solveDFS(PuzzleState initial, PuzzleState goal) {
    stack<PuzzleNode> s;
    set<string> visited;

    PuzzleNode start;
    memcpy(start.state, initial, sizeof(PuzzleState));
    s.push(start);
    visited.insert(stateKey(start.state));

    while (!s.empty()) {
        PuzzleNode curr = s.top(); s.pop();

        if (isSame(curr.state, goal)) {
            cout << "Goal state reached using DFS:\n";
            printState(curr.state);
            return;
        }

        pair<int, int> pos = findZero(curr.state);
        int x = pos.first;
        int y = pos.second;

        for (int dir = 0; dir < 4; ++dir) {
            int newX = x + dx[dir];
            int newY = y + dy[dir];

            if (isValid(newX, newY)) {
                PuzzleNode next;
                memcpy(next.state, curr.state, sizeof(PuzzleState));
                swap(next.state[x][y], next.state[newX][newY]);

                string key = stateKey(next.state);
                if (visited.find(key) == visited.end()) {
                    visited.insert(key);
                    s.push(next);
                }
            }
        }
    }

    cout << "Goal state not reachable using DFS.\n";
}

int main() {
    PuzzleState initial;
    PuzzleState goal = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };

    cout << "Enter the initial 3x3 puzzle configuration (use 0 for blank):\n";
    for (int i = 0; i < DIM; ++i)
        for (int j = 0; j < DIM; ++j)
            cin >> initial[i][j];

    int choice;
    cout << "\nChoose traversal method:\n1. BFS\n2. DFS\nYour choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            solveBFS(initial, goal);
            break;
        case 2:
            solveDFS(initial, goal);
            break;
        default:
            cout << "Invalid choice.\n";
    }

    return 0;
}
