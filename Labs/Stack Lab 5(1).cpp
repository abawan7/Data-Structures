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
    return(top == max);
}

bool top (T &d){
    if (!isEmpty)
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
    return max;
}

void push(T item){
    if (isFull()){
    cout << "Stack is full" << endl;
    }
    else {
        cout << "Position: " << top << "Pushed value: " << item  << endl;
        arr[top++] = item;
    }
}

void pop(){
    if (isEmpty()){
        cout << "Stack Is Empty" <<endl;
    }
    else
    {
        --top;
        cout << "Position: " << top << " Popped Value: " << arr[top];
    }
}


void display(){
    for (int i = (top - 1);i >= 0; i-- ){
        cout << arr[i] << " ";
    }
}

};

int main(){
    Stack<int> obj(6);
    obj.push(1);
    obj.push(2);
    obj.push(3);
    obj.push(4);
    obj.push(5);
    obj.push(6);
    obj.display();
    obj.pop();
    obj.display();
    system("pause");
}
