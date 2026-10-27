#include <iostream>
#include <algorithm>
using namespace std;

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

    BSTNode* del(BSTNode* n, int val, bool& found) {
        if (!n) return nullptr;
        if (val < n->id) n->left = del(n->left, val, found);
        else if (val > n->id) n->right = del(n->right, val, found);
        else {
            found = true;
            if (!n->left && !n->right) { delete n; return nullptr; }
            if (!n->left) { BSTNode* t = n->right; delete n; return t; }
            if (!n->right) { BSTNode* t = n->left; delete n; return t; }
            BSTNode* t = getMin(n->right);
            n->id = t->id;
            n->right = del(n->right, t->id, found);
        }
        return n;
    }

    void in(BSTNode* n) { if (n) { in(n->left); cout << n->id << " "; in(n->right); } }
    void pre(BSTNode* n) { if (n) { cout << n->id << " "; pre(n->left); pre(n->right); } }
    void post(BSTNode* n) { if (n) { post(n->left); post(n->right); cout << n->id << " "; } }
    int cnt(BSTNode* n) { return n ? 1 + cnt(n->left) + cnt(n->right) : 0; }
    int hgt(BSTNode* n) { return n ? 1 + max(hgt(n->left), hgt(n->right)) : 0; }

    void clear(BSTNode* n) {
        if (n) { clear(n->left); clear(n->right); delete n; }
    }

public:
    ~BST() { clear(root); }

    void insert(int val) { root = ins(root, val); }

    void remove(int val) {
        if (!root) { cout << "Tree is empty. Operation cancelled.\n"; return; }
        bool found = false;
        root = del(root, val, found);
        if (found) {
            cout << "ID " << val << " deleted successfully.\nUpdated In-Order: ";
            showInOrder();
        } else {
            cout << "ID " << val << " does not exist in the inventory.\n";
        }
    }

    void search(int val) {
        if (!root) { cout << "Tree is empty.\n"; return; }
        BSTNode* c = root;
        while (c) {
            if (c->id == val) { cout << "ID " << val << " EXISTS in inventory.\n"; return; }
            c = (val < c->id) ? c->left : c->right;
        }
        cout << "ID " << val << " NOT FOUND in inventory.\n";
    }

    void showInOrder() { if (!root) cout << "Tree is empty."; else in(root); cout << "\n"; }
    void showPreOrder() { if (!root) cout << "Tree is empty."; else pre(root); cout << "\n"; }
    void showPostOrder() { if (!root) cout << "Tree is empty."; else post(root); cout << "\n"; }
    int getCount() { return cnt(root); }
    int getHeight() { return hgt(root); }
};

int main() {
    BST hospital;
    int hIDs[] = {55, 35, 75, 25, 45, 65, 85, 40, 50};
    for (int x : hIDs) hospital.insert(x);

    int choice, id;
    do {
        cout << "\n=========================================\n";
        cout << "  HOSPITAL & EMERGENCY INVENTORY BST     \n";
        cout << "=========================================\n";
        cout << "1. Insert an ID\n";
        cout << "2. Search for an ID\n";
        cout << "3. Delete an ID\n";
        cout << "4. Display In-Order Traversal\n";
        cout << "5. Display Pre-Order Traversal\n";
        cout << "6. Display Post-Order Traversal\n";
        cout << "7. Count Total Nodes\n";
        cout << "8. Calculate Height of BST\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) break;

        switch (choice) {
            case 1: cout << "Enter ID to insert: "; cin >> id; hospital.insert(id); break;
            case 2: cout << "Enter ID to search: "; cin >> id; hospital.search(id); break;
            case 3: cout << "Enter ID to delete: "; cin >> id; hospital.remove(id); break;
            case 4: cout << "In-Order Traversal: "; hospital.showInOrder(); break;
            case 5: cout << "Pre-Order Traversal: "; hospital.showPreOrder(); break;
            case 6: cout << "Post-Order Traversal: "; hospital.showPostOrder(); break;
            case 7: cout << "Total Nodes: " << hospital.getCount() << "\n"; break;
            case 8: cout << "BST Height: " << hospital.getHeight() << "\n"; break;
            case 9: cout << "Exiting application...\n"; break;
            default: cout << "Invalid menu choice!\n";
        }
    } while (choice != 9);

    return 0;
}