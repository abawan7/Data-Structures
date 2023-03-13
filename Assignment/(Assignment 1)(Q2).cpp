#include<iostream>
using namespace std;
class stack
{
    char* arr;
    int currentelements;
    int size;
public:
    stack()
    {
        size = 10;
        arr = new char[size];
        currentelements = 0;
    }
    void push(char ele)
    {
        if (currentelements == size)
        {
            char* arr1 = new char[size];
            for (int i = 0; i < size; i++)
            {
            arr1[i] = arr[i];
            }
            delete[]arr;
            arr = new char[size * 2];
            for (int i = 0; i < size; i++)
            {
            arr[i] = arr1[i];
            }
            size=size*2;
        }
        else
        {
        arr[currentelements] = ele;
        currentelements++;
        }
    }
    char top()
    {
        return arr[currentelements - 1];
    }
    bool empty()
    {
        return (currentelements == 0);
    }
    void pop()
    {
        currentelements--;
    }
};
int precedence(char op)
{
    if(op == '+' || op == '-')
    {
        return 1;
    }
    else if(op == '*' || op == '/')
    {
        return 2;
    }
    return 0;
}
string convert(string infix)
{
    stack ops;
    int i=0;
    string postfix;
    while(infix[i]!='\0')
    {
        if (infix[i] >= '0' && infix[i] <= '9' || infix[i] >= 'a' && infix[i] <= 'z' || infix[i] >= 'A' && infix[i] <= 'Z')
        {
            postfix = postfix + infix[i];
            i++;
        }
        postfix = postfix + ' ';
        if (infix[i] == '(')
        {
            ops.push(infix[i]);
            i++;
        }
        else if (infix[i] == ')')
        {
            while (ops.top() != '(')
            {
                postfix = postfix + ops.top();
                ops.pop();
            }
            ops.pop();
            i++;
        }
        else
        {
            while (!ops.empty() && precedence(infix[i]) <= precedence(ops.top()))
            {
                postfix = postfix + ops.top();
                ops.pop();
            }
            ops.push(infix[i]);
            i++;
        }
    }
    while (!ops.empty())
    {
        postfix = postfix + ops.top();
        ops.pop();
    }
    return postfix;
}
int main()
{
    string infix;
    cout << "Enter Your Postfix Expression:\t";
    cin >> infix;
    cout << "The Post Fix is:\t" << convert(infix) << endl;
    return 0;
}
