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
        cout << "Position: " << top << " Popped Value: " << arr[top] << endl;
    }
}

bool isBalanced(char* s) {
    char ch;
    int count = 0, chk=  0;
    Stack<char> a((strlen(s)));
    for (int i = 0; s[i] != '\0' ; i++){
    if(s[i] == '{' || s[i] == '[' || s[i] == '('){
        a.push(s[i]);
    }
    if(s[i] == '}' || s[i] == ']' || s[i] == ')'){
        if(!a.isEmpty()){
            pop();
            count++;
        }
        chk++;
    }
    }
    if(chk%2 == 0 && count==chk/2){
        return true;
    }
    return false;
}




void display(){
    for (int i = (top - 1);i >= 0; i-- ){
        cout << arr[i] << " ";
    }
}

};



int main(){
    char * expr;
    Stack<char> obj(10);
    int size;
    cout << "Enter Size: ";
    cin >> size;
    expr = new char[size];
    for(int i = 0; i < size; i++){
    cin >> expr[i];
    }
    if (obj.isBalanced(expr))
      cout << "Balanced" << endl;
   else
      cout << "Not Balanced" << endl;
    system("pause");
}
