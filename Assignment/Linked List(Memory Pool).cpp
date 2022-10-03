#include <iostream>
using namespace std;
template <typename T>
class Singlylinkedlist {
private:
    struct Node {
        T data;
        Node* next;
        Node() {
            next = NULL;
        }
        Node(T a, Node* temp = 0) {
            data = a;
            next = temp;
        }
    };
    Node* head;
    Node* tail;
    int size = 0;
    class Iterator {
    private:
        Node* curr;
    public:
        friend class list;
        Iterator(Node* ptr = NULL) { //Iterator Constructor
            curr = ptr;
        };
        Iterator& operator++() {
            if (curr) curr = curr->next;
            return (*this);
        }
        bool operator==(const Iterator& l) const {
            return (curr == l.curr);
        }
        T& operator*() {
            return curr->data;
        }
        bool operator!=(const Iterator& l) const {
            return (curr != l.curr);
        }
    };
public:
    friend class MMS;
    Singlylinkedlist() {
        tail = new Node();
        head = new Node();
        head->next = tail;
        tail->next = NULL;
    }
    Singlylinkedlist(Singlylinkedlist& obj) { //Copy Constructor
        if (!obj.isEmpty()) {
            Node* tmp;
            for (tmp = obj.head->next; tmp->next != NULL; tmp = tmp->next) {
                this->insertAtEnd(tmp->data);
            }
            this->size = obj.size;
        }
    }
    void insertAtStart(T val) {
        head->next = new Node(val, head->next);
        size++;
    }
    void insertAtEnd(T val) {
        Node* temp = head;
        for (; temp->next != tail;) {
            temp = temp->next;
        }
        temp->next = new Node(val, temp->next);
    }
    void deleteFromStart() {
        if (!isEmpty()) {
            Node* tmp = head->next;
            head->next = head->next->next;
            delete tmp;
            size--;
        }
    }
    bool isEmpty() {
        return(!head->next->next);
    }

