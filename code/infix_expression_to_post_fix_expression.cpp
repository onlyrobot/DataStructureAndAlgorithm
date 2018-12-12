#include <iostream>
#include <stack>
#include <climits>
#include <map>
using namespace std;
int main()
{
	map<char, int> in;
	in.insert(pair<char, int>('+', 1));
	in.insert(pair<char, int>('-', 1));
	in.insert(pair<char, int>('*', 2));
	in.insert(pair<char, int>('/', 2));
	in.insert(pair<char, int>('^', 4));
	in.insert(pair<char, int>('(', 10));
	map<char, int> out;
	out.insert(pair<char, int>('+', 1));
	out.insert(pair<char, int>('-', 1));
	out.insert(pair<char, int>('*', 2));
	out.insert(pair<char, int>('/', 2));
	out.insert(pair<char, int>('^', 3));
	out.insert(pair<char, int>('(', 0));
	int n;
	cin >> n;
	while (n-- > 0)
	{
		stack<char> o;
		char input;
		cin >> input;
		while (input != '#')
		{
			if (input == ')')
			{
				while (o.top() != '(')
				{
					cout << o.top();
					o.pop();
				}
				o.pop();
			}
			else if (in.find(input) == in.end())
			{
				cout << input;
			}
			else
			{
				while (!o.empty() && in[input] <= out[o.top()])
				{
					cout << o.top();
					o.pop();
				}
				o.push(input);
			}
			cin >> input;
		}
		while (!o.empty())
		{
			cout << o.top();
			o.pop();
		}
		cout << endl;
	}
	return 0;
}