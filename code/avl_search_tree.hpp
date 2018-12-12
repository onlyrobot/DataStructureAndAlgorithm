#pragma once
#include <iostream>
using namespace std;
#define max(a, b) ( a > b ? a : b )
struct node;
node * create(int value);
int height(node * root);
node * find(node * root, int value);
node * delete_node(node * root, int value);
node * insert(node * root, int value);
node * find_min(node * root);
node * find_max(node * root);
node * left_balance(node * root);
node * right_balance(node * root);
void print_tree(node * root, int depth);
struct node
{
	node * left;
	node * right;
	int height;
	int value;
	node(int value) : value(value), height(0), left(NULL), right(NULL) {};
};
void print_tree(node * root, int depth = 0)
{
	if (root == NULL) return;
	print_tree(root->left, depth + 1);
	for (int i = 0; i < depth; ++i)
	{
		cout << "    ";
	}
	cout << root->value << endl;
	print_tree(root->right, depth + 1);
}
node * create(int value)
{
	return new node(value);
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
int height(node * root)
{
	return root == NULL ? -1 : root->height;
}
node * find_min(node * root)
{
	if (root == NULL) return NULL;
	while (root->left != NULL) root = root->left;
	return root;
}
node * find_max(node * root)
{
	if (root == NULL) return NULL;
	while (root->right != NULL) root = root->right;
	return root;
}
node * find(node * root, int value)
{
	while (root != NULL)
	{
		if (root->value < value)
		{
			root = root->right;
		}
		else if (root->value > value)
		{
			root = root->left;
		}
		else
		{
			return root;
		}
	}
	return root;
}
node * delete_node(node * root, int value)
{
	if (root == NULL) return NULL;
	if (root->value < value)
	{
		root->right = delete_node(root->right, value);
	}
	else if (root->value > value)
	{
		root->left = delete_node(root->left, value);
	}
	else
	{
		if (root->left != NULL && root->right != NULL)
		{
			if (height(root->left) < height(root->right))
			{
				root->value = find_min(root->right)->value;
				root->right= delete_node(root->right, root->value);
			}
			else
			{
				root->value = find_max(root->left)->value;
				root->left = delete_node(root->left, root->value);
			}
		}
		else
		{
			if (root->left != NULL)
			{
				node * temp = root->left;
				delete root;
				root = temp;
			}
			else if (root->right != NULL)
			{
				node * temp = root->right;
				delete root;
				root = temp;
			}
			else
			{
				delete root;
				return NULL;
			}
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
node * insert(node * root, int value)
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