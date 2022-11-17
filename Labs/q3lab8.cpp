#include <iostream>
#include <queue>
using namespace std;

/* A binary tree node has data, pointer to left child
and a pointer to right child */

struct Node {
	int data;
	Node* left;
	Node* right;
};

// Function to create a new node
Node* CreateNode(int data)
{
	Node* newNode = new Node();
	if (!newNode) {
		cout << "Memory error\n";
		return NULL;
	}
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	return newNode;
}

// Function to insert element in binary tree
Node* InsertNode(Node* root, int data)
{
	// If the tree is empty, assign new node address to root
	if (root == NULL) {
		root = CreateNode(data);
		return root;
	}

	// Else, do level order traversal until we find an empty
	// place, i.e. either left child or right child of some
	// node is pointing to NULL.
	queue<Node*> q;
	q.push(root);

	while (!q.empty()) {
		Node* temp = q.front();
		q.pop();

		if (temp->left != NULL)
			q.push(temp->left);
		else {
			temp->left = CreateNode(data);
			return root;
		}

		if (temp->right != NULL)
			q.push(temp->right);
		else {
			temp->right = CreateNode(data);
			return root;
		}
	}
}

/* Inorder traversal of a binary tree */

void inorder(Node* temp)
{
	if (temp == NULL)
		return;

	inorder(temp->left);
	cout << temp->data << ' ';
	inorder(temp->right);
}

void fixtree(Node* r){
	if (r != nullptr){
		if (r->left > r){
			Node* temp;
			temp = r->left;
			r->left = r->right;
			r->right = temp;
			fixtree(r->left);
		}
		else if (r->right < r){
			Node* temp;
			temp = r->right;
			r->right = r->left;
			r->left = temp;
			fixtree(r->right);
		}
	}
}
// Driver code
int main()
{
	Node* root = CreateNode(5);
	root->left = CreateNode(3);
	root->left->left = CreateNode(4);
	root->left->right = CreateNode(2);
	root->right = CreateNode(8);
	root->right->left = CreateNode(6);
	root->right->right = CreateNode(10);

	inorder(root);
	cout << endl;

	fixtree(root);
	inorder(root);


	system("pause");
}