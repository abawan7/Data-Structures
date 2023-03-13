#include <iostream>

using namespace std;

template<typename T>
class Queue {
private:
    T *items;
    int front, rear, maxSize;
public:
    Queue(int size) {
        items = new T[size];
        maxSize = size;
        front = -1;
        rear = -1;
    }

    ~Queue() {
        delete[] items;
    }

    bool isFull() {
        return rear == maxSize - 1;
    }

    bool isEmpty() {
        return front == -1 || front > rear;
    }

    void enqueue(T item) {
        if (isFull()) {
            cout << "Queue is full." << endl;
            return;
        }

        rear++;
        items[rear] = item;

        if (front == -1) {
            front++;
        }
    }

    T dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return T();
        }

        T item = items[front];
        front++;

        if (front > rear) {
            front = rear = -1;
        }

        return item;
    }

    int size() {
        if (isEmpty()) {
            return 0;
        }

        return rear - front + 1;
    }

    T frontItem() {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return T();
        }

        return items[front];
    }

    T rearItem() {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return T();
        }

        return items[rear];
    }

    void twoQueueSort() {
        if (size() <= 1) {
            return;
        }
        Queue<T> q1(maxSize);
        Queue<T> q2(maxSize);
        // Use the front item as the pivot
        T pivot = dequeue();
        while (!isEmpty()) {
            T item = dequeue();
            if (item < pivot) {
                q1.enqueue(item);
            } else {
                q2.enqueue(item);
            }
        }
        // Recursively sort the two sub-queues
        q1.twoQueueSort();
        q2.twoQueueSort();
        // Merge the sorted sub-queues with the pivot element
        while (!q1.isEmpty()) {
            enqueue(q1.dequeue());
        }
        enqueue(pivot);
        while (!q2.isEmpty()) {
            enqueue(q2.dequeue());
        }
    }

    void oneQueueSort() {
        if (size() <= 1) {
            return;
        }
        Queue<T> q1(maxSize);
        Queue<T> q2(maxSize);
        // Use the front item as the pivot
        T pivot = dequeue();
        while (!isEmpty()) {
            T item = dequeue();
            if (item < pivot) {
                q1.enqueue(item);
            } else {
                q2.enqueue(item);
            }
        }
        // Recursively sort the two sub-queues
        q1.twoQueueSort();
        q2.twoQueueSort();
        // Merge the sorted sub-queues with the pivot element
        while (!q1.isEmpty()) {
            enqueue(q1.dequeue());
        }
        enqueue(pivot);
        while (!q2.isEmpty()) {
            enqueue(q2.dequeue());
        }
    }
};

int main() {
    Queue<int> q(5);

    q.enqueue(4);
    q.enqueue(1);
    q.enqueue(3);
    q.enqueue(5);
    q.enqueue(2);
    q.twoQueueSort();
    cout << "After Using Two Additional Queues:  ";
    while (!q.isEmpty()) {
        cout << q.dequeue() << " ";
    }
    Queue<int> q1(5);
    q1.enqueue(4);
    q1.enqueue(1);
    q.enqueue(3);
    q1.enqueue(5);
    q1.enqueue(2);
    q1.oneQueueSort();
    cout << "After Using Two Additional Queues:  ";
    while (!q1.isEmpty()) {
        cout << q1.dequeue() << " ";
    }
    return 0;
}
