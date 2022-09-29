
#include "iostream"

using namespace std;

template<class T>
class list {
private:
    class Node {
    public:
        T data;
        Node *next;
    };

    Node *head;
    Node *tail;
public:
    list() {
        head = tail = nullptr;
    }

    void insertSorted(T const element) {
        int num;
        Node *temp = new Node;
        temp->next = head;
        temp->data = element;
        if (head == nullptr) {
            head = tail = temp;
        } else {
            head = temp;
            Node *curr = temp->next;
            while (curr != nullptr) {
                if (temp->data > curr->data) {
                    num = temp->data;
                    temp->data = curr->data;
                    curr->data = num;
                } else {
                    curr = curr->next;
                    temp = temp->next;
                }
            }
        }
    }

    void print() {
        Node *current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
    }

    void search(T value) {
        Node *temp = head;
        while (temp != nullptr) {
            if (temp->data == value) {
                cout << "Y" << endl;
                break;
            } else {
                temp = temp->next;
            }
        }
        if (!temp) {
            cout << "N" << endl;
        }
    }

    void deleteAtStart() {
        if (head != nullptr) {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
        if (head == nullptr) {
            tail = nullptr;
        }
    }

    void deleteAtEnd() {
        if (head != nullptr) {
            if (head == tail) {
                delete head;
                head = tail = nullptr;
            } else {
                Node *t = head;
                while (t->next != tail) {
                    t = t->next;
                    delete tail;
                    tail = t;
                    tail->next = nullptr;
                }
            }
        }
    }

    void printIndex(T index) {
        Node *temp = head;
        int i = 0;
        while (i <= index) {
            if (i == index) {
                cout << temp->data << " ";
            }
            temp = temp->next;
            i++;
        }
    }

    void deleteDuplicate(){
        Node *temp = head;
        Node *curr = head->next;
        while (curr->next!= nullptr){
            if (temp->data==curr->data){
                head =temp->next;
                delete temp;
            }
            temp = temp->next;
            curr = curr->next;
        }
    }
};

int main() {
    list<int> l1;
    int search, index;
    l1.insertSorted(5);
    l1.insertSorted(15);
    l1.insertSorted(10);
    l1.insertSorted(8);
    l1.insertSorted(20);
    cout << "Sorted:  ";
    l1.print();
    cout << "\nSearch Value: ";
    cin >> search;
    l1.search(search);
    cout << "Search Index: ";
    cin >> index;
    cout << "Printing Index 2: ";
    l1.printIndex(2);
    l1.deleteAtEnd();
    cout << "Delete At End: ";
    l1.print();
    l1.deleteAtStart();
    cout << "Delete At Start: ";
    l1.print();
    l1.deleteDuplicate();
    cout << "Delete Duplicate: ";
    l1.print();
}