#pragma once
#include <iostream>
using namespace std;
template <class T>
struct node;
template <class T>
node<T> * create_tree(T data);
template <class T>
node<T> * thread_tree(node<T> * root, node<T> * pre = NULL); //thread the tree, the return value is the last node of inorder_traverse
template <class T>
void insert(node<T> * root, T data); //insert data to root
template <class T>
struct node
{
	T data;
	bool left_thread, right_thread;
	node<T> * left, * right;
	node<T>(T data) : data(data), left_thread(true), right_thread(true), left(NULL), right(NULL) {};
};
template <class T>
node<T> * create_tree(T data)
{
	return new node<T>(data);
}
template <class T>
node<T> * thread_tree(node<T> * root, node<T> * pre)
{
	node<T> * left = root->left, *right = root->right;
	if (left != NULL)
	{
		pre = thread_tree(left, pre);
	}
	else
	{
		root->left_thread = true;
		root->left = pre;
	}
	if (pre != NULL && pre->right == NULL)
	{
		pre->right_thread = true;
		pre->right = root;
	}
	pre = root;
	if (right != NULL)
	{
		pre = thread_tree(right, pre);
	}
	return pre;
}
template <class T>
void insert(node<T> * root, T data)
{
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
		else
		{
			return;
		}
	}
	if (root == NULL) return;
	if (root->data < data) root->right = new node<T>(data);
	else root->left = new node<T>(data);
}