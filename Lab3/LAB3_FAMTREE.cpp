#include <iostream>
#include <string>
using namespace std;

// Node structure for family members
struct Person {
    string name;
    Person* father;
    Person* mother;
    Person* firstChild;
    Person* nextSibling;
};

// Create new person
Person* createPerson(string name) {
    Person* p = new Person;
    p->name = name;
    p->father = nullptr;
    p->mother = nullptr;
    p->firstChild = nullptr;
    p->nextSibling = nullptr;
    return p;
}

// Add child to a parent
void addChild(Person* parent, Person* child) {
    if (parent->firstChild == nullptr) {
        parent->firstChild = child;
    } else {
        Person* temp = parent->firstChild;
        while (temp->nextSibling != nullptr) {
            temp = temp->nextSibling;
        }
        temp->nextSibling = child;
    }
}

// Print tree recursively
void printTree(Person* root, int level = 0) {
    if (root == nullptr) return;
    for (int i = 0; i < level; i++) cout << "   ";
    cout << root->name << endl;

    Person* child = root->firstChild;
    while (child != nullptr) {
        printTree(child, level + 1);
        child = child->nextSibling;
    }
}

// Query: print children of a person
void printChildren(Person* root, string personName) {
    if (root == nullptr) return;

    if (root->name == personName) {
        cout << "Children of " << personName << ": ";
        Person* child = root->firstChild;
        if (child == nullptr) {
            cout << "None";
        }
        while (child != nullptr) {
            cout << child->name << " ";
            child = child->nextSibling;
        }
        cout << endl;
    }

    // Recursively search
    Person* child = root->firstChild;
    while (child != nullptr) {
        printChildren(child, personName);
        child = child->nextSibling;
    }
}

int main() {
    // Build family tree manually
    Person* grandpa = createPerson("Grandpa");
    Person* father = createPerson("Father");
    Person* uncle = createPerson("Uncle");
    Person* me = createPerson("Me");
    Person* sibling = createPerson("Sibling");
    Person* cousin = createPerson("Cousin");

    // Relationships
    addChild(grandpa, father);
    addChild(grandpa, uncle);
    addChild(father, me);
    addChild(father, sibling);
    addChild(uncle, cousin);

    cout << "Family Tree:" << endl;
    printTree(grandpa);

    cout << "\nQueries:" << endl;
    printChildren(grandpa, "Grandpa");
    printChildren(grandpa, "Father");
    printChildren(grandpa, "Uncle");

    return 0;
}
