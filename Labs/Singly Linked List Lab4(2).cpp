#include<iostream>

using namespace std;

template<class T>
class Dlist {
private:
    class Dnode {
    public:
        T data;
        Dnode *next;
    };

    Dnode *tail;
public:
    Dlist() {
        tail = new Dnode;
        tail->next = tail;
    }

    void checkEmpty() {
        if (tail->next == tail) {
            cout << "Empty." << endl;
        } else {
            cout << "Not Empty." << endl;
        }
    }

    void print() {
        Dnode *temp = tail->next;
        for (; temp->next != tail;) {
            cout << temp->data << endl;
            temp = temp->next;
        }
        cout << temp->data << endl;
    }

    void Destroy() {
        Dnode *temp = tail->next;
        for (; temp->next != tail;) {
            temp->data = temp->next->data;
            temp->next = temp->next->next;
            delete temp->next;
            temp = temp->next;
        }
    }

    bool search(T d) {
        Dnode *temp = tail->next;
        for (; temp->next != tail;) {
            if (temp->data == d) {
                return true;
            }
        }
        return false;
    }

    void length() {
        Dnode *temp = tail->next;
        int count = 0;
        for (; temp->next != tail->next;) {
            count++;
            temp = temp->next;
        }
        cout << "Length of the list: " << count << endl;
    }

    void insertAtStart(T d) {
        Dnode *temp = new Dnode;
        temp->data = d;
        temp->next = tail->next;
        tail->next = temp;
    }

    void insertAtGivenPosition(T &d, T dd) {
        Dnode *temp = new Dnode;
        Dnode *cur = tail;
        temp->data = dd;
        for (int i = 2; i <= d; i++) {
            cur = cur->next;
        }
        temp->next = cur->next;
        cur->next = temp;
    }

    void insertAtEnd(T d) {
        Dnode *temp = new Dnode;
        Dnode *cur = tail->next;
        temp->data = d;
        for (; cur->next != tail;) {
            cur = cur->next;
        }
        cur->next = temp;
        temp->next = tail;
    }

    void deleteAtStart() {
        Dnode *temp = tail->next;
        tail->next = temp->next;
        delete temp;
    }

    void deleteAtGivenPosition() {
        int position;
        cout << "Enter position: ";
        cin >> position;

    }

    void deleteatend() {
        Dnode *temp = tail;
        while(temp->next!=tail)
        {
            temp=temp;
            temp=temp->next;
        }
        temp->next=tail;
        delete temp;
    }

    ~Dlist() {

    }
};

int main() {
    Dlist<int> l1;
    int d, input;
    l1.checkEmpty();
    l1.insertAtStart(1);
    l1.insertAtStart(2);
    l1.insertAtStart(3);
    l1.insertAtEnd(4);
    l1.insertAtEnd(5);
    l1.print();
    l1.length();
    cout << "Enter the position you want to enter d: ";
    cin >> input;
    cout << "Enter d: ";
    cin >> d;
    l1.insertAtGivenPosition(input, d);
    l1.print();
    l1.checkEmpty();
    l1.length();
    cout << "After deleting from start: ";
    l1.deleteAtStart();
    l1.print();
    cout << "After deleting from given position: ";
    l1.deleteAtGivenPosition();
    l1.print();
    cout << "After deleting from end: ";
    l1.deleteatend();
    l1.print();
    system("pause");
    return 0;
}
