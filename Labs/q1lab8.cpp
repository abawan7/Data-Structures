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
	int countleaves(BNode* r){
		if (r == nullptr){
			return 0;
		}
		if (r->left == r->right == 0){
			return 1;
		}
		else
			return countleaves(r->left) + countleaves(r->right);
	}
	int countleaves(){
		return countleaves(root);
	}
};

int main(){
	Bintree <int> b;
	b.Insert(500);
	b.Insert(865);
	b.Insert(457);
	b.Insert(354);
	b.Insert(987);
	b.Insert(8);
	b.Insert(321);
	cout << b.countleaves() << endl;
	system("pause");
}