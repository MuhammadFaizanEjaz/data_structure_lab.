#include <iostream>
using namespace std;

#define SIZE 5

class CircularPacketQueue {
private:
    int items[SIZE];
    int front, rear;

public:
    CircularPacketQueue() {
        front = -1;
        rear = -1;
    }

    bool isFull() {
        return (front == 0 && rear == SIZE - 1) || (front == rear + 1);
    }

    bool isEmpty() {
        return front == -1;
    }

    void enqueue(int packetId) {
        if (isFull()) {
            cout << "Buffer Full!\n";
            return;
        }
        if (front == -1) front = 0;
        rear = (rear + 1) % SIZE;
        items[rear] = packetId;
        cout << "Buffered packet: " << packetId << "\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Buffer Empty!\n";
            return;
        }
        cout << "Transmitted packet: " << items[front] << "\n";
        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % SIZE;
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "No packets waiting.\n";
            return;
        }
        cout << "Waiting packets: ";
        int i = front;
        while (true) {
            cout << items[i] << " ";
            if (i == rear) break;
            i = (i + 1) % SIZE;
        }
        cout << "\n";
    }
};

int main() {
    CircularPacketQueue queue;

    queue.enqueue(2001);
    queue.enqueue(2002);
    queue.enqueue(2003);
    queue.enqueue(2004);
    queue.enqueue(2005);

    queue.display();

    queue.dequeue();
    queue.dequeue();

    queue.display();

    queue.enqueue(2006);
    queue.display();

    return 0;
}