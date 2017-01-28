#include <bits/stdc++.h>
using namespace std;

const int maxn = 5500000 + 5;
const char lambda[] = "lambda ";
struct treenode{
	int l, r, tp;
	unsigned long long val;
}tree[maxn];

map<int, string> mp;
multiset<int> lam;
set<string> ans;

int totnode;
char buf[maxn * 4];
int nxtcol[maxn * 4];
stack<int> sta;

void clear()
{
	mp.clear();
	ans.clear();
	lam.clear();
	totnode = 0;
}

int build(int l, int r)
{
	while (buf[l] == ' ' && l <= r) l++;
	if (l > r) return 0;
	int rootnode = totnode++;
	bool islambda = true;
	for (int i = l; (i < l + 7) && islambda; i++)
		islambda = islambda && (buf[i] == lambda[i - l]);
	if (islambda)
	{
		l += 7;
		tree[rootnode].tp = 1;
		tree[rootnode].val = 0;
		tree[rootnode].l = tree[rootnode].r = 0;
		while (buf[l] != '(') l++;
		l++;
		while (buf[l] == ' ') l++;
		for (; buf[l] != ')' && buf[l] != ' '; l++)
			tree[rootnode].val = tree[rootnode].val * 131 + buf[l];
		while (buf[l] == ' ') l++;
		l++;
		while (buf[l] == ' ') l++;
		if (buf[l] != '(')
		{
			totnode--;
			return 0;
		} else {
			tree[rootnode].l = build(l + 1, nxtcol[l] - 1);
		}
	} else
	{
		tree[rootnode].tp = 2;
		tree[rootnode].l = tree[rootnode].r = 0;
		if (buf[l] == '(')
		{
			tree[rootnode].l = build(l + 1, nxtcol[l] - 1);
			l = nxtcol[l] + 1;
		} else {
			int tnode = totnode++;
			tree[rootnode].l = tnode;
			tree[tnode].tp = 3;
			tree[tnode].l = tree[tnode].r = 0;
			string tstr = "";
			tree[tnode].val = 0;
			for (; buf[l] != ' ' && l <= r; l++)
			{
				tree[tnode].val = tree[tnode].val * 131 + buf[l];
				tstr += buf[l];
			}
			if (mp.find(tree[tnode].val) == mp.end())
				mp[tree[tnode].val] = tstr;
			l++;
		}
		while (buf[l] == ' ') l++;
		if (buf[l] == '(')
		{
			tree[rootnode].r = build(l + 1, nxtcol[l] - 1);
		} else {
			int tnode = totnode++;
			tree[tnode].tp = 3;
			tree[rootnode].r = tnode;
			tree[tnode].val = 0;
			tree[tnode].l = tree[tnode].r = 0;
			string tstr = "";
			for (; buf[l] != ' ' && l <= r; l++)
			{
				tree[tnode].val = tree[tnode].val * 131 + buf[l];
				tstr += buf[l];
			}
			if (mp.find(tree[tnode].val) == mp.end())
				mp[tree[tnode].val] = tstr;
		}
	}
	return rootnode;
}

void debug(int root, int lay)
{
	for (int i = 0; i < lay; i++) printf("	");
	if (tree[root].tp == 1)
		printf("@ (%s)\n", mp[tree[root].val].c_str());
	else if (tree[root].tp == 3)
		printf("# %s\n", mp[tree[root].val].c_str());
	else printf("*\n");
	if (tree[root].l) debug(tree[root].l, lay + 1);
	if (tree[root].r) debug(tree[root].r, lay + 1);
}

void dfs(int root)
{
	if (tree[root].tp == 1)
	{
		lam.insert(tree[root].val);
	}
	if (tree[root].tp == 3 && tree[root].val)
		if (lam.find(tree[root].val) == lam.end())
			ans.insert(mp[tree[root].val]);
	if (tree[root].l) dfs(tree[root].l);
	if (tree[root].r) dfs(tree[root].r);
	if (tree[root].tp == 1)
	{
		lam.erase(lam.find(tree[root].val));
	}
}

int rmain()
{
	fgets(buf, 10000000 + 5, stdin);
	int i = 0;
	for (i = 0; buf[i]; i++)
	{
		if (buf[i] == '(') sta.push(i);
		if (buf[i] == ')')
		{
			nxtcol[sta.top()] = i;
			sta.pop();
		}
	}
	while (buf[i] <= ' ') i--;
	int root = build(0, i);
	//	debug(root, 0);
	dfs(root);
	if (!ans.size()) printf(" ");
	for (string a : ans)
		printf(" %s", a.c_str());
	printf("\n");
	return 0;
}

int main()
{
	int t = 0;
	fgets(buf, 10000000 + 5, stdin);
	sscanf(buf, "%d", &t);
	for (int i = 1; i <= t; i++)
	{
		printf("Case #%d:", i);
		clear();
		rmain();
	}
}
