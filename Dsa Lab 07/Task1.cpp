#include <iostream>
using namespace std;

#define SIZE 5

class BankQueue {
private:
    int items[SIZE];
    int front, rear;

public:
    BankQueue() {
        front = -1;
        rear = -1;
    }

    bool isFull() {
        return rear == SIZE - 1;
    }

    bool isEmpty() {
        return front == -1 || front > rear;
    }

    void enqueue(int token) {
        if (isFull()) {
            cout << "Queue Full!\n";
            return;
        }
        if (front == -1) front = 0;
        rear++;
        items[rear] = token;
        cout << "Added customer: " << token << "\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue Empty!\n";
            return;
        }
        cout << "Serving customer: " << items[front] << "\n";
        front++;
    }

    void display() {
        if (isEmpty()) {
            cout << "No waiting customers.\n";
            return;
        }
        cout << "Waiting customers: ";
        for (int i = front; i <= rear; i++) {
            cout << items[i] << " ";
        }
        cout << "\n";
    }

    void displayCount() {
        if (isEmpty()) {
            cout << "Total waiting: 0\n";
        } else {
            cout << "Total waiting: " << (rear - front + 1) << "\n";
        }
    }
};

int main() {
    BankQueue q;

    q.enqueue(101);
    q.enqueue(102);
    q.enqueue(103);

    q.display();
    q.displayCount();

    q.dequeue();

    q.display();
    q.displayCount();

    return 0;
}