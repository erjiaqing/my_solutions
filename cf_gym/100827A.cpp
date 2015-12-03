#include <iostream>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <cstring>
using namespace std;
char str[10000];
char s[10000];
char buf[10000];
typedef pair<int, int> pii;
int getnum(int beg, int end)
{
	//cerr << beg << "->" << end << endl;
	if ((str[beg] == '0' && end > beg) || (str[beg] == '-' && str[beg+1] == '0'))
		return 0x3f3f3f3f;
	memset(buf, 0, sizeof(buf));
	for (int i = 0; beg + i <= end; i++)
		buf[i] = str[beg + i];
	return atoi(buf);
}
bool check()
{
	//cerr << str << endl;
	int flg = 0;
	int l = strlen(str);
	int i = 1;
	int oppos = 0, eqsgn = 0;
pii n1, n2, n3;
int num1, num2, num3;
	for (; i < l; i++)
	{
		if (str[i] == '+' || str[i] == '-' || str[i] == '*')
		{
			n1.second = i - 1;
			n2.first = i + 1;
			oppos = i;
			break;
		}
	}
	//cerr << i << endl;
	i += 2;
	for (; i < l; i++)
	{
		if (str[i] == '=')
		{
			n2.second = i - 1;
			n3.first = i + 1;
			eqsgn = i;
			break;
		}
	}
	n3.second = l - 1;
	num1 = getnum(n1.first, n1.second);
	num2 = getnum(n2.first, n2.second);
	num3 = getnum(n3.first, n3.second);
	if (max(num1, max(num2, num3)) == 0x3f3f3f3f)
		return false;
	bool res = 0;
	/*
	cerr << num1 << str[oppos] << num2 << '=' << num3 << endl;
	for (int i = 0; i < l; i++)
	{
		if (i == n1.first || i == n2.first || i == n3.first) cerr << "^";
		else cerr << " ";
	}
	cerr << endl;*/
	if (str[oppos] == '+') return num1 + num2 == num3;
	else if (str[oppos] == '-') return num1 - num2 == num3;
	else return num1 * num2 == num3;
}
int work()
{
	scanf("%s", s);
	int l = strlen(s);
	for (int i = '0'; i <= '9'; i++)
	{
		bool chk = false;
		for (int j = 0; j < l; j++)
		{
			if (s[j] == i)
				chk = true;
			str[j] = ((s[j] == '?') ? (i) : s[j]);
		}
		str[l] = 0;
		if (chk) continue;
		if (check())
			return i - '0';
	}
	return -1;
}
int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
		printf("%d\n", work());
	return 0;
}
