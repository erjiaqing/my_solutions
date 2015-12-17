#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <stack>
#include <vector>
#include <utility>
#include <cmath>
using namespace std;
struct vls{
	bool type;
	int vI;
	double vD;
	vls(int vl)
	{
		type = 0;
		vI = vl;
		vD = 0;
	}
	vls(double vl)
	{
		type = 1;
		vD = vl;
		vI = 0;
	}
	vls()
	{
		type = 0;
		vI = vD = 0;
	}
friend vls operator + (vls a, vls b)
{
	if (a.type | b.type)
		return vls(((a.type) ? a.vD : double(a.vI)) + (((b.type) ? b.vD : double(b.vI))));
	else
		return vls(a.vI + b.vI);
}
friend vls operator - (vls a, vls b)
{
	if (a.type | b.type)
		return vls(((a.type) ? a.vD : double(a.vI)) - (((b.type) ? b.vD : double(b.vI))));
	else
		return vls(a.vI - b.vI);
}
friend vls operator * (vls a, vls b)
{
	if (a.type | b.type)
		return vls(((a.type) ? a.vD : double(a.vI)) * (((b.type) ? b.vD : double(b.vI))));
	else
		return vls(a.vI * b.vI);
}
friend vls operator / (vls a, vls b)
{
	if (b.vI == 0 && fabs(b.vD) < 1e-8)
	{
		printf("divided by ZERO\n");
		exit(0);
	}
	if (a.type | b.type)
		return vls(((a.type) ? a.vD : double(a.vI)) / (((b.type) ? b.vD : double(b.vI))));
	else
		return vls(a.vI / b.vI);
}
};
typedef pair<vls, char> pvo; // pair_value_operator
int priority[256];
map<string, int> vals;
vls parse_val(char *s)
{
	string tmpval;
	stack<char> operator_stack;
	stack<vls> value_stack;
	vector<pvo> value_queue;
	int thisisnum = 0;
	int doublecnt = 0;
	vls current_val;
	for (int i = 0; s[i] != ';' && s[i]; i++)
	{
		if (('0' <= s[i] && s[i] <= '9') || s[i] == '.')
		{
			if (s[i] == '.') {
				thisisnum = -1;
				current_val = vls(current_val.vI * 1.0);
				continue;
			}
			else if (!thisisnum) thisisnum = 1;
			if (thisisnum == 1) {
				current_val = current_val * 10 + s[i] - '0';
			} else {
				current_val.vD += (s[i] - '0') * pow(0.1, ++doublecnt);
			}
		} else if (('a' <= s[i] && s[i] <= 'z') || ('A' <= s[i] && s[i] <= 'Z')) {
			thisisnum = 2;
			tmpval = tmpval + s[i];
		} else if (s[i] == '=') {
			vls nextval = parse_val(&s[i + 1]);
			current_val = vals[tmpval];
			if (current_val.type == 0)
			{
				if (nextval.type == 0) current_val.vI = nextval.vI;
				else current_val.vI = nextval.vD;
			} else
			{
				vls nextval = parseInt(&s[i + 1]);
				if (nextval.type == 0) current_val.vD = nextval.vI;
				else current_val.vD = nextval.vD;
			}
			vals[tmpval] = current_val;
		} else {
			if (thisisnum == 1 || thisisnum == -1) {
				thisisnum = 0;
				value_queue.push_back(pvo(current_val, 'x'));
			} else if (thisisnum == 2) {
				value_queue.push_back(pvo(vals[tmpval], 'x'));
			}
			if (s[i] == ' ') continue;
			else if (s[i] == '(') operator_stack.push('(');
			else if (s[i] == ')')
			{
				while (!operator_stack.empty())
				{
					char stop = operator_stack.top();
					operator_stack.pop();
					if (stop != '(')
						value_queue.push_back(pvo(vls(0), stop));
					else
						break;
				}
			}
			else {
				while (!operator_stack.empty())
				{
					char stop = operator_stack.top();
					if (priority[stop] >= priority[s[i]])
					{
						operator_stack.pop();
						value_queue.push_back(pvo(vls(0), stop));
					}
				}
				operator_stack.push(s[i]);
			}
		}
	}
	while (!operator_stack.empty())
	{
		char stop = operator_stack.top();
		operator_stack.pop();
		value_queue.push_back(pvo(vls(0), stop));
	}
	current_val = vls(0);
	for (int i = 0; i < value_queue.size(); i++)
	{
		if (value_queue[i].second == 'x')
			value_stack.push(value_queue[i].first);
		else
		{
			vls va, vb;
			vb = value_stack.top();value_stack.pop();
			va = value_stack.top();value_stack.pop();
			switch (value_queue[i].second)
			{
				case '+':
					value_stack.push(va + vb);break;
				case '-':
					value_stack.push(va - vb);break;
				case '*':
					value_stack.push(va * vb);break;
				case '/':
					value_stack.push(va / vb);break;
				default:
					break;
			}
		}
	}
	return value_stack.top();
}
int main()
{
	priority['+'] = priority['-'] = 1;
	priority['*'] = priority['/'] = 2;
	priority['('] = -1;
	priority[')'] = -1;
	return 0;
}
