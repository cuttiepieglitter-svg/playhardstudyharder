#include <iostream>
#include <string>
using namespace std;

const int NUM_REGIONS = 7;
const int NUM_COLORS = 3;

string regions[NUM_REGIONS] = {"WA", "NT", "SA", "Q", "NSW", "V", "T"};
string colors[NUM_COLORS] = {"Red", "Green", "Blue"};

// Adjacency matrix (1 = adjacent, 0 = not adjacent)
int adjacency[NUM_REGIONS][NUM_REGIONS] = {
    // WA, NT, SA, Q, NSW, V, T
    {0, 1, 1, 0, 0, 0, 0}, // WA
    {1, 0, 1, 1, 0, 0, 0}, // NT
    {1, 1, 0, 1, 1, 1, 0}, // SA
    {0, 1, 1, 0, 1, 0, 0}, // Q
    {0, 0, 1, 1, 0, 1, 0}, // NSW
    {0, 0, 1, 0, 1, 0, 0}, // V
    {0, 0, 0, 0, 0, 0, 0}  // T (Tasmania isolated)
};

int assignment[NUM_REGIONS]; // stores assigned color index (-1 = unassigned)

// Forward checking: verify if assigning `color` to `region` is valid
bool isSafe(int region, int color) {
    for (int i = 0; i < NUM_REGIONS; i++) {
        if (adjacency[region][i] == 1 && assignment[i] == color) {
            return false; // neighbor already has this color
        }
    }
    return true;
}

// Backtracking with forward checking
bool forwardChecking(int region) {
    if (region == NUM_REGIONS) return true; // all assigned

    for (int c = 0; c < NUM_COLORS; c++) {
        if (isSafe(region, c)) {
            assignment[region] = c; // assign color

            if (forwardChecking(region + 1)) return true;

            assignment[region] = -1; // backtrack
        }
    }
    return false; // no valid color
}

int main() {
    // initialize assignments
    for (int i = 0; i < NUM_REGIONS; i++) {
        assignment[i] = -1;
    }

    if (forwardChecking(0)) {
        cout << "Australia Map Coloring Solution (using Forward Checking):\n";
        for (int i = 0; i < NUM_REGIONS; i++) {
            cout << regions[i] << " -> " << colors[assignment[i]] << endl;
        }
    } else {
        cout << "No solution found!\n";
    }

    return 0;
}
