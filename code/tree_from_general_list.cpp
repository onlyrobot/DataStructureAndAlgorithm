#include <iostream>
#include <string>
using namespace std;
struct degree_list
{
	int degree;
	int num;
	degree_list * next;
	degree_list(int degree, int num, degree_list * next) : degree(degree), num(num), next(next) {};
};
struct node
{
	char body;
	node * child;
	node * sibling;
};
node * create_tree(string::iterator & it, string::iterator end, degree_list * dl, int & degree_of_tree)
{
	if (it == end || *it++ == ')') return NULL;
	if (*it == ')') return NULL; //the case of empty tree
	node * root = new node();
	root->body = *it;
	int degree = 0;
	node * sub;
	if (*++it == ')') sub = NULL;
	else //*++it == ','
	{
		sub = root->child = create_tree(++it, end, dl, degree_of_tree);
		degree += 1;
		while (*it == ',')
		{
			sub = sub->sibling = create_tree(++it, end, dl, degree_of_tree);
			degree += 1;
		}
		sub->sibling = NULL;
	}
	++it; //jump the ')'
	if (degree > degree_of_tree) degree_of_tree = degree;
	degree_list * front = dl, * cur = front->next;
	while (cur != NULL && cur->degree < degree)
	{
		front = cur, cur = cur->next;
	}
	if (cur != NULL && cur->degree == degree) ++cur->num;
	else
	{
		front->next = new degree_list(degree, 1, cur);
	}
	return root;
}
void print_tree(node * root, int depth)
{
	if (root == NULL) return;
	for (int i = 0; i < depth; ++i) cout << "    ";
	cout << root->body << endl;
	node * sub = root->child;
	while (sub != NULL)
	{
		print_tree(sub, depth + 1);
		sub = sub->sibling;
	}
}
int main()
{
	string input;
	cin >> input;
	degree_list * dl = new degree_list(-1, -1, NULL);
	int degree_of_tree = 0;
	string::iterator it = input.begin();
	node * root = create_tree(it, input.end(), dl, degree_of_tree);
	print_tree(root, 0);
	cout << "Degree of tree: " << degree_of_tree << endl;
	int degree_count = 0;
	while (dl->next != NULL)
	{
		dl = dl->next;
		while (true)
		{
			cout << "Number of nodes of degree " << degree_count << ": ";
			if (degree_count == dl->degree)
			{
				cout << dl->num << endl;
				++degree_count;
				break;
			}
			else cout << 0 << endl;
			++degree_count;
		}
	}
	if (degree_count == 0) cout << "Number of nodes of degree 0: 0" << endl;
	return 0;
}