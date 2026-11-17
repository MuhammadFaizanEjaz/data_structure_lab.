#include <iostream>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

class EmergencyNode {
public:
    int emergency_id;
    string location;
    string severity;
    EmergencyNode* left;
    EmergencyNode* right;
    int height;

    EmergencyNode(int id, string loc, string sev) {
        emergency_id = id;
        location = loc;
        severity = sev;
        left = NULL;
        right = NULL;
        height = 1;
    }
};

class EmergencyAVL {
private:
    EmergencyNode* root;

    int getHeight(EmergencyNode* node) {
        if (node == NULL) return 0;
        return node->height;
    }

    int getBalance(EmergencyNode* node) {
        if (node == NULL) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    EmergencyNode* rightRotate(EmergencyNode* y) {
        EmergencyNode* x = y->left;
        EmergencyNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return x;
    }

    EmergencyNode* leftRotate(EmergencyNode* x) {
        EmergencyNode* y = x->right;
        EmergencyNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    EmergencyNode* insertRecursive(EmergencyNode* node, int id, string loc, string sev) {
        if (node == NULL) {
            return new EmergencyNode(id, loc, sev);
        }
        if (id < node->emergency_id) {
            node->left = insertRecursive(node->left, id, loc, sev);
        } else if (id > node->emergency_id) {
            node->right = insertRecursive(node->right, id, loc, sev);
        } else {
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        if (balance > 1 && id < node->left->emergency_id) {
            return rightRotate(node);
        }
        if (balance < -1 && id > node->right->emergency_id) {
            return leftRotate(node);
        }
        if (balance > 1 && id > node->left->emergency_id) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && id < node->right->emergency_id) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    EmergencyNode* minValueNode(EmergencyNode* node) {
        EmergencyNode* current = node;
        while (current->left != NULL) {
            current = current->left;
        }
        return current;
    }

    EmergencyNode* deleteRecursive(EmergencyNode* node, int id) {
        if (node == NULL) {
            return node;
        }
        if (id < node->emergency_id) {
            node->left = deleteRecursive(node->left, id);
        } else if (id > node->emergency_id) {
            node->right = deleteRecursive(node->right, id);
        } else {
            if (node->left == NULL && node->right == NULL) {
                delete node;
                return NULL;
            }
            if (node->left == NULL) {
                EmergencyNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == NULL) {
                EmergencyNode* temp = node->left;
                delete node;
                return temp;
            }
            EmergencyNode* temp = minValueNode(node->right);
            node->emergency_id = temp->emergency_id;
            node->location = temp->location;
            node->severity = temp->severity;
            node->right = deleteRecursive(node->right, temp->emergency_id);
        }

        if (node == NULL) {
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0) {
            return rightRotate(node);
        }
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && getBalance(node->right) <= 0) {
            return leftRotate(node);
        }
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    EmergencyNode* searchRecursive(EmergencyNode* node, int id) {
        if (node == NULL || node->emergency_id == id) {
            return node;
        }
        if (id < node->emergency_id) {
            return searchRecursive(node->left, id);
        }
        return searchRecursive(node->right, id);
    }

    void inorderRecursive(EmergencyNode* node) {
        if (node != NULL) {
            inorderRecursive(node->left);
            cout << "(" << node->emergency_id << ", " << node->location << ", " << node->severity << ")" << endl;
            inorderRecursive(node->right);
        }
    }

    void displayStatsRecursive(EmergencyNode* node) {
        if (node != NULL) {
            displayStatsRecursive(node->left);
            cout << "ID: " << node->emergency_id 
                 << ", Location: " << node->location 
                 << ", Severity: " << node->severity 
                 << ", Height: " << node->height 
                 << ", Balance: " << getBalance(node) << endl;
            displayStatsRecursive(node->right);
        }
    }

    void displayRecursive(EmergencyNode* node, int level, string prefix) {
        if (node != NULL) {
            for (int i = 0; i < level * 4; i++) cout << " ";
            cout << prefix << "ID:" << node->emergency_id 
                 << " [Loc:" << node->location 
                 << ", Sev:" << node->severity 
                 << ", BF:" << getBalance(node) << "]" << endl;
            if (node->left != NULL || node->right != NULL) {
                if (node->left != NULL) {
                    displayRecursive(node->left, level + 1, "L--- ");
                } else {
                    for (int i = 0; i < (level + 1) * 4; i++) cout << " ";
                    cout << "L--- None" << endl;
                }
                if (node->right != NULL) {
                    displayRecursive(node->right, level + 1, "R--- ");
                } else {
                    for (int i = 0; i < (level + 1) * 4; i++) cout << " ";
                    cout << "R--- None" << endl;
                }
            }
        }
    }

public:
    EmergencyAVL() {
        root = NULL;
    }

    void insert(int id, string loc, string sev) {
        root = insertRecursive(root, id, loc, sev);
    }

    void remove(int id) {
        root = deleteRecursive(root, id);
    }

    EmergencyNode* search(int id) {
        return searchRecursive(root, id);
    }

    void inorder() {
        inorderRecursive(root);
    }

    void levelOrder() {
        if (root == NULL) return;
        queue<EmergencyNode*> q;
        q.push(root);
        while (!q.empty()) {
            EmergencyNode* current = q.front();
            q.pop();
            cout << "(" << current->emergency_id << ", " << current->location << ", " << current->severity << ")" << endl;
            if (current->left != NULL) q.push(current->left);
            if (current->right != NULL) q.push(current->right);
        }
    }

    void displayNodeStats() {
        displayStatsRecursive(root);
    }

    void displayStructure() {
        displayRecursive(root, 0, "Root: ");
    }
};

int main() {
    EmergencyAVL avl;

    avl.insert(50, "Sector F-7", "High");
    avl.insert(30, "Blue Area", "Critical");
    avl.insert(70, "G-11 Markaz", "Medium");
    avl.insert(20, "I-8 Sector", "Low");
    avl.insert(40, "F-10 Markaz", "High");
    avl.insert(60, "DHA Phase 2", "Critical");
    avl.insert(80, "Bahria Town", "Medium");
    avl.insert(10, "Rawalpindi Saddar", "High");
    avl.insert(25, "Airport Road", "Critical");
    avl.insert(35, "G-9 Markaz", "Low");
    avl.insert(65, "E-7 Sector", "High");
    avl.insert(90, "Bani Gala", "Medium");

    cout << "In-order Traversal (Sorted by Emergency ID):" << endl;
    avl.inorder();

    cout << "\nLevel-order (BFS) Traversal:" << endl;
    avl.levelOrder();

    cout << "\nNode Heights and Balance Factors:" << endl;
    avl.displayNodeStats();

    EmergencyNode* foundEm = avl.search(60);
    cout << "\nSearch Emergency ID 60: ";
    if (foundEm != NULL) {
        cout << "(" << foundEm->emergency_id << ", " << foundEm->location << ", " << foundEm->severity << ")" << endl;
    } else {
        cout << "Not Found" << endl;
    }

    avl.remove(10);
    avl.remove(70);

    cout << "\nFinal Balanced AVL Tree Structure after Deletions (10, 70):" << endl;
    avl.displayStructure();

    return 0;
}
