#include <iostream>
using namespace std;

template<class T>
class Stack{
public:
    T *arr;
    int max;
    int top;

    Stack(int size = 0){
        top = 0;
        arr = new T[size];
        max = size;
    }

    bool isFull(){
        return (top == max);
    }

    bool isEmpty(){
        return(top == 0);
    }

    bool Top(T &d){
        if (!isEmpty())
        {
            d = arr[top-1];
            return true;
        }
        else
        {
            return false;
        }
    }

    int size(){
        return top;
    }

    void push(T item){
        if (isFull()){
            cout << "Stack is full" << endl;
        }
        else {
            arr[top++] = item;
        }
    }

    void pop(){
        if (isEmpty()){
            cout << "Stack is empty" <<endl;
        }
        else {
            arr[--top];
        }
    }

    void display(){
        for (int i = top-1; i >= 0; i--){
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void transferWithStack(Stack<T>& t){
        Stack<T> c(size()); // create an additional stack c
        while (!isEmpty()){ // while stack s is not empty
            T elem;
            Top(elem); // pop an element from s
            c.push(elem); // push it onto stack c
            pop();
        }
        while (!c.isEmpty()){ // while stack c is not empty
            T elem;
            c.Top(elem); // pop an element from c
            t.push(elem); // push it onto stack t
            c.pop();
        }
    }

    void transferWithoutStack(Stack<T>& t){
        T temp;
        while(!isEmpty()){
            Top(temp);
            pop();
            while(!t.isEmpty() && t.arr[t.top-1] > temp){
                push(t.arr[t.top-1]);
                t.pop();
            }
            t.push(temp);
        }
    }
};

int main(){
    Stack<int> s(5);
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);

    Stack<int> t(5);
    cout << "Using One Additional Stack" << endl;
    cout << "Stack s: ";
    s.display();
    cout << "Stack t: ";
    t.display();

    s.transferWithStack(t);

    cout << "Stack s: ";
    s.display();
    cout << "Stack t: ";
    t.display();

    Stack<int> s1(5);
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);
    s1.push(5);

    Stack<int> t1(5);
    cout << "Using One Additional Stack" << endl;
    cout << "Stack s: ";
    s1.display();
    cout << "Stack t: ";
    t1.display();

    s1.transferWithoutStack(t1);

    cout << "Stack s: ";
    s1.display();
    cout << "Stack t: ";
    t1.display();

    return 0;
}
