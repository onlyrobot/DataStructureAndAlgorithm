#include <iostream>
#include <string>
using namespace std;
struct node
{
	char body;
	node * left;
	node * right;
};
node * create_tree(string::iterator & it, string::iterator end, int & leaf_count)
{
	if (it == end || *it == '#')
	{
		return NULL;
	}
	node * root = new node();
	root->body = *it;
	root->left = create_tree(++it, end, leaf_count);
	root->right = create_tree(++it, end, leaf_count);
	if (root->left == NULL && root->right == NULL) ++leaf_count;
	return root;
}
void print_tree(node * root, int depth)
{
	if (root == NULL) return;
	for (int i = 0; i < depth; ++i)
	{
		cout << "    ";
	}
	cout << root->body << endl;
	print_tree(root->left, depth + 1);
	print_tree(root->right, depth + 1);
}
void print_presequence(node * root)
{
	if (root == NULL) return;
	cout << root->body;
	print_presequence(root->left);
	print_presequence(root->right);
}
void print_insequence(node * root)
{
	if (root == NULL) return;
	print_insequence(root->left);
	cout << root->body;
	print_insequence(root->right);
}
void print_postsequence(node * root)
{
	if (root == NULL) return;
	print_postsequence(root->left);
	print_postsequence(root->right);
	cout << root->body;
}
void swap_binarytree(node * root)
{
	if (root == NULL) return;
	swap_binarytree(root->left);
	swap_binarytree(root->right);
	swap(root->left, root->right);
}
int main()
{
	string input;
	cin >> input;
	string::iterator it = input.begin();
	int leaf_count = 0;
	node * root = create_tree(it, input.end(), leaf_count);
	cout << "BiTree" << endl;
	print_tree(root, 0);
	cout << "pre_sequence  : ";
	print_presequence(root);
	cout << endl;
	cout << "in_sequence   : ";
	print_insequence(root);
	cout << endl;
	cout << "post_sequence : ";
	print_postsequence(root);
	cout << endl;
	cout << "Number of leaf: " << leaf_count << endl;
	swap_binarytree(root);

	cout << "BiTree swapped" << endl;
	print_tree(root, 0);
	cout << "pre_sequence  : ";
	print_presequence(root);
	cout << endl;
	cout << "in_sequence   : ";
	print_insequence(root);
	cout << endl;
	cout << "post_sequence : ";
	print_postsequence(root);
	cout << endl;
	swap_binarytree(root);
	return 0;
}