#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 5;
vector<int> v;

int rn;

int segt[maxn * 80], son[maxn * 80][2];
int root[maxn];
int pre[maxn];
int tn;

void add(int fa, int &x, int l, int r, int t, int delta)
{
	if (x == 0)
		x = ++tn;
	segt[x] = segt[fa] + delta;
	if (l == r)
		return;
	int mid = (l + r) / 2;
	if (t <= mid)
	{
		son[x][1] = son[fa][1];
		add(son[fa][0], son[x][0], l, mid, t, delta);
	} else
	{
		son[x][0] = son[fa][0];
		add(son[fa][1], son[x][1], mid + 1, r, t, delta);
	}
}

int sum(int rt, int l, int r, int k, int tr)
{
	while (l != r)
	{
		int mid = (l + r) / 2;
		if (tr - mid + segt[son[rt][1]] >= k)
		{
			rt = son[rt][1];
			l = mid + 1;
		}
		else
		{
			k -= tr - mid + segt[son[rt][1]];
			tr = mid;
			rt = son[rt][0];
			r = mid;
		}
	}
	return l;
}

int getans(int k)
{
	int curr = rn;
	int ans = 0;
	while (curr > 0)
	{
		int nxt = sum(root[curr], 0, rn, k + rn - curr + 1, rn);
		curr = nxt;
		ans++;
	}
	return ans;
}

int main()
{
	ios::sync_with_stdio(0);
	int n;
	cin >> n;
	int lst = -1;
	for (int i = 1; i <= n; i++)
	{
		int ci;
		cin >> ci;
		if (ci != lst)
			v.push_back(lst);
		lst = ci;
	}
	v.push_back(lst);
	rn = v.size() - 1;
	for (int i = 1; i < (int)v.size(); i++)
	{
		if (pre[v[i]])
			add(root[i - 1], root[i], 0, rn, pre[v[i]], -1);
		else
			root[i] = root[i - 1];
		pre[v[i]] = i;
	}
	for (int i = 1; i <= n; i++)
		cout << getans(i) << " \n"[i == n];
	return 0;
}
