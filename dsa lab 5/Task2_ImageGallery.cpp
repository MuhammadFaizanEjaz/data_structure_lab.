// Task 2: Image Gallery using Doubly Linked List
#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string image;
    Node* prev;
    Node* next;
    Node(string name) : image(name), prev(NULL), next(NULL) {}
};

class ImageGallery {
private:
    Node* head;
    Node* tail;
public:
    ImageGallery() : head(NULL), tail(NULL) {}

    void addImage(string name) {
        Node* newNode = new Node(name);
        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void displayForward() {
        cout << "Gallery (First -> Last):" << endl;
        for (Node* cur = head; cur != NULL; cur = cur->next)
            cout << "  " << cur->image << endl;
    }

    void displayBackward() {
        cout << "Gallery (Last -> First):" << endl;
        for (Node* cur = tail; cur != NULL; cur = cur->prev)
            cout << "  " << cur->image << endl;
    }

    // Demonstrates movement in both directions with next and prev
    void demonstrateNavigation() {
        cout << "Navigation demo:" << endl;
        Node* cur = head;
        cout << "  Start at        : " << cur->image << endl;
        cur = cur->next;
        cout << "  next -> moved to: " << cur->image << endl;
        cur = cur->next;
        cout << "  next -> moved to: " << cur->image << endl;
        cur = cur->prev;
        cout << "  prev -> moved to: " << cur->image << endl;
        cur = cur->prev;
        cout << "  prev -> moved to: " << cur->image << endl;
    }

    ~ImageGallery() {
        while (head != NULL) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    ImageGallery gallery;
    gallery.addImage("sunset.jpg");
    gallery.addImage("mountain.png");
    gallery.addImage("beach.jpg");
    gallery.addImage("city_night.png");
    gallery.addImage("forest.jpg");

    gallery.displayForward();
    cout << endl;
    gallery.displayBackward();
    cout << endl;
    gallery.demonstrateNavigation();
    return 0;
}
