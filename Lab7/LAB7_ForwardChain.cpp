#include <iostream>
#include <map>
#include <string>
using namespace std;

// Forward chaining for Flu diagnosis
int main() {
    // Knowledge base facts (initial symptoms from doctor)
    map<string, bool> facts;
    facts["Fever"] = true;      // P
    facts["Cough"] = true;      // Q
    facts["BodyAche"] = true;   // S

    // Inferred facts initialized as false
    facts["ViralInfection"] = false;  // R
    facts["FluSymptoms"] = false;     // T
    facts["Flu"] = false;             // U

    cout << "=== Forward Chaining Medical Diagnosis ===\n";
    cout << "Initial Facts: Fever, Cough, BodyAche\n\n";

    // Step 1: Apply Rule 1: Fever ∧ Cough ⇒ ViralInfection
    if (facts["Fever"] && facts["Cough"]) {
        facts["ViralInfection"] = true;
        cout << "Rule 1 applied: Fever ∧ Cough ⇒ ViralInfection\n";
        cout << "Inferred: ViralInfection = true\n\n";
    }

    // Step 2: Apply Rule 2: ViralInfection ∧ BodyAche ⇒ FluSymptoms
    if (facts["ViralInfection"] && facts["BodyAche"]) {
        facts["FluSymptoms"] = true;
        cout << "Rule 2 applied: ViralInfection ∧ BodyAche ⇒ FluSymptoms\n";
        cout << "Inferred: FluSymptoms = true\n\n";
    }

    // Step 3: Apply Rule 3: FluSymptoms ⇒ Flu
    if (facts["FluSymptoms"]) {
        facts["Flu"] = true;
        cout << "Rule 3 applied: FluSymptoms ⇒ Flu\n";
        cout << "Inferred: Flu = true\n\n";
    }

    // Final Result
    cout << "=== Final Diagnosis ===\n";
    if (facts["Flu"])
        cout << "The patient is diagnosed with Flu.\n";
    else
        cout << "The patient does NOT have Flu.\n";

    return 0;
}
