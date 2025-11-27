//run: g++ LAB1_BFS_DFS.cpp -o LAB1_BFS_DFS (this is op file name), then just write output file name

#include <iostream>
using namespace std;

//Node Structure
struct Node {
    int data;
    Node* left;
    Node* right;
};

//Queue Node (for BFS)
struct QueueNode {
    Node* treeNode;
    QueueNode* next;
};

//Linked List Queue
class Queue {
    QueueNode* front;
    QueueNode* rear;
public:
    Queue() {
        front = rear = nullptr;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    void enqueue(Node* node) {
        QueueNode* temp = new QueueNode{node, nullptr};
        if (rear == nullptr) {
            front = rear = temp;
        } else {
            rear->next = temp;
            rear = temp;
        }
    }

    Node* dequeue() {
        if (isEmpty()) return nullptr;
        QueueNode* temp = front;
        Node* treeNode = temp->treeNode;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        delete temp;
        return treeNode;
    }
};

//BST Functions 
Node* insert(Node* root, int data) {
    if (root == nullptr) {
        root = new Node{data, nullptr, nullptr};
    } else if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

//DFS Traversals 
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

void preorder(Node* root) {
    if (root) {
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
}

//BFS (Level Order Traversal) 
void bfs(Node* root) {
    if (root == nullptr) return;
    Queue q;
    q.enqueue(root);
    while (!q.isEmpty()) {
        Node* curr = q.dequeue();
        cout << curr->data << " ";
        if (curr->left) q.enqueue(curr->left);
        if (curr->right) q.enqueue(curr->right);
    }
}

//Menu 
int main() {
    Node* root = nullptr;
    int choice, val;
    
    do {
        cout << "\n====== Binary Search Tree Menu ======\n";
        cout << "1. Insert Node\n";
        cout << "2. DFS - Inorder Traversal\n";
        cout << "3. DFS - Preorder Traversal\n";
        cout << "4. DFS - Postorder Traversal\n";
        cout << "5. BFS - Level Order Traversal\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> val;
                root = insert(root, val);
                break;
            case 2:
                cout << "Inorder Traversal: ";
                inorder(root);
                cout << endl;
                break;
            case 3:
                cout << "Preorder Traversal: ";
                preorder(root);
                cout << endl;
                break;
            case 4:
                cout << "Postorder Traversal: ";
                postorder(root);
                cout << endl;
                break;
            case 5:
                cout << "Level Order Traversal (BFS): ";
                bfs(root);
                cout << endl;
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
