#include <iostream>
#include <string>
using namespace std;

struct Node {
    string name;
    Node *left, *right;
    Node(string v) : name(v), left(nullptr), right(nullptr) {}
};

void showTree(Node* n) {
    if (!n) return;
    cout << "Staff Member: " << n->name << "\n";
    cout << "  Left Child : " << (n->left ? n->left->name : "NULL") << "\n";
    cout << "  Right Child: " << (n->right ? n->right->name : "NULL") << "\n";
    cout << "-----------------------------------\n";
    showTree(n->left);
    showTree(n->right);
}

struct BSTNode {
    int id;
    BSTNode *left, *right;
    BSTNode(int v) : id(v), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root = nullptr;

    BSTNode* ins(BSTNode* n, int val) {
        if (!n) return new BSTNode(val);
        if (val < n->id) n->left = ins(n->left, val);
        else if (val > n->id) n->right = ins(n->right, val);
        else cout << "Duplicate ID " << val << " rejected. Tree not modified.\n";
        return n;
    }

    BSTNode* getMin(BSTNode* n) {
        while (n && n->left) n = n->left;
        return n;
    }

    BSTNode* del(BSTNode* n, int val) {
        if (!n) return nullptr;
        if (val < n->id) n->left = del(n->left, val);
        else if (val > n->id) n->right = del(n->right, val);
        else {
            if (!n->left && !n->right) { delete n; return nullptr; }
            if (!n->left) { BSTNode* t = n->right; delete n; return t; }
            if (!n->right) { BSTNode* t = n->left; delete n; return t; }
            BSTNode* t = getMin(n->right);
            n->id = t->id;
            n->right = del(n->right, t->id);
        }
        return n;
    }

    void in(BSTNode* n) {
        if (n) {
            in(n->left);
            cout << n->id << " ";
            in(n->right);
        }
    }

    void clear(BSTNode* n) {
        if (n) { clear(n->left); clear(n->right); delete n; }
    }

public:
    ~BST() { clear(root); }

    void insert(int val) { root = ins(root, val); }
    void remove(int val) { root = del(root, val); }

    void search(int val) {
        BSTNode* c = root;
        int visits = 0;
        bool found = false;
        while (c) {
            visits++;
            if (c->id == val) { found = true; break; }
            c = (val < c->id) ? c->left : c->right;
        }
        if (found) cout << "Staff ID " << val << " EXISTS in system.\n";
        else cout << "Staff ID " << val << " NOT FOUND in system.\n";
        cout << "Total node visits: " << visits << "\n";
    }

    void showInOrder() { in(root); cout << "\n"; }
};

BST buildOriginalBST() {
    BST tree;
    int initialIDs[] = {48, 28, 68, 18, 38, 58, 78};
    for (int x : initialIDs) tree.insert(x);
    return tree;
}

int main() {
    cout << "=========================================\n";
    cout << "PART A: GENERAL BINARY TREE (STAFF NAMES)\n";
    cout << "=========================================\n";

    Node* root = new Node("Alice (Dean)");
    root->left = new Node("Bob (HOD CS)");
    root->right = new Node("Charlie (HOD EE)");
    root->left->left = new Node("David (Lecturer)");
    root->left->right = new Node("Eva (Lecturer)");
    root->right->left = new Node("Frank (Lab Attendant)");
    root->right->right = new Node("Grace (Admin)");

    showTree(root);

    cout << "\n=========================================\n";
    cout << "PART B: BINARY SEARCH TREE (STAFF IDS)  \n";
    cout << "=========================================\n";

    BST bst = buildOriginalBST();

    cout << "Inserting additional IDs (25, 85, 38):\n";
    bst.insert(25);
    bst.insert(85);
    bst.insert(38);

    cout << "\nIn-Order Traversal after insertions:\n";
    bst.showInOrder();

    cout << "\nSearch Operations:\n";
    cout << "-- Existing ID (38) --\n"; bst.search(38);
    cout << "-- Missing ID (50) --\n"; bst.search(50);
    cout << "-- ID smaller than all (10) --\n"; bst.search(10);

    cout << "\nTesting Deletion Cases (Fresh BST Per Case):\n";

    BST t1 = buildOriginalBST();
    cout << "Original BST: "; t1.showInOrder();
    t1.remove(18);
    cout << "After Deleting Leaf Node (18): "; t1.showInOrder();

    BST t2 = buildOriginalBST();
    t2.insert(10);
    cout << "\nModified BST (18 has child 10): "; t2.showInOrder();
    t2.remove(18);
    cout << "After Deleting Node with One Child (18): "; t2.showInOrder();

    BST t3 = buildOriginalBST();
    cout << "\nOriginal BST: "; t3.showInOrder();
    t3.remove(28);
    cout << "After Deleting Node with Two Children (28): "; t3.showInOrder();

    return 0;
}