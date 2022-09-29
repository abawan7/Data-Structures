#include<iostream>
using namespace std;
template<class t>
class list {
private:
	class node {
	public:
		t data;node*next;
	};
	node*head, *tail;
public:
	list() {
		head = tail = NULL;
	}
	void insertatstart(t const element) {
		node*temp = new node;
		temp->data = element;
		temp->next = head;
		if (head == NULL) {
			head = tail = temp;
		}
		else {
			head = temp;
		}
	}
	void insertatend(t const element) {
		node*temp = new node;
		if (head == NULL) {
			insertatstart(element);
		}
		else {
			temp->data = element;
			temp->next = NULL;
			tail->next = temp;
			tail = temp;
		}
	}
	bool search(t const& element) const {
		node*current = head;
		while (current != NULL) {
			if (current->data == element) {
				return true;
			}
			else {
				current = current->next;
			}
		}
		return false;
	}
	bool isempty() const {
		if (head == NULL) {
			return true;
		}
		else {
			return false;
		}
	}
	void print()const {
		node*current = head;
		while (current != NULL) {
			cout << current->data << " ";
			current = current->next;
		}
	}
	void printrev() const {
		int count = 1;
		node*temp = head;
		while (temp->next != NULL) {
			count++;
			temp = temp->next;
		}
		temp = head;
		for (int i = 1;i <= count;i++) {
			if (i == count) {
				cout << temp->data << " ";
				count--;i = 1;
				temp = head;
			}
			temp = temp->next;
		}
		temp = head;
		cout << temp->data << endl;
	}
};
int main() {
	list<int> l1;int value;
	l1.insertatstart(4);
	l1.insertatstart(7);
	l1.insertatstart(9);
	l1.insertatend(2);
	l1.insertatstart(3);
	l1.insertatstart(7);
	l1.insertatstart(1);
	l1.print();
	cout << "\nEnter the value you want to search: ";
	cin >> value;
	while (value != 0) {
		if (l1.search(value)) {
			cout << "'" << value << "'" << " exists." << endl;
		}
		else {
			cout << "'" << value << "'" << " does not exist." << endl;
		}
		cout << "\nEnter the value you want to search or press '0' to stop: ";
		cin >> value;
	}
	l1.printrev();
	if (l1.isempty()) {
		cout << "List is empty.\n";
	}
	else {
		cout << "List is not empty.\n";
	}
	system("pause");
}