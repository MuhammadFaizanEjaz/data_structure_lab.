// Task 3: Game Player Turns using Circular Singly Linked List
#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string player;
    Node* next;
    Node(string name) : player(name), next(NULL) {}
};

class GameTurns {
private:
    Node* head;
    Node* tail;
public:
    GameTurns() : head(NULL), tail(NULL) {}

    void addPlayer(string name) {
        Node* newNode = new Node(name);
        if (head == NULL) {
            head = tail = newNode;
            tail->next = head;          // points to itself
        } else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head;          // circular connection
        }
    }

    // Each player's turn once
    void displayTurns() {
        cout << "Player turns:" << endl;
        Node* cur = head;
        int turn = 1;
        do {
            cout << "  Turn " << turn++ << ": " << cur->player << endl;
            cur = cur->next;
        } while (cur != head);
    }

    // Shows that after the last player, turn returns to the first
    void showCircular() {
        cout << "Last player : " << tail->player << endl;
        cout << "Next turn   : " << tail->next->player
             << " (back to the first player)" << endl;
    }

    ~GameTurns() {
        if (head == NULL) return;
        tail->next = NULL;              // break the circle before deleting
        while (head != NULL) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    GameTurns game;
    game.addPlayer("Ali");
    game.addPlayer("Sara");
    game.addPlayer("Ahmed");
    game.addPlayer("Fatima");
    game.addPlayer("Usman");

    game.displayTurns();
    cout << endl;
    game.showCircular();
    return 0;
}
