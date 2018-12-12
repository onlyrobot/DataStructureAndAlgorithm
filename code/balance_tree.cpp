#include <iostream>
#include <cstdio>
using namespace std;
#define max(a, b) ( a > b ? a : b )
struct node
{
	node * left;
	node * right;
	int height;
	char value;
	node(int value) : value(value), height(0), left(NULL), right(NULL) {};
};
void print_presequence(node * root)
{
	if (root == NULL) return;
	cout << root->value;
	print_presequence(root->left);
	print_presequence(root->right);
}
void print_insequence(node * root)
{
	if (root == NULL) return;
	print_insequence(root->left);
	cout << root->value;
	print_insequence(root->right);
}
void print_postsequence(node * root)
{
	if (root == NULL) return;
	print_postsequence(root->left);
	print_postsequence(root->right);
	cout << root->value;
}
void print_tree(node * root, int depth = 0)
{
	if (root == NULL) return;
	print_tree(root->right, depth + 1);
	for (int i = 0; i < depth; ++i) cout << "    ";
	cout << root->value << endl;
	print_tree(root->left, depth + 1);
}
int height(node * root)
{
	return root == NULL ? -1 : root->height;
}
node * left_balance(node * root)
{
	node * left = root->left;
	if (height(left->right) > height(left->left)) //LR rotation
	{
		node * right = left->right;
		root->left = right->right;
		left->right = right->left;
		right->left = left;
		right->right = root;
		root = right;
	}
	else //LL rotation
	{
		root->left = left->right;
		left->right = root;
		root = left;
	}
	left->height = max(height(left->left), height(left->right)) + 1;
	root->right->height = max(height(root->right->left), height(root->right->right)) + 1;
	return root;
}
node * right_balance(node * root)
{
	node * right = root->right;
	if (height(right->left) > height(right->right)) //RL rotation
	{
		node * left = right->left;
		root->right = left->left;
		left->left = root;
		right->left = left->right;
		left->right = right;
		root = left;
	}
	else //RR rotation
	{
		root->right = right->left;
		right->left = root;
		root = right;
	}
	right->height = max(height(right->left), height(right->right)) + 1;
	root->left->height = max(height(root->left->left), height(root->left->right)) + 1;
	return root;
}
node * insert(node * root, char value)
{
	if (root == NULL)
	{
		return new node(value);
	}
	if (root->value < value)
	{
		if (root->right == NULL)
		{
			root->right = new node(value);
		}
		else
		{
			root->right = insert(root->right, value);
		}
	}
	else if (root->value > value)
	{
		if (root->left == NULL)
		{
			root->left = new node(value);
		}
		else
		{
			root->left = insert(root->left, value);
		}
	}
	if (height(root->left) - height(root->right) > 1)
	{
		root = left_balance(root);
	}
	else if (height(root->right) - height(root->left) > 1)
	{
		root = right_balance(root);
	}
	root->height = max(height(root->left), height(root->right)) + 1;
	return root;
}
int main()
{
	char c;
	node * root = NULL;
	while ((c = getchar()) != '\n')
	{
		root = insert(root, c);
	}
	cout << "Preorder: ";
	print_presequence(root);
	cout << endl << "Inorder: ";
	print_insequence(root);
	cout << endl << "Postorder: ";
	print_postsequence(root);
	cout << endl << "Tree:" << endl;
	print_tree(root);
	return 0;
}