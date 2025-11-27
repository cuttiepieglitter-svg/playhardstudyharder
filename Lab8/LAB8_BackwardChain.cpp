#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

// Knowledge Base: Rules
struct Rule {
    string consequent;              // e.g. "ViralInfection"
    vector<string> antecedents;     // e.g. {"Fever", "Cough"}
};

// Global data
map<string, bool> facts;  // initial known facts
vector<Rule> rules;       // rules knowledge base

// Recursive backward chaining function
bool backward_prove(string goal, vector<string> &proved) {
    cout << "Trying to prove: " << goal << endl;

    // Step 1: Check if already a fact
    if (facts[goal]) {
        cout << goal << " is a known fact.\n";
        proved.push_back(goal);
        return true;
    }

    // Step 2: Search for rules that can produce the goal
    for (auto &rule : rules) {
        if (rule.consequent == goal) {
            cout << "Found rule to derive " << goal << ": ";
            for (size_t i = 0; i < rule.antecedents.size(); i++) {
                cout << rule.antecedents[i];
                if (i < rule.antecedents.size() - 1) cout << " and ";
            }
            cout << " ⇒ " << rule.consequent << endl;

            bool allAntecedentsProved = true;
            for (auto &ant : rule.antecedents) {
                if (!backward_prove(ant, proved)) {
                    allAntecedentsProved = false;
                    break;
                }
            }

            if (allAntecedentsProved) {
                cout <<goal << " is proved by rule.\n";
                proved.push_back(goal);
                facts[goal] = true; // mark as proved fact
                return true;
            }
        }
    }

    cout << "Oh no! Failed to prove " << goal << endl;
    return false;
}

int main() {
    cout << "=== Backward Chaining Medical Diagnosis ===\n";

    // Initial facts from doctor's checkup
    facts["Fever"] = true;
    facts["Cough"] = true;
    facts["BodyAche"] = true;
    facts["ViralInfection"] = false;
    facts["FluSymptoms"] = false;
    facts["Flu"] = false;

    // Rules
    rules.push_back({"ViralInfection", {"Fever", "Cough"}});
    rules.push_back({"FluSymptoms", {"ViralInfection", "BodyAche"}});
    rules.push_back({"Flu", {"FluSymptoms"}});

    string query = "Flu";
    cout << "\nGoal: Prove whether patient has " << query << "\n\n";

    vector<string> proved;
    bool result = backward_prove(query, proved);

    cout << "\n=== Final Result ===\n";
    if (result) {
        cout << "The patient is diagnosed with Flu.\n";
        cout << "Proved sequence: ";
        for (size_t i = 0; i < proved.size(); i++) {
            cout << proved[i];
            if (i < proved.size() - 1) cout << " -> ";
        }
        cout << endl;
    } else {
        cout << "Could not prove Flu with given facts.\n";
    }

    return 0;
}
