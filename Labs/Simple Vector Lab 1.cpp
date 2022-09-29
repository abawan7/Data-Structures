#include<iostream>
using namespace std;
template <typename T>
class simplevector
{
private:
	T*pointer; int size;
public:
	simplevector() {
		size = 0;
		pointer = new T[size];
	}
	simplevector(int ssize) {
		size = ssize;
		pointer = new T[size];
		for (int i = 0; i < size; i++) {
			pointer[i] = 0;
		}
	}
	void input() {
		cout << "Enter the size of the array: "; cin >> size;
		pointer = new T[size];
		cout << "Enter values:\n";
		for (int i = 0; i < size; i++) {
			cin >> pointer[i];
		}
	}
	simplevector(simplevector&a) {
		size = a.size;
		pointer = new T[size];
		for (int i = 0; i < size; i++) {
			pointer[i] = a.pointer[i];
		}
	}
	void sizesetter(int ssize) {
		size = ssize;
	}
	void pointersetter(T*ppointer) {
		for (int i = 0; i < size; i++) {
			pointer[i] = ppointer[i];
		}
	}
	int sizegetter() {
		return size;
	}
	T pointergetter() {
		return pointer;
	}
	void finditem() {
		T value;
		cout << "Enter the value you want to find: ";
		cin >> value;
		for (int i = 0; i < size; i++) {
			if (pointer[i] == value) {
				cout << value << " is at " << i << " index.\n";
			}
		}
	}
	void sortarray() {
		for (int i = 0; i < size; i++) {
			for (int j = i + 1; j < size; j++) {
				if (pointer[i] > pointer[j]) {
					swap(pointer[j], pointer[i]);
				}
			}
		}
	}
	void output() {
		cout << "Size: " << size << endl;
		cout << "Array:\n";
		for (int i = 0; i < size; i++) {
			if (pointer[i] != NULL)
				cout << pointer[i] << endl;
		}
	}
	void operator+(simplevector&a) {
		T value, oldsize = a.size;
		cout << "Enter the value you want to add: ";
		cin >> value;
		size = size * 2;
		pointer[oldsize] = value;
		for (int i = oldsize + 1; i < size; i++) {
			pointer[i] = NULL;
		}
	}
	void operator-(simplevector&a) {
		T oldsize = a.size;
		size = size / 2;
		for (int i = oldsize; i >= size; i--) {
			pointer[i] = NULL;
		}
	}
	~simplevector() {
		cout << "Destructor called.\n";
		delete[] pointer;
	}
};
int main()
{
	simplevector<int>s1;
	s1.input();
	s1.output();
	simplevector<int>s2(s1);
	cout << "After deep copy:\n";
	s2.output();
	s1.finditem();
	s1.sortarray();
	s1.output();
	s1 + s2;
	cout << "After + operator:\n";
	s1.output();
	s1 - s2;
	cout << "After - operator:\n";
	s1.output();
	system("pause");
	return 0;
}