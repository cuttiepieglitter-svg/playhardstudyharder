#include <iostream>
#include <queue>
#include <stack>
#include <set>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstring>

using namespace std;

#define DIM 3

typedef int PuzzleState[DIM][DIM];

// Node structure now stores parent pointer
struct PuzzleNode {
    PuzzleState state;
    PuzzleNode* parent;   // NEW: to reconstruct path
};

// Print puzzle state
void printState(PuzzleState state) {
    for (int i = 0; i < DIM; ++i) {
        for (int j = 0; j < DIM; ++j) {
            cout << state[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

// Compare states
bool isSame(PuzzleState a, PuzzleState b) {
    return memcmp(a, b, sizeof(PuzzleState)) == 0;
}

// Locate zero
pair<int, int> findZero(PuzzleState state) {
    for (int i = 0; i < DIM; ++i)
        for (int j = 0; j < DIM; ++j)
            if (state[i][j] == 0)
                return make_pair(i, j);
    return {-1, -1};
}

// Generate key for visited
string stateKey(PuzzleState state) {
    string key = "";
    for (int i = 0; i < DIM; ++i)
        for (int j = 0; j < DIM; ++j)
            key += to_string(state[i][j]);
    return key;
}

bool isValid(int x, int y) {
    return x >= 0 && x < DIM && y >= 0 && y < DIM;
}

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// NEW: Reconstruct & print full path from initial → goal
void printPath(PuzzleNode* goalNode) {
    vector<PuzzleNode*> path;
    while (goalNode != nullptr) {
        path.push_back(goalNode);
        goalNode = goalNode->parent;
    }
    reverse(path.begin(), path.end());

    cout << "=== Steps from Initial State to Goal ===\n";
    for (int i = 0; i < path.size(); i++) {
        cout << "Step " << i << ":\n";
        printState(path[i]->state);
    }
}

void solveBFS(PuzzleState initial, PuzzleState goal) {
    queue<PuzzleNode*> q;
    set<string> visited;

    PuzzleNode* start = new PuzzleNode;
    memcpy(start->state, initial, sizeof(PuzzleState));
    start->parent = nullptr;

    q.push(start);
    visited.insert(stateKey(start->state));

    while (!q.empty()) {
        PuzzleNode* curr = q.front();
        q.pop();

        if (isSame(curr->state, goal)) {
            cout << "Goal reached using BFS!\n";
            printPath(curr);
            return;
        }

        auto pos = findZero(curr->state);
        int x = pos.first, y = pos.second;

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (isValid(nx, ny)) {
                PuzzleNode* next = new PuzzleNode;
                memcpy(next->state, curr->state, sizeof(PuzzleState));
                swap(next->state[x][y], next->state[nx][ny]);
                next->parent = curr;

                string key = stateKey(next->state);
                if (visited.find(key) == visited.end()) {
                    visited.insert(key);
                    q.push(next);
                } else {
                    delete next;
                }
            }
        }
    }

    cout << "Goal not reachable (BFS).\n";
}

void solveDFS(PuzzleState initial, PuzzleState goal) {
    stack<PuzzleNode*> s;
    set<string> visited;

    PuzzleNode* start = new PuzzleNode;
    memcpy(start->state, initial, sizeof(PuzzleState));
    start->parent = nullptr;

    s.push(start);
    visited.insert(stateKey(start->state));

    while (!s.empty()) {
        PuzzleNode* curr = s.top();
        s.pop();

        if (isSame(curr->state, goal)) {
            cout << "Goal reached using DFS!\n";
            printPath(curr);
            return;
        }

        auto pos = findZero(curr->state);
        int x = pos.first, y = pos.second;

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (isValid(nx, ny)) {
                PuzzleNode* next = new PuzzleNode;
                memcpy(next->state, curr->state, sizeof(PuzzleState));
                swap(next->state[x][y], next->state[nx][ny]);
                next->parent = curr;

                string key = stateKey(next->state);
                if (visited.find(key) == visited.end()) {
                    visited.insert(key);
                    s.push(next);
                } else {
                    delete next;
                }
            }
        }
    }

    cout << "Goal not reachable (DFS).\n";
}

int main() {
    PuzzleState initial;
    PuzzleState goal = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };

    cout << "Enter the initial 3x3 puzzle configuration (0 is blank):\n";
    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++)
            cin >> initial[i][j];

    int choice;
    cout << "\nChoose search method:\n1. BFS\n2. DFS\n> ";
    cin >> choice;

    if (choice == 1)
        solveBFS(initial, goal);
    else if (choice == 2)
        solveDFS(initial, goal);
    else
        cout << "Invalid choice.\n";

    return 0;
}
