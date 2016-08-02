//#include <bits/stdc++.h>
#include <cstdio>
#include <string>
using namespace std;
#define _________B namespace ejq{
#define _________E }
_________B

int n;
int r, p, s;

string dfs(char c, int l)
{
	if (l == n)
		return string("") + c;
	string a, b;
	if (c == 'R')
	{
		a = dfs('R', l + 1);
		b = dfs('S', l + 1);
	}
	else if (c == 'S')
	{
		a = dfs('P', l + 1);
		b = dfs('S', l + 1);
	}
	else if (c == 'P')
	{
		a = dfs('P', l + 1);
		b = dfs('R', l + 1);
	}
	if (a < b) return a + b;
	else return b + a;
}

bool check(string _)
{
	int cr, cp, cs;
	cr = cp = cs = 0;
	//printf(" >>%s\n", _.c_str());
	for (int i = 0; i < _.size(); i++)
	{
		if (_[i] == 'R') cr++;
		if (_[i] == 'P') cp++;
		if (_[i] == 'S') cs++;
	}
	//printf("%d %d %d %d %d %d\n", cr, r, cp, p, cs, s);
	return cr == r && cp == p && cs == s;
}

string check()
{
	string R = dfs('R', 0);
	string P = dfs('P', 0);
	string S = dfs('S', 0);
	string ret = "IMPOSSIBLE";
	bool flg = 1;
	if (check(R)) ret = R, flg = 1;
	if (check(P) && (flg || P < ret)) ret = P, flg = 1;
	if (check(S) && (flg || S < ret)) ret = S, flg = 1;
	return ret;
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++)
	{
		scanf("%d%d%d%d", &n, &r, &p, &s);
		printf("Case #%d: %s\n", i, check().c_str());
	}
	return 0;
}

_________E
int main()
{
	return ejq::main();
}
