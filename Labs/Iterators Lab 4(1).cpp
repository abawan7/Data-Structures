#include<iostream>

using namespace std;

template<class t>
class Dlist {
private:
    class Dnode {
    public:
        t data;
        Dnode *next, *prev;
    };

    Dnode *head, *tail;
public:
    class iterator {
        friend class Dlist<t>;

    private:
        Dnode *curr;

        iterator(Dnode *c) {
            curr = c;
        }

    public:
        iterator() {
            curr = NULL;
        }

        t &operator*() {
            return curr->data;
        }

        iterator &operator++() {
            curr = curr->next;
            return *this;
        }

        bool operator!=(iterator &it) {
            if (curr != it.curr) {
                return true;
            }
            return false;
        }

        iterator &operator++(int) {
            iterator old = *this;
            curr = curr->next;
            return old;
        }

        iterator &operator--() {
            curr = curr->prev;
            return *this;
        }
    };

    Dlist() {
        head = new Dnode;
        tail = new Dnode;
        head->next = tail;
        head->prev = NULL;
        tail->next = NULL;
        tail->prev = head;
    }

    iterator begin() {
        iterator it = (head->next);
        return it;
    }

    iterator end() {
        iterator it = (tail);
        return it;
    }

    void insert(iterator it, t d) {
        Dnode *temp = new Dnode;
        temp->data = d;
        Dnode *tt = it.curr;
        temp->next = tt;
        temp->prev = tt->prev;
        tt->prev->next = temp;
        tt->prev = temp;
    }

    iterator remove(iterator it) {
        Dnode *tt = it.curr;
        tt->prev->next = tt->next;
        tt->next->prev = tt->prev;
        iterator ite(tt->next);
        delete tt;
        return ite;
    }

    void insertAtStart(t d) {
        insert(begin(), d);
    }

    void insertAtEnd(t d) {
        insert(end(), d);
    }

    void removeAtStart() {
        remove(begin());
    }

    void removeAtEnd() {
        remove(--end());
    }

    void print() {
        iterator it = head->next;
        Dnode *temp = head->next;
        for (; temp->next != tail->next; ++it) {
            cout << *(it) << endl;
            temp = temp->next;
        }
    }

    void printnode(t element) {
        iterator it = head;
        for (int i = 1; i <= element; i++, ++it) {
        }
        cout << "Index Value is: "<< *(it) << endl;
    }

    bool search(t element) {
        iterator it = head->next;
        Dnode *temp = head->next;
        while (temp->next != tail->next) {
            if (*it == element) {
                return true;
            }
            temp = temp->next;
            ++it;
        }
        return false;
    }

    int sum() {
        int sum = 0;
        iterator it = head->next;
        Dnode *temp = head->next;
        for (; temp->next != tail->next; ++it) {
            sum += *it;
            temp = temp->next;
        }
        return sum;
    }

    ~Dlist() {

    }
};

int main() {
    Dlist<int> l1;
    Dlist<int>::iterator it;
    int input;
    for (int i = 0; i < 5; i++) {
        cout << "Insert: ";
        cin >> input;
        l1.insertAtStart(input);
    }
    l1.print();
    int sum = l1.sum();
    cout << "Sum is: " << sum << endl;
    cout << "Search Index: ";
    cin >> input;
    l1.printnode(input);
    cout << "Search Value: ";
    cin >> input;
    bool flag = l1.search(input);
    if (flag) {
        cout << "Found" << endl;
    } else {
        cout << "Not Found" << endl;
    }
    l1.removeAtEnd();
    cout << "After removing from the end:" << endl;

    l1.print();
    sum = l1.sum();
    cout << "Sum is: " << sum << endl;
    l1.removeAtStart();
    cout << "Removing from the start:" << endl;
    l1.print();
    sum = l1.sum();
    cout << "Sum is: " << sum << endl;

    return 0;
}

