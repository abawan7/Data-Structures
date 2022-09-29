#include<iostream>

using namespace std;

template<class T>
class Queue {
private:
    T *arr_que;
    int max_size;
    int size;
    int front, rear;
    int count = 0;

public:
    Queue(int s = 6) {
        arr_que = new T[s];
        size = 0;
        max_size = s;
        front = 0;
        rear = 0;
    }

    bool isFull() {
        return (size == max_size);
    }

    bool isEmpty() {
        return (size == 0);
    }

    bool push(T d) {
        if (!isFull()) {
            arr_que[rear % max_size] = d;
            size++;
            rear++;
            this->count++;
            return true;
        } else {
            return false;
        }
    }

    bool pop() {
        if (!isEmpty()) {
            front++;
            arr_que[front % max_size];
            size--;
            return true;
        } else {
            return false;
        }
    }


    void print() {
        for (int i = 0; i < size; i++) {
            cout << arr_que[i];
        }

    }

    void interLeaveQueue(Queue<int> &q) {
        if (q.size % 2 != 0) {
            cout << "Input even number of integers." << endl;
            return;
        }

        Queue<int> temp;
        int halfSize = size / 2;

        for (int i = 0; i < halfSize; i++) {
            int num = q.arr_que[front];
            temp.push(num);
            q.pop();
        }

        for (int i = 0; i < halfSize; i++) {
            q.push(temp.arr_que[i]);
            q.push(q.arr_que[front]);
            if (i != halfSize - 1) {
                q.pop();
                temp.pop();
            }
        }
    }
};

int main() {
    Queue<int> Q1;
    Q1.push(5);
    Q1.push(4);
    Q1.push(6);
    Q1.push(7);
    Q1.push(8);
    Q1.push(9);
    cout << "Element: ";
    Q1.print();
    cout << endl;
    cout << "After: ";
    Q1.interLeaveQueue(Q1);
    Q1.print();

    return 0;
}
