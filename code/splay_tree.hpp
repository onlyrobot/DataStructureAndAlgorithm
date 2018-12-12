#pragma once
#include <iostream>
using namespace std;
struct node;
node * create(int data);
void insert(node * root, int data);
node * access(node * root, int data); //return the accessed node as root, original root if no such element
node * splay(node * root, int data);
node * delete_node(node * root, int data);
node * find_min(node * root);
struct node
{
	int data;
	node * left;
	node * right;
	node(int data) : data(data), left(NULL), right(NULL) {};
};
node * find_min(node * root)
{
	if (root == NULL) return NULL;
	while (root->left != NULL) root = root->left;
	return root;
}
node * create(int data)
{
	return new node(data);
}
void insert(node * root, int data)
{
	if (root == NULL) return;
	while (true)
	{
		if (root->data < data)
		{
			if (root->right != NULL) root = root->right;
			else break;
		}
		else if (root->data > data)
		{
			if (root->left != NULL) root = root->left;
			else break;
		}
		else return;
	}
	if (root != NULL)
	{
		if (root->data < data) root->right = new node(data);
		else root->left = new node(data);
	}
}
node * delete_node(node * root, int data)
{
	if (root == NULL) return NULL;
	if (root->data < data)
	{
		root->right = delete_node(root->right, data);
	}
	else if (root->data > data)
	{
		root->left = delete_node(root->left, data);
	}
	else
	{
		if (root->left != NULL && root->right != NULL)
		{
			root->data = find_min(root->right)->data;
			root->right = delete_node(root->right, root->data);
		}
		else
		{
			if (root->left != NULL)
			{
				node * temp = root->left;
				*root = *root->left;
				delete temp;
			}
			else if (root->right != NULL)
			{
				node * temp = root->right;
				*root = *root->right;
				delete temp;
			}
			else
			{
				delete root;
				root = NULL;
			}
		}
	}
	return root;
}
node * splay(node * root, int data)
{
	if (root == NULL) return NULL;
	if (root->data < data)
	{
		node * right = splay(root->right, data);
		if (right == NULL) return NULL; //not found
		if (right->data != data)
		{
			if (right->data < data) //RR rotation
			{
				root->right = right->left;
				right->left = root;
				root = right->right;
				right->right = root->left;
				root->left = right;
			}
			else //RL rotation
			{
				node * left = right->left;
				right->left = left->right;
				left->right = right;
				root->right = left->left;
				left->left = root;
				root = left;
			}
		}
		else root->right = right;
	}
	else if (root->data > data)
	{
		node * left = splay(root->left, data);
		if (left == NULL) return NULL; //not found
		if (left->data != data)
		{
			if (left->data > data) //LL rotation
			{
				root->left = left->right;
				left->right = root;
				root = left->left;
				left->left = root->right;
				root->right = left;
			}
			else //LR rotation
			{
				node * right = left->right;
				left->right = right->left;
				right->left = left;
				root->left = right->right;
				right->right = root;
				root = right;
			}
		}
		else root->left = left;
	}
	return root;
}
node * access(node * root, int data)
{
	if (root == NULL) return NULL;
	node * temp = splay(root, data);
	if (temp == NULL || root->data == data) return root;
	else root = temp;
	node * left = root->left, *right = root->right;
	if (left != NULL && left->data == data)
	{
		//adjust root and root->left
		root->left = left->right;
		left->right = root;
		root = left;
	}
	else if (right != NULL && right->data == data)
	{
		//adjust root and root->right
		root->right = right->left;
		right->left = root;
		root = right;
	}
	return root;
}