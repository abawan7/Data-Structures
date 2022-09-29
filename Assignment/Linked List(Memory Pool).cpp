#include <iostream>
using namespace std;
template <typename T>
class list {
private:
    struct node {
        T data;
        node* next;
        node() {
            next = NULL;
        }
        node(T a, node* temp = 0) {
            data = a;
            next = temp;
        }
    };
    node* head;
    node* tail;
    int size = 0;
    class iterator {
    public:
        friend class list;
        iterator(node* ptr = NULL) {
            iptr = ptr;
        };
        iterator& operator++() {
            if (iptr) iptr = iptr->next;
            return (*this);
        }
        bool operator==(const iterator& l) const {
            return (iptr == l.iptr);
        }
        T& operator*() {
            return iptr->data;
        }
        bool operator!=(const iterator& l) const {
            return (iptr != l.iptr);
        }
    private:
        node* iptr;
    };
public:
    friend class memorysystem;
    list() {
        tail = new node();
        head = new node();
        head->next = tail;
        tail->next = NULL;
    }
    list(list& obj) {
        if (!obj.isEmpty()) {
            node* tmp;
            for (tmp = obj.head->next; tmp->next != NULL; tmp = tmp->next) {
                this->insertatend(tmp->data);
            }
            this->size = obj.size;
        }
    }
    void insertatstart(T val) {
        head->next = new node(val, head->next);
        size++;
    }
    void insertatend(T val) {
        node* temp = head;
        for (; temp->next != tail;) {
            temp = temp->next;
        }
        temp->next = new node(val, temp->next);
    }
    void deletefromstart() {
        if (!isEmpty()) {
            node* tmp = head->next;
            head->next = head->next->next;
            delete tmp;
            size--;
        }
    }
    void deletefromend() {
        node* temp = head->next;
        for (; temp->next->next != tail;) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = tail;
        size--;
    }
    void print() {
        node* tmp;
        for (tmp = head->next; tmp->next != NULL; tmp = tmp->next) {
            cout << tmp->data << " ";
        }
        cout << endl;
    }
    bool isEmpty() {
        return(!head->next->next);
    }
    void merge(list l1) {
        node* tmp;
        for (tmp = l1.head->next; tmp->next != NULL; tmp = tmp->next) {
            this->insertatend(tmp->data);
        }
    }
    int getSize() {
        return size;
    }
    void sort() {
        node* temp;
        node* temporary;
        for (temp = head->next; temp->next != NULL; temp = temp->next) {
            for (temporary = temp->next; temporary->next != NULL; temporary = temporary->next) {
                if (temp->data > temporary->data) {
                    T temp = temp->data;
                    temp->data = temporary->data;
                    temporary->data = temp;
                }
            }
        }
    }
    typedef iterator Iterator;
    Iterator begin() {
        Iterator I(head->next);
        return I;
    }
    Iterator end() {
        Iterator I(tail);
        return I;
    }
    ~list() {
        node* ptr = head->next;
        while (!isEmpty()) {
            deletefromstart();
        }
    }
};
class blocks{
public:
    int startingbyte;
    int totalbytes;
    blocks(int start_byte_ID, int total_bytes){
        this->startingbyte = start_byte_ID;
        this->totalbytes = total_bytes;
    }
    blocks(blocks& obj){
        this->startingbyte = obj.startingbyte;
        this->totalbytes = obj.totalbytes;
    }
    blocks operator=(blocks& obj){
        this->startingbyte = obj.startingbyte;
        this->totalbytes = obj.totalbytes;
        return *this;
    }
    void print(){
        cout << "Start byte ID: " << startingbyte << endl;
        cout << "Total bytes: " << totalbytes << endl;
    }
};
class programs{
public:
    int id;
    int size;
    list<blocks*> blockList;
    programs(int id, int size){
        this->id = id;
        this->size = size;
    }
    programs(programs& obj){
        this->id = obj.id;
        this->size = obj.size;
        this->blockList = obj.blockList;
    }
    void print(){
        cout << "Program id: " << id << endl;
        cout << "Program size: " << size << endl;
        cout << "In Block: " << endl;
        for (list<blocks*>::Iterator I = blockList.begin(); I != blockList.end(); ++I){
            cout << "Starting byte: " << (*I)->startingbyte << endl;
            cout << "Total bytes: " << (*I)->totalbytes << endl;
        }
    }
};
class memorysystem{
public:
    list<blocks*> pools;
    list<programs*> pp;
    int sizeOfMemory;
    bool strategy;
    memorysystem(int size = 1000, bool choice = 0){
        this->sizeOfMemory = size;
        this->strategy = choice;

        blocks* tmp = new blocks(0, sizeOfMemory);
        pools.insertatstart(tmp);
    }
    void newprogram(int id, int size){
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
        for (list<programs*>::Iterator dummy = pp.begin(); dummy != pp.end(); ++dummy){
            if ((*dummy)->id == id){
                flag = true;
                break;
            }
        }
        if (flag == true){
            for (list<programs*>::Iterator dummy = pp.begin(); dummy != pp.end(); ++dummy){
                if ((*dummy)->id == id){
                    for (list<blocks*>::Iterator trash = pools.begin(); trash != pools.end(); ++trash){
                        if ((*trash)->totalbytes >= size){
                            (*dummy)->blockList.insertatend(new blocks((*trash)->startingbyte, size));
                            (*trash)->startingbyte = (*trash)->startingbyte+ size;
                            (*trash)->totalbytes = (*trash)->totalbytes- size;
                            if ((*trash)->totalbytes == 0){
                                pools.deletefromstart();
                            }
                            break;
                        }
                    }
                }
            }
        }
        else{
            programs* temp = new programs(id, size);
            for (list<blocks*>::Iterator trash = pools.begin(); trash != pools.end(); ++trash){
                if ((*trash)->totalbytes >= size){
                    temp->blockList.insertatend(new blocks((*trash)->startingbyte, size));
                    (*trash)->startingbyte += size;
                    (*trash)->totalbytes -= size;
                    if ((*trash)->totalbytes == 0){
                        pools.deletefromstart();
                    }
                    break;
                }
            }
            pp.insertatend(temp);
        }
    }
    void bestFit(int id, int size) {
        bool flag = false;
        for (list<programs*>::Iterator dummy = pp.begin(); dummy != pp.end(); ++dummy){
            if ((*dummy)->id == id){
                flag = true;
                break;
            }
        }
        if (flag == true){
            for (list<programs*>::Iterator dummy = pp.begin(); dummy != pp.end(); ++dummy){
                if ((*dummy)->id == id){
                    int bestFit = 1000000000;
                    list<blocks*>::Iterator bestFitBlock;
                    for (list<blocks*>::Iterator J = pools.begin(); J != pools.end(); ++J){
                        if ((*J)->totalbytes >= size && (*J)->totalbytes < bestFit){
                            bestFit = (*J)->totalbytes;
                            bestFitBlock = J;
                        }
                    }
                    (*dummy)->blockList.insertatend(new blocks((*bestFitBlock)->startingbyte, size));
                    (*bestFitBlock)->startingbyte += size;
                    (*bestFitBlock)->totalbytes -= size;
                    if ((*bestFitBlock)->totalbytes == 0){
                        pools.deletefromstart();
                    }
                    break;
                }
            }
        }
        else{
            programs* trash = new programs(id, size);
            int bestFit = 1000000000;
            list<blocks*>::Iterator bestFitBlock;
            for (list<blocks*>::Iterator temp = pools.begin(); temp != pools.end(); ++temp){
                if ((*temp)->totalbytes >= size && (*temp)->totalbytes < bestFit){
                    bestFit = (*temp)->totalbytes;
                    bestFitBlock = temp;
                }
            }
            trash->blockList.insertatend(new blocks((*bestFitBlock)->startingbyte, size));
            (*bestFitBlock)->startingbyte += size;
            (*bestFitBlock)->totalbytes -= size;
            if ((*bestFitBlock)->totalbytes == 0){
                pools.deletefromstart();
            }
            pp.insertatend(trash);
        }
    }
    void removeprog(int id){
        for (list<programs*>::Iterator dummy = pp.begin(); dummy != pp.end(); ++dummy){
            if ((*dummy)->id == id){
                for (list<blocks*>::Iterator J = (*dummy)->blockList.begin(); J != (*dummy)->blockList.end(); ++J){
                    pools.insertatend(new blocks((*J)->startingbyte, (*J)->totalbytes));
                }
                pp.deletefromstart();
                break;
            }
        }
        this->sortpool();
        for (list<blocks*>::Iterator temp = pools.begin(); temp != pools.end(); ++temp){
            if ((*temp)->totalbytes == 0){
                pools.deletefromstart();
            }
        }
        this->merging();
    }
    void merging() {
        for (list<blocks*>::Iterator dummy = pools.begin(); dummy != pools.end(); ++dummy){
            list<blocks*>::Iterator temp = dummy;++temp;
            if (temp != pools.end()){
                if ((*dummy)->startingbyte + (*dummy)->totalbytes == (*temp)->startingbyte){
                    (*dummy)->totalbytes += (*temp)->totalbytes;
                    pools.deletefromstart();
                }
            }
        }
    }
    void sortpool() {
        for (list<blocks*>::Iterator it = pools.begin(); it != pools.end(); ++it){
            list<blocks*>::Iterator ite = it;
            ++ite;
            if (ite != pools.end()){
                if ((*it)->startingbyte > (*ite)->startingbyte){
                    blocks* tmp = *it;
                    *it = *ite;
                    *ite = tmp;
                }
            }
        }
    }
    void print(){
        cout << "Pool: " << endl;
        for (list<blocks*>::Iterator temp = pools.begin(); temp != pools.end(); ++temp){
            (*temp)->print();
        }
        cout << endl;
        cout << "Programs: " << endl;
        for (list<programs*>::Iterator temp = pp.begin(); temp != pp.end(); ++temp){
            (*temp)->print();
            cout << endl;
        }
    }
};
int main() {
    list<int> l1; int id, memory;
    memorysystem memman1(1000, 0);
    cout << "Enter first program id:" << endl;
    cin >> id;
    cout << "Enter required memory:" << endl;
    cin >> memory;
    memman1.newprogram(id, memory);
    cout << "Enter second program id:" << endl;
    cin >> id;
    cout << "Enter required memory:" << endl;
    cin >> memory;
    memman1.newprogram(id, memory);
    cout << "Enter third program id:" << endl;
    cin >> id;
    cout << "Enter required memory:" << endl;
    cin >> memory;
    memman1.newprogram(id, memory);
    cout << "Enter fourth program id:" << endl;
    cin >> id;
    cout << "Enter required memory:" << endl;
    cin >> memory;
    memman1.newprogram(id, memory);
    cout << "According to the first fit:" << endl;
    cout << "First: " << endl;
    memman1.print();
    cout << endl;
    memman1.removeprog(1);
    cout << "Second: " << endl;
    memman1.print();
    cout << endl;
    cout << "Now, according to the best fit:" << endl;
    memorysystem memman2(1000, 1);
    cout << "Enter first program id:" << endl;
    cin >> id;
    cout << "Enter required memory:" << endl;
    cin >> memory;
    memman2.newprogram(id, memory);
    cout << "Enter second program id:" << endl;
    cin >> id;
    cout << "Enter required memory:" << endl;
    cin >> memory;
    memman2.newprogram(id, memory);
    cout << "Enter third program id:" << endl;
    cin >> id;
    cout << "Enter required memory:" << endl;
    cin >> memory;
    memman2.newprogram(id, memory);
    cout << "Enter fourth program id:" << endl;
    cin >> id;
    cout << "Enter required memory:" << endl;
    cin >> memory;
    memman2.newprogram(id, memory);
    cout << "First: " << endl;
    memman2.print();
    memman2.removeprog(1);
    cout << "Second: " << endl;
    memman2.print();
    return 0;
}
