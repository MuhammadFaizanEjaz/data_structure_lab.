#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class FlightNode {
public:
    int flight_no;
    string destination;
    string departure_time;
    FlightNode* left;
    FlightNode* right;

    FlightNode(int fn, string dest, string dt) {
        flight_no = fn;
        destination = dest;
        departure_time = dt;
        left = NULL;
        right = NULL;
    }
};

class FlightBST {
private:
    FlightNode* root;

    FlightNode* insertRecursive(FlightNode* node, int fn, string dest, string dt) {
        if (node == NULL) {
            return new FlightNode(fn, dest, dt);
        }
        if (fn < node->flight_no) {
            node->left = insertRecursive(node->left, fn, dest, dt);
        } else if (fn > node->flight_no) {
            node->right = insertRecursive(node->right, fn, dest, dt);
        }
        return node;
    }

    FlightNode* searchRecursive(FlightNode* node, int fn) {
        if (node == NULL || node->flight_no == fn) {
            return node;
        }
        if (fn < node->flight_no) {
            return searchRecursive(node->left, fn);
        }
        return searchRecursive(node->right, fn);
    }

    FlightNode* minValueNode(FlightNode* node) {
        FlightNode* current = node;
        while (current != NULL && current->left != NULL) {
            current = current->left;
        }
        return current;
    }

    FlightNode* deleteRecursive(FlightNode* node, int fn) {
        if (node == NULL) {
            return node;
        }
        if (fn < node->flight_no) {
            node->left = deleteRecursive(node->left, fn);
        } else if (fn > node->flight_no) {
            node->right = deleteRecursive(node->right, fn);
        } else {
            if (node->left == NULL && node->right == NULL) {
                delete node;
                return NULL;
            }
            if (node->left == NULL) {
                FlightNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == NULL) {
                FlightNode* temp = node->left;
                delete node;
                return temp;
            }
            FlightNode* temp = minValueNode(node->right);
            node->flight_no = temp->flight_no;
            node->destination = temp->destination;
            node->departure_time = temp->departure_time;
            node->right = deleteRecursive(node->right, temp->flight_no);
        }
        return node;
    }

    void inorderRecursive(FlightNode* node) {
        if (node != NULL) {
            inorderRecursive(node->left);
            cout << "(" << node->flight_no << ", " << node->destination << ", " << node->departure_time << ")" << endl;
            inorderRecursive(node->right);
        }
    }

    void preorderRecursive(FlightNode* node) {
        if (node != NULL) {
            cout << "(" << node->flight_no << ", " << node->destination << ", " << node->departure_time << ")" << endl;
            preorderRecursive(node->left);
            preorderRecursive(node->right);
        }
    }

    void postorderRecursive(FlightNode* node) {
        if (node != NULL) {
            postorderRecursive(node->left);
            postorderRecursive(node->right);
            cout << "(" << node->flight_no << ", " << node->destination << ", " << node->departure_time << ")" << endl;
        }
    }

    int countRecursive(FlightNode* node) {
        if (node == NULL) {
            return 0;
        }
        return 1 + countRecursive(node->left) + countRecursive(node->right);
    }

    int heightRecursive(FlightNode* node) {
        if (node == NULL) {
            return -1;
        }
        return 1 + max(heightRecursive(node->left), heightRecursive(node->right));
    }

    void displayRecursive(FlightNode* node, int level, string prefix) {
        if (node != NULL) {
            for (int i = 0; i < level * 4; i++) cout << " ";
            cout << prefix << node->flight_no << " (" << node->destination << ", " << node->departure_time << ")" << endl;
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
    FlightBST() {
        root = NULL;
    }

    void insert(int fn, string dest, string dt) {
        root = insertRecursive(root, fn, dest, dt);
    }

    FlightNode* search(int fn) {
        return searchRecursive(root, fn);
    }

    void remove(int fn) {
        root = deleteRecursive(root, fn);
    }

    void inorder() {
        inorderRecursive(root);
    }

    void preorder() {
        preorderRecursive(root);
    }

    void postorder() {
        postorderRecursive(root);
    }

    int findMin() {
        if (root == NULL) return -1;
        FlightNode* current = root;
        while (current->left != NULL) {
            current = current->left;
        }
        return current->flight_no;
    }

    int findMax() {
        if (root == NULL) return -1;
        FlightNode* current = root;
        while (current->right != NULL) {
            current = current->right;
        }
        return current->flight_no;
    }

    int countFlights() {
        return countRecursive(root);
    }

    int height() {
        return heightRecursive(root);
    }

    void displayStructure() {
        displayRecursive(root, 0, "Root: ");
    }
};

int main() {
    FlightBST bst;

    bst.insert(500, "London", "08:00");
    bst.insert(300, "Dubai", "09:15");
    bst.insert(700, "New York", "10:30");
    bst.insert(200, "Tokyo", "11:45");
    bst.insert(400, "Paris", "13:00");
    bst.insert(600, "Toronto", "14:20");
    bst.insert(800, "Istanbul", "15:40");
    bst.insert(150, "Doha", "16:50");
    bst.insert(250, "Sydney", "18:00");
    bst.insert(350, "Frankfurt", "19:10");
    bst.insert(450, "Singapore", "20:25");
    bst.insert(750, "Beijing", "22:00");

    cout << "In-order Traversal:" << endl;
    bst.inorder();

    cout << "\nPre-order Traversal:" << endl;
    bst.preorder();

    cout << "\nPost-order Traversal:" << endl;
    bst.postorder();

    FlightNode* found = bst.search(400);
    cout << "\nSearch Flight 400: ";
    if (found != NULL) {
        cout << "(" << found->flight_no << ", " << found->destination << ", " << found->departure_time << ")" << endl;
    } else {
        cout << "Not Found" << endl;
    }

    cout << "Min Flight Number: " << bst.findMin() << endl;
    cout << "Max Flight Number: " << bst.findMax() << endl;
    cout << "Total Flights: " << bst.countFlights() << endl;
    cout << "Tree Height: " << bst.height() << endl;

    bst.remove(150);
    bst.remove(300);
    bst.remove(500);

    cout << "\nFinal BST Structure after Deletions (150, 300, 500):" << endl;
    bst.displayStructure();

    return 0;
}
