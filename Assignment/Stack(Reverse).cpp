\\reverse Stack
#include "iostream"
using namespace std;

template<class T>
class Stack {
public:
    T *arr;
    int max_size;
    int top;

    Stack(int s = 0) {
        arr = new T[s];
        max_size = s;
        top = 0;
    }
    int checkfull() {
        return (top >= max_size-1);
    }

    int checkifempty() {
        return (top == -1);
    }

    void Push(T num) {
        if (isFull())
            cout << "Stack is Full!" << endl;
        else {
            arr[top + 1] = num;
            top++;
        }
    }

    int Pop() {
        if (isEmpty())
            cout << "Stack is Empty!" << endl;
        else {
            top = top - 1;
            return arr[top+1];
        }
    }

    void display(){
        if(!isEmpty())
        {
            int temp = pop();
            display();
            cout << temp << " ";
            push(temp);
        }
    }

    void Insertatbottom(T item) {
        if (isEmpty()) {
            push(item);
        } else {
            int top = pop();
            insertAtBottom(item);
            push(top);
        }
    }

    void Reverse() {
        if (!isEmpty()) {
            int top = pop();
            reverse();
            insertAtBottom(top);
        }
    }
};

int main() {
    Stack<int> obj(6);
    obj.push(1);
    obj.push(2);
    obj.push(3);
    obj.push(4);
    obj.push(5);
    obj.push(6);
    cout << "Original Stack\n";
    obj.display();
    obj.reverse();
    cout << "\nReversed Stack\n";
    obj.display();
    return 0;
}
