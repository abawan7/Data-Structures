#include <iostream>
using namespace std;
struct node {
    int Data;
    node* Next;
    int Freq;
};

class linkedlist {
public:
    linkedlist() {
        head = NULL;
    }

    void insert(int val) {
        node* Node = new node;
        Node->Data = val;
        Node->Next = head;
        Node->Freq = 1;
        head = Node;
    }

    void Unique() {
        node* cur = head;
        while (cur != NULL) {
            node* temp = cur->Next;
            while (temp != NULL) {
                if (temp->Data == cur->Data) {
                    cur->Freq++;
                    deleteNode(temp);
                    temp = cur->Next; // update temp after deletion
                }
                else {
                    temp = temp->Next;
                }
            }
            cur = cur->Next;
        }

        SortList();

        cur = head;
        while (cur != NULL && cur->Next != NULL) {
            if (cur->Data == cur->Next->Data) {
                node* temp = cur->Next;
                cur->Next = cur->Next->Next;
                delete temp;
            }
            else {
                cur = cur->Next;
            }
        }
    }

    void Print() {
        node* cur = head;
        cout << "L1: ";
        while (cur != NULL) {
            cout << cur->Data << "->";
            cur = cur->Next;
        }
        cout << "NULL" << endl;
    }
private:
    node* head;

    void deleteNode(node* Node) {
        if (Node == NULL) {
            return;
        }
        if (Node == head) {
            head = head->Next;
            delete Node;
            return;
        }
        node* cur = head;
        while (cur != NULL && cur->Next != Node) {
            cur = cur->Next;
        }
        if (cur == NULL) {
            return;
        }
        cur->Next = Node->Next;
        delete Node;
    }

    void SortList() {
        if (head == NULL || head->Next == NULL) {
            return;
        }
        node* cur = head;
        while (cur != NULL) {
            node* temp = cur->Next;
            while (temp != NULL) {
                if (cur->Freq < temp->Freq) {
                    swap(cur->Data, temp->Data);
                    swap(cur->Freq, temp->Freq);
                }
                temp = temp->Next;
            }
            cur = cur->Next;
        }
    }

};

int main() {
    linkedlist L1;
    L1.insert(2);
    L1.insert(100);
    L1.insert(12);
    L1.insert(5);
    L1.insert(6);
    L1.insert(5);
    L1.insert(2);
    L1.insert(1);
    L1.insert(5);

    cout << "Original List: ";
    L1.Print();
    L1.Unique();
    cout << "List after sorting: ";
    L1.Print();

    return 0;
}
