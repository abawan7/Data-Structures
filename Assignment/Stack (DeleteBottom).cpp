#include "iostream"

using namespace std;

template<class T>
class Stack {
private:
    T *arr;
    int max_size;
    int top;
public:
    Stack(int s = 0) {
        arr = new T[s];
        max_size = s;
        top = 0;
    }

    bool isEmpty() {
        return (top == 0);
    }

    bool isFull() {
        return (top == max_size);
    }

    void push(T item) {
        if (isFull()) {
            cout << "\n## Stack is Full!";
        } else {
            cout << "\n## Position : " << top << ", Pushed Value  :" << item;
            arr[top++] = item;
        }
    }

    void pop() {
        if (isEmpty()) {
            cout << "\n## Stack is Empty!";
        } else {
            for (int i = 0; i <top; i++){
                arr[i] = arr[i+1];
            }
            --top;
            cout << "\n## Position : 1 Popped Value  :" << arr[0];
        }
    }

    void display() {
        cout << "\n## Stack Size : " << top;
        for (int i = (top - 1); i >= 0; i--)
            cout << "\n## Position : " << i << ", Value  :" << arr[i];
    }
    int getTop(){
        return top;
    }

};

int main() {
    int choice, exit_p = 1, size, push;
    cout << "\nQ3: UndoStack\n\n";
    cout << "Enter The Size of Stack: ";
    cin >> size;
    Stack<int> obj(101);
    int i = 1;
    while (i < 100){
        obj.push(i);
        i++;
    }
    do {
        cout << "\n\nStack Main Menu";
        cout << "\nEnter Your Choice : ";
        cout << "\n1.To Push Value: ";
        cout << "\n2.To Display: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter value you want to push: ";
                cin >> push;
                if (obj.getTop() >= 100){
                    obj.pop();
                }
                obj.push(push);
                break;
            case 2:
                obj.display();
                break;
            default:
                exit_p = 0;
                break;
        }
    } while (exit_p);

    obj.display();
    return 0;
}
