#include <iostream>
using namespace std;
#pragma once
struct node;
void insert(node * root, int value);
node * delete_node(node * root, int value);
node * find(node * root, int value);
node * find_min(node * root);
struct node
{
	int value;
	node * left;
	node * right;
	node(int value) : value(value), left(NULL), right(NULL) {};
};
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
node * find_min(node * root)
{
	if (root == NULL) return NULL;
	while (root->left != NULL) root = root->left;
	return root;
}
void insert(node * root, int value)
{
	if (root == NULL) return;
	while (true)
	{
		if (root->left != NULL && root->value > value)
		{
			root = root->left;
		}
		else if (root->right != NULL && root->value < value)
		{
			root = root->right;
		}
		else break;
	}
	if (root->value > value) root->left = new node(value);
	else if (root->value < value) root->right = new node(value);
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
			root->value = find_min(root->right)->value;
			root->right = delete_node(root->right, root->value);
		}
		else
		{
			node * successor = root->left == NULL ? root->right : root->left;
			free(root);
			return successor;
		}
	}
	return root;
}