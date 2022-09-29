#include "iostream"

using namespace std;

template<class T>
class Dlist {
private:
    class DNode {
    public:
        T data;
        DNode *next;
        DNode *prev;
    };

    DNode *head;
    DNode *tail;
public:
    Dlist() {
        head = new DNode;
        tail = new DNode;
        head->next = tail;
        tail->next = nullptr;
        head->prev = nullptr;
        tail->prev = head;
    }

    void InsertStart(T d) {
        DNode *temp = new DNode;
        temp->data = d;
        temp->prev = head;
        temp->next = head->next;
        head->next->prev = temp;
        head->next = temp;
    }

    void InsertAtEnd(T d) {
        DNode *temp = new DNode;
        temp->data = d;
        temp->next = tail;
        temp->prev = tail->prev;
        tail->prev->next = temp;
        tail->prev = temp;
    }

    void DeleteAtEnd(){
        DNode * temp = tail->prev;
        temp->prev->next = tail;
        tail->prev = temp->prev;
        delete temp;
    }

    void DeleteAtStart(){
        DNode *temp = head->next;
        head->next->prev = head;
        head->next = temp->next;
        delete temp;
    }

    void print() {
        DNode *current = head->next;
        while (current != tail) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void printreverse(){
        DNode *current = tail->prev;
        while (current!= head->next) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << current->data << " " << endl;
    }

    void swap(int n1){
        DNode* temp=head->next;
        DNode *curr = tail->prev;
        int t;
        for(int i = 0; i <= n1; i++){
            if (i == n1){
                t = temp->data;
                temp->data = curr->data;
                curr->data = t;
            }
            temp = temp->next;
            curr = curr->prev;
        }

    }

    ~Dlist(){
        while (head->next){
            DeleteAtStart();
        }
    }
};

int main(){
    Dlist<int>d1;
    d1.InsertStart(5);
    d1.InsertStart(6);
    d1.InsertStart(7);
    d1.InsertStart(8);
    cout << "Output: ";
    d1.print();
    d1.swap(1);
    cout << "After Swapping: ";
    d1.print();
    cout << "Reverse Print: ";
    d1.printreverse();
    d1.DeleteAtStart();
    cout << "Delete At Start: ";
    d1.print();
    d1.DeleteAtEnd();
    cout << "Delete At End: ";
    d1.print();
}