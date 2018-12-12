#include <iostream>
#include <cstdio>
#include <string>
#include <map>
#include <stack>
#include <climits>
#include <cmath>
using namespace std;
struct op
{
	int priority;
	int (* fun)(int, int);
	op(int priority, int (*fun)(int, int)) : priority(priority), fun(fun) {};
};
int add(int a, int b)
{
	return a + b;
}
int multiply(int a, int b)
{
	return a * b;
}
int subtraction(int a, int b)
{
	return a - b;
}
int divide(int a, int b)
{
	if (b == 0)
	{
		cout << "Divide 0." << endl;
		return INT_MIN;
	}
	return a / b;
}
int mode(int a, int b)
{
	if (b == 0)
	{
		cout << "Divide 0." << endl;
		return INT_MIN;
	}
	return a % b;
}
int my_pow(int a, int b)
{
	return pow(a, b);
}
string parse_name(string & s, string::iterator & pos)
{
	string name;
	while (pos != s.end() && *pos >= 'a' && *pos <= 'z') name += *pos++;
	return name;
}
int parse_int(string & s, string::iterator & pos)
{
	int symbol = 1;
	if (*pos == '-')
	{
		symbol = -1;
		++pos;
	}
	int num = 0;
	while (pos != s.end() && *pos >= '0' && *pos <= '9')
	{
		num = num * 10 + *pos++ - '0';
	}
	return num * symbol;
}
op parse_op(stack<op> & o, string::iterator & pos)
{
	switch (*pos++)
	{
	case '+': return op(0, add);
	case '-': return op(0, subtraction);
	case '*': return op(1, multiply);
	case '/': return op(1, divide);
	case '%': return op(1, mode);
	case '^': return op(o.empty() ? 2 : o.top().priority + 3, my_pow); //specil
	default:
		cout << "parse operator error." << endl;
		exit(0);
	}
}
int main()
{
	map<string, int> a;
	while (true)
	{
		string input;
		getline(cin, input);
		string::iterator pos = input.begin();
		if (*pos == '?')
		{
			++pos;
			string left = parse_name(input, ++pos);
			cout << left << "=" << a[left] << endl;
			continue;
		}
		string left = parse_name(input, pos);
		if (left == "end") return 0;

		++pos; //jump the '='

		stack<op> o;
		stack<int> n;
		while (true)
		{
			int num;
			if (*pos == '-' || *pos >= '0' && *pos <= '9')
			{
				num = parse_int(input, pos);
			}
			else if (*pos == '(')
			{
				o.push(op(-1, NULL));
				++pos;
				continue;
			}
			else
			{
				num = a[parse_name(input, pos)];
			}

			n.push(num);

			if (pos == input.end()) break;

			while (*pos == ')')
			{
				while (o.top().priority != -1)
				{
					int num1, num2;
					num2 = n.top(), n.pop();
					num1 = n.top(), n.pop();

					int res = o.top().fun(num1, num2);
					if (res == INT_MIN) return -1; //error occurred
					else n.push(res);
					o.pop();
				}
				o.pop();
				++pos;
				if (pos == input.end()) goto outer;
			}
			op optor = parse_op(o, pos);
			
			if (o.empty() || optor.priority > o.top().priority)
			{
				o.push(optor);
			}
			else
			{
				while (!o.empty() && optor.priority <= o.top().priority)
				{
					int num1, num2;
					num2 = n.top(), n.pop();
					num1 = n.top(), n.pop();

					int res = o.top().fun(num1, num2);
					if (res == INT_MIN) return -1; //error occurred
					else n.push(res);
					o.pop();
				}
				o.push(optor);
			}
		}
	outer:;
		while (!o.empty())
		{
			int num1, num2;
			num2 = n.top(), n.pop();
			num1 = n.top(), n.pop();

			int res = o.top().fun(num1, num2);
			if (res == INT_MIN) return -1; //error occurred
			else n.push(res);
			o.pop();
		}
		
		a[left] = n.top();
	}
	return 0;
}