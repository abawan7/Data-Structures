#include<iostream>
using namespace std;

template<typename t>
class CListHistory
{
    struct Node
    {
        Node* Next = 0;
        Node* Pre = 0;
        t Data;
    };
    Node* head;
public:
    CListHistory()
    {
        head = 0;
    }
    void menu()
    {
        Node* curr = 0;
        Node* curr1 = 0;
        cout << "Press 1 for Search/Insert new Tab: " << endl;
        cout << "Press 2 for going to previous Tab: " << endl;
        cout << "Press 3 for going to Next Tab: " << endl;
        cout << "Press 4 for Deleting a Tab: " << endl;
        int num;

        while (1) {
            cout << "Select Option: " << endl;
            cin >> num;
            //For Searching in a new tab
            if (num == 1)
            {
                string s;
                cout << "Enter TO Search: " << endl;
                cin >> s;
                //When no Node/tab exists
                if (!head)
                {
                    head = new Node;
                    head->Data = s;
                    head->Next = head;
                    head->Pre = head;
                    curr = head;
                    cout << "Your Current Tab is : " << curr->Data << endl;
                }
                    //Searching in between tabs
                else
                {
                    curr1 = new Node;
                    curr1->Data = s;
                    curr1->Pre = curr;
                    curr1->Next = curr->Next;
                    curr->Next = curr1;
                    curr = curr1;
                    cout << "Current Tab is : " << curr->Data << endl;
                }
            }
                //Going to back tab
            else if (num == 2)
            {
                curr = curr->Pre;
                cout << "Current Tab is " << curr->Data << endl;
            }
                //Going to Next Tab i-e Forwarding
            else if (num == 3)
            {
                curr = curr->Next;
                cout << "Current Tab is: " << curr->Data << endl;
            }
                //For Deleting a Tab
            else if (num == 4)
            {
                //When there is no tab
                if (!head)
                {
                    cout << "No Tab Exists to Be Deleted: " << endl;
                }
                    //Deleting at Head if only one Node/tab
                else if (curr->Pre == head && curr->Next == head)
                {
                    delete head;
                    head = 0;
                    cout << "There was only one tab that has been deleted : " << endl;
                }
                else
                {
                    curr1 = curr;
                    curr = curr1->Pre;
                    curr->Next = curr1->Next;
                    delete curr1;
                    cout << "Your Current Tab is: " << curr->Data << endl;
                }
            }
            else
            {
                cout << "Invalid Input: " << endl;
                break;
            }
        }
    }
};
int main()
{
    CListHistory<string> h;
    h.menu();

    return 0;
}
