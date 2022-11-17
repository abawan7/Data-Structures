#include <iostream>
using namespace std;
template <class T>
class Bintree{
	class BNode{
		friend class Bintree;
		T data;
		BNode* left;
		BNode* right;
	};
	BNode* root;
public:
	Bintree(){
		root = nullptr;
	}
	void Insert(BNode* &r, T d){
		if (r == nullptr){
			r = new BNode;
			r->data = d;
			r->left = nullptr;
			r->right = nullptr;
		}
		else
		{
			if (d < r->data){
				Insert(r->left, d);
			}
			else if (d>r->data){
				Insert(r->right, d);
			}
		}
	}
	void Insert(T d){
		Insert(root, d);
	}
	void fliptree(BNode* r){
		if (r == nullptr){
			return;
		}
		else{
			BNode* temp;
			fliptree(r->left);
			fliptree(r->right);

			temp = r->left;
			r->left = r->right;
			r->right = temp;
		}
	}
	void fliptree(){
		fliptree(root);
	}
	void printinorder(BNode* r){
		if (r != nullptr){
			printinorder(r->left);
			cout << r->data << " ";
			printinorder(r->right);
		}
	}
	void printinorder(){
		printinorder(root);
	}
};

int main(){
	Bintree <int> b;
	b.Insert(1);
	b.Insert(2);
	b.Insert(3);
	b.Insert(4);
	b.Insert(5);
	b.Insert(6);
	/*b.Insert(0);
	b.Insert(0);*/
	b.Insert(7);
	b.Insert(8);
	b.printinorder();
	b.fliptree();
	cout << endl;
	b.printinorder();
	system("pause");
}














