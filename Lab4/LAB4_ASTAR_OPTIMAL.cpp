#include <bits/stdc++.h>
using namespace std;

struct Node {
    string name;
    int g, h, f;
    Node* parent;
};

struct CompareF {
    bool operator()(Node* a, Node* b) {
        return a->f > b->f; // min-heap based on f
    }
};

void printList(const vector<Node*>& lst, string listName) {
    cout << listName << ": [";
    for (size_t i = 0; i < lst.size(); i++) {
        cout << lst[i]->name << "(g=" << lst[i]->g
             << ", h=" << lst[i]->h
             << ", f=" << lst[i]->f << ")";
        if (i != lst.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

void printClosed(const set<string>& closed) {
    cout << "Closed List: {";
    int i = 0;
    for (auto& c : closed) {
        cout << c;
        if (i != (int)closed.size() - 1) cout << ", ";
        i++;
    }
    cout << "}" << endl;
}

void reconstructPath(Node* goal) {
    vector<string> path;
    Node* curr = goal;
    while (curr != nullptr) {
        path.push_back(curr->name);
        curr = curr->parent;
    }
    reverse(path.begin(), path.end());
    cout << "Optimal Path: ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i != path.size() - 1) cout << " -> ";
    }
    cout << endl;
}

int main() {
    // Graph: Pune -> Expressway, OldHighway, CoastalRoad -> Mumbai
    map<string, vector<pair<string, int>>> graph;
    graph["Pune"] = {{"Expressway", 50}, {"OldHighway", 30}, {"CoastalRoad", 20}};
    graph["Expressway"] = {{"Mumbai", 100}};
    graph["OldHighway"] = {{"Mumbai", 120}};
    graph["CoastalRoad"] = {{"Mumbai", 180}};
    graph["Mumbai"] = {};

    // Heuristic (straight-line distance to Mumbai)
    map<string, int> heuristic;
    heuristic["Pune"] = 150;
    heuristic["Expressway"] = 100;
    heuristic["OldHighway"] = 120;
    heuristic["CoastalRoad"] = 180;
    heuristic["Mumbai"] = 0;

    string start = "Pune";
    string goal = "Mumbai";

    // Priority queue (min-heap by f value)
    priority_queue<Node*, vector<Node*>, CompareF> openPQ;
    vector<Node*> openList; // for printing
    set<string> closedList;

    // Start node
    Node* startNode = new Node{start, 0, heuristic[start], heuristic[start], nullptr};
    openPQ.push(startNode);
    openList.push_back(startNode);

    int step = 1;

    while (!openPQ.empty()) {
        cout << "\n--- Step " << step++ << " ---" << endl;
        printList(openList, "Open List");

        Node* current = openPQ.top();
        openPQ.pop();

        cout << "Expanding: " << current->name
             << " (g=" << current->g << ", h=" << current->h
             << ", f=" << current->f << ")" << endl;

        closedList.insert(current->name);
        printClosed(closedList);

        if (current->name == goal) {
            cout << endl;
            reconstructPath(current);
            break;
        }

        // remove expanded node from openList
        openList.erase(remove_if(openList.begin(), openList.end(),
                                 [&](Node* n) { return n->name == current->name; }),
                       openList.end());

        // Explore neighbors
        for (auto& neighbor : graph[current->name]) {
            string nextName = neighbor.first;
            int cost = neighbor.second;

            if (closedList.find(nextName) != closedList.end())
                continue; // already explored

            int gNew = current->g + cost;
            int hNew = heuristic[nextName];
            int fNew = gNew + hNew;

            Node* nextNode = new Node{nextName, gNew, hNew, fNew, current};
            openPQ.push(nextNode);
            openList.push_back(nextNode);
        }
    }

    return 0;
}