    typedef Iterator Iterator;
    Iterator begin() {
        Iterator I(head->next);
        return I;
    }
    Iterator end() {
        Iterator I(tail);
        return I;
    }
    ~Singlylinkedlist() {
        Node* ptr = head->next;
        while (!isEmpty()) {
            deleteFromStart();
        }
    }
};
class Blocks{
public:
    int start_byte;
    int total_bytes;
    Blocks(int start_byte_ID, int total_bytes){
        this->start_byte = start_byte_ID;
        this->total_bytes = total_bytes;
    }
    Blocks(Blocks& obj){
        this->start_byte = obj.start_byte;
        this->total_bytes = obj.total_bytes;
    }
    Blocks operator=(Blocks& obj){
        this->start_byte = obj.start_byte;
        this->total_bytes = obj.total_bytes;
        return *this;
    }
    void print(){
        cout << "Start byte ID: " << start_byte << endl;
        cout << "Total bytes: " << total_bytes << endl;
    }
};
class Program{
public:
    int id;
    int size;
    Singlylinkedlist<Blocks*> blockList;
    Program(int id, int size){
        this->id = id;
        this->size = size;
    }
    Program(Program& obj){
        this->id = obj.id;
        this->size = obj.size;
        this->blockList = obj.blockList;
    }
    void print(){
        cout << "Program id: " << id << endl;
        cout << "Program size: " << size << endl;
        cout << "In Block: " << endl;
        for (Singlylinkedlist<Blocks*>::Iterator I = blockList.begin(); I != blockList.end(); ++I){
            cout << "Starting byte: " << (*I)->start_byte << endl;
            cout << "Total bytes: " << (*I)->total_bytes << endl;
        }
    }
};
class MMS{
public:
    Singlylinkedlist<Blocks*> pools;
    Singlylinkedlist<Program*> pp;
    int sizeOfMemory;
    bool strategy;
    MMS(int size = 1000, bool choice = 0){
        this->sizeOfMemory = size;
        this->strategy = choice;

        Blocks* tmp = new Blocks(0, sizeOfMemory);
        pools.insertAtStart(tmp);
    }
    void newProgram(int id, int size){
        if (size > sizeOfMemory){
            cout << "Program too large to fit in memory" << endl;
            return;
        }
        if (strategy == 0){
            firstFit(id, size);
        }
        else{
            bestFit(id, size);
        }
    }
    void firstFit(int id, int size){
        bool flag = false;
        for (Singlylinkedlist<Program*>::Iterator dummy = pp.begin(); dummy != pp.end(); ++dummy){
            if ((*dummy)->id == id){
                flag = true;
                break;
            }
        }
        if (flag == true){
            for (Singlylinkedlist<Program*>::Iterator dummy = pp.begin(); dummy != pp.end(); ++dummy){
                if ((*dummy)->id == id){
                    for (Singlylinkedlist<Blocks*>::Iterator trash = pools.begin(); trash != pools.end(); ++trash){
                        if ((*trash)->total_bytes >= size){
                            (*dummy)->blockList.insertAtEnd(new Blocks((*trash)->start_byte, size));
                            (*trash)->start_byte = (*trash)->start_byte + size;
                            (*trash)->total_bytes = (*trash)->total_bytes - size;
                            if ((*trash)->total_bytes == 0){
                                pools.deleteFromStart();
                            }
                            break;
                        }
                    }
                }
            }
        }
        else{
            Program* temp = new Program(id, size);
            for (Singlylinkedlist<Blocks*>::Iterator trash = pools.begin(); trash != pools.end(); ++trash){
                if ((*trash)->total_bytes >= size){
                    temp->blockList.insertAtEnd(new Blocks((*trash)->start_byte, size));
                    (*trash)->start_byte += size;
                    (*trash)->total_bytes -= size;
                    if ((*trash)->total_bytes == 0){
                        pools.deleteFromStart();
                    }
                    break;
                }
            }
            pp.insertAtEnd(temp);
        }
    }
    void bestFit(int id, int size) {
        bool flag = false;
        for (Singlylinkedlist<Program*>::Iterator dummy = pp.begin(); dummy != pp.end(); ++dummy){
            if ((*dummy)->id == id){
                flag = true;
                break;
            }
        }
        if (flag == true){
            for (Singlylinkedlist<Program*>::Iterator dummy = pp.begin(); dummy != pp.end(); ++dummy){
                if ((*dummy)->id == id){
                    int bestFit = 1000000000;
                    Singlylinkedlist<Blocks*>::Iterator bestFitBlock;
                    for (Singlylinkedlist<Blocks*>::Iterator J = pools.begin(); J != pools.end(); ++J){
                        if ((*J)->total_bytes >= size && (*J)->total_bytes < bestFit){
                            bestFit = (*J)->total_bytes;
                            bestFitBlock = J;
                        }
                    }
                    (*dummy)->blockList.insertAtEnd(new Blocks((*bestFitBlock)->start_byte, size));
                    (*bestFitBlock)->start_byte += size;
                    (*bestFitBlock)->total_bytes -= size;
                    if ((*bestFitBlock)->total_bytes == 0){
                        pools.deleteFromStart();
                    }
                    break;
                }
            }
        }
        else{
            Program* trash = new Program(id, size);
            int bestFit = 1000000000;
            Singlylinkedlist<Blocks*>::Iterator bestFitBlock;
            for (Singlylinkedlist<Blocks*>::Iterator temp = pools.begin(); temp != pools.end(); ++temp){
                if ((*temp)->total_bytes >= size && (*temp)->total_bytes < bestFit){
                    bestFit = (*temp)->total_bytes;
                    bestFitBlock = temp;
                }
            }
            trash->blockList.insertAtEnd(new Blocks((*bestFitBlock)->start_byte, size));
            (*bestFitBlock)->start_byte += size;
            (*bestFitBlock)->total_bytes -= size;
            if ((*bestFitBlock)->total_bytes == 0){
                pools.deleteFromStart();
            }
            pp.insertAtEnd(trash);
        }
    }
    void removeProg(int id){
        for (Singlylinkedlist<Program*>::Iterator dummy = pp.begin(); dummy != pp.end(); ++dummy){
            if ((*dummy)->id == id){
                for (Singlylinkedlist<Blocks*>::Iterator J = (*dummy)->blockList.begin(); J != (*dummy)->blockList.end(); ++J){
                    pools.insertAtEnd(new Blocks((*J)->start_byte, (*J)->total_bytes));
                }
                pp.deleteFromStart();
                break;
            }
        }
        this->sortPool();
        for (Singlylinkedlist<Blocks*>::Iterator temp = pools.begin(); temp != pools.end(); ++temp){
            if ((*temp)->total_bytes == 0){
                pools.deleteFromStart();
            }
        }
        this->merge();
    }
    void merge() {
        for (Singlylinkedlist<Blocks*>::Iterator dummy = pools.begin(); dummy != pools.end(); ++dummy){
            Singlylinkedlist<Blocks*>::Iterator temp = dummy;++temp;
            if (temp != pools.end()){
                if ((*dummy)->start_byte + (*dummy)->total_bytes == (*temp)->start_byte){
                    (*dummy)->total_bytes += (*temp)->total_bytes;
                    pools.deleteFromStart();
                }
            }
        }
    }
    void sortPool() {
        for (Singlylinkedlist<Blocks*>::Iterator it = pools.begin(); it != pools.end(); ++it){
            Singlylinkedlist<Blocks*>::Iterator ite = it;
            ++ite;
            if (ite != pools.end()){
                if ((*it)->start_byte > (*ite)->start_byte){
                    Blocks* tmp = *it;
                    *it = *ite;
                    *ite = tmp;
                }
            }
        }
    }
    void print(){
        cout << "Pool: " << endl;
        for (Singlylinkedlist<Blocks*>::Iterator temp = pools.begin(); temp != pools.end(); ++temp){
            (*temp)->print();
        }
        cout << endl;
        cout << "Programs: " << endl;
        for (Singlylinkedlist<Program*>::Iterator temp = pp.begin(); temp != pp.end(); ++temp){
            (*temp)->print();
            cout << endl;
        }
    }
};
int main() {
    Singlylinkedlist<int> l1; int id, memory;
    MMS memman1(1000, 0);
    cout << "Enter first program id:" << endl;
    cin >> id;
    cout << "Enter required memory:" << endl;
    cin >> memory;
    memman1.newProgram(id, memory);
    cout << "Enter second program id:" << endl;
    cin >> id;
    cout << "Enter required memory:" << endl;
    cin >> memory;
    memman1.newProgram(id, memory);
    cout << "Enter third program id:" << endl;
    cin >> id;
    cout << "Enter required memory:" << endl;
    cin >> memory;
    memman1.newProgram(id, memory);
    cout << "Enter fourth program id:" << endl;
    cin >> id;
    cout << "Enter required memory:" << endl;
    cin >> memory;
    memman1.newProgram(id, memory);
    cout << "According to the first fit:" << endl;
    cout << "First: " << endl;
    memman1.print();
    cout << endl;
    memman1.removeProg(1);
    cout << "Second: " << endl;
    memman1.print();
    cout << endl;
    cout << "Now, according to the best fit:" << endl;
    MMS memman2(1000, 1);
    cout << "Enter first program id:" << endl;
    cin >> id;
    cout << "Enter required memory:" << endl;
    cin >> memory;
    memman2.newProgram(id, memory);
    cout << "Enter second program id:" << endl;
    cin >> id;
    cout << "Enter required memory:" << endl;
    cin >> memory;
    memman2.newProgram(id, memory);
    cout << "Enter third program id:" << endl;
    cin >> id;
    cout << "Enter required memory:" << endl;
    cin >> memory;
    memman2.newProgram(id, memory);
    cout << "Enter fourth program id:" << endl;
    cin >> id;
    cout << "Enter required memory:" << endl;
    cin >> memory;
    memman2.newProgram(id, memory);
    cout << "First: " << endl;
    memman2.print();
    memman2.removeProg(1);
    cout << "Second: " << endl;
    memman2.print();
    return 0;
}
