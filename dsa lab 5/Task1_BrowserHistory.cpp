// Task 1: Browser History using Doubly Linked List
#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string website;
    Node* prev;
    Node* next;
    Node(string site) : website(site), prev(NULL), next(NULL) {}
};

class BrowserHistory {
private:
    Node* head;
    Node* tail;
public:
    BrowserHistory() : head(NULL), tail(NULL) {}

    // Add a newly visited website at the end
    void visit(string site) {
        Node* newNode = new Node(site);
        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // first visited -> last visited (using next)
    void displayForward() {
        cout << "History (First -> Last):" << endl;
        Node* cur = head;
        int i = 1;
        while (cur != NULL) {
            cout << "  " << i++ << ". " << cur->website << endl;
            cur = cur->next;
        }
    }

    // last visited -> first visited (using prev)
    void displayBackward() {
        cout << "History (Last -> First):" << endl;
        Node* cur = tail;
        int i = 1;
        while (cur != NULL) {
            cout << "  " << i++ << ". " << cur->website << endl;
            cur = cur->prev;
        }
    }

    ~BrowserHistory() {
        while (head != NULL) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    BrowserHistory history;
    history.visit("google.com");
    history.visit("youtube.com");
    history.visit("github.com");
    history.visit("stackoverflow.com");
    history.visit("wikipedia.org");

    history.displayForward();
    cout << endl;
    history.displayBackward();
    return 0;
}
