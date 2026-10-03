// Task 4: Music Playlist using Circular Singly Linked List
#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string song;
    Node* next;
    Node(string name) : song(name), next(NULL) {}
};

class Playlist {
private:
    Node* head;
    Node* tail;
    int count;
public:
    Playlist() : head(NULL), tail(NULL), count(0) {}

    void addSong(string name) {
        Node* newNode = new Node(name);
        if (head == NULL) {
            head = tail = newNode;
            tail->next = head;
        } else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head;          // last node links to first (no NULL)
        }
        count++;
    }

    void displayOnce() {
        cout << "Playlist (all songs once):" << endl;
        Node* cur = head;
        int i = 1;
        do {
            cout << "  " << i++ << ". " << cur->song << endl;
            cur = cur->next;
        } while (cur != head);
    }

    // Plays the playlist for a number of complete rounds
    void play(int rounds) {
        Node* cur = head;
        for (int r = 1; r <= rounds; r++) {
            cout << "Round " << r << ":" << endl;
            for (int i = 0; i < count; i++) {
                cout << "  Playing: " << cur->song << endl;
                cur = cur->next;        // after last song, goes to first
            }
        }
    }

    ~Playlist() {
        if (head == NULL) return;
        tail->next = NULL;
        while (head != NULL) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    Playlist p;
    p.addSong("Tum Hi Ho");
    p.addSong("Shape of You");
    p.addSong("Believer");
    p.addSong("Perfect");
    p.addSong("Closer");

    p.displayOnce();
    cout << endl;
    p.play(2);
    return 0;
}
