#include <iostream>
#include <string>	
#include <queue>
using namespace std;
struct node
{
	char body;
	node * left;
	node * right;
};
node * recover(string::iterator front, string::iterator back, string::reverse_iterator & it)
{
	if (back == front)
	{
		--it; //caution
		return NULL;
	}
	node * root = new node();
	root->body = *it;
	if (back - front > 1)
	{
		string::iterator center = front;
		while (*center != *it)
		{
			++center;
		}
		root->right = recover(center + 1, back, ++it);
		root->left = recover(front, center, ++it);
	}
	return root;
}
int main()
{
	string inorder, postorder;
	cin >> inorder >> postorder;
	string::reverse_iterator post_it = postorder.rbegin();
	node * root = recover(inorder.begin(), inorder.end(), post_it);
	//print the binary tree by layer
	queue<node *> que;
	que.push(root);
	while (!que.empty())
	{
		node * n = que.front();
		que.pop();
		cout << n->body;
		if (n->left != NULL) que.push(n->left);
		if (n->right != NULL) que.push(n->right);
	}
	cout << endl;
	return 0;
}