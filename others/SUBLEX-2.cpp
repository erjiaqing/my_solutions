#include <bits/stdc++.h>
using namespace std;
const int maxn = 90000 + 5, maxl = 270000;

struct SAM{
	struct node{
		int n[27], f, s, v;
		void init(int _v) {
			v = _v;s = 0;f = -1;
			memset(n, -1, sizeof(n));
		}
	}m[maxl];
	int mems, rt, ls;
	int appcnt[maxl], vis[maxl];
	int getmem(int v) {
		int ret = mems++;
		m[ret].init(v);
		return ret;
	}
	SAM(){mems = 0;ls = rt = getmem(0);}
	void clear()
	{
		mems = 0;
		ls = rt = getmem(0);
		memset(appcnt, 0, sizeof(appcnt));
		memset(vis, 0, sizeof(vis));
	}
	void extend(int w) {
		int p = ls, np = getmem(m[p].v + 1);
		while ((~p) && m[p].n[w] == -1)
			m[p].n[w] = np, p = m[p].f;
		if (p == -1)
			m[np].f = rt;
		else {
			int q = m[p].n[w];
			if (m[p].v + 1 == m[q].v)
				m[np].f = q;
			else {
				int nq = getmem(m[p].v + 1);
				memcpy(m[nq].n, m[q].n, sizeof(m[q].n));
				m[nq].f = m[q].f;
				m[q].f = m[np].f = nq;
				while (p != -1 && m[p].n[w] == q)
					m[p].n[w] = nq, p = m[p].f;
			}
		}
		ls = np;
	}
	void prep()
	{
		static int b[maxl], go[maxl];
		memset(b, 0, sizeof(b));
		for (int i = 0; i < mems; i++)
			b[m[i].v]++;
		for (int i = 1; i < mems; i++)
			b[i] += b[i - 1];
		for (int i = 0; i < mems; i++)
			go[b[m[i].v]--] = i;
		for (int i = mems; i; i--)
		{
			m[go[i]].s = 1;
			for (int j = 0; j < 26; j++)
				if (m[go[i]].n[j] != -1)
					m[go[i]].s += m[m[go[i]].n[j]].s;
		}
	}
}sam;

char s[maxn], res[maxn];
void query(int k)
{
	int len = 0;
	auto cur = sam.rt;
	while (k)
	{
		for (int i = 0; i < 26; i++)
		{
			if (sam.m[cur].n[i] != -1)
			{
				if (sam.m[sam.m[cur].n[i]].s >= k)
				{
					res[len++] = 'a' + i;
					cur = sam.m[cur].n[i];
					k--;
					break;
				} else {
					k -= sam.m[sam.m[cur].n[i]].s;
				}
			}
		}
	}
	res[len] = 0;
}
int main()
{
	scanf("%s", s);
	for (int i = 0; s[i]; i++)
		sam.extend(s[i] - 'a');
	sam.prep();
	int n, k;
	scanf("%d", &n);
	while (n--)
	{
		scanf("%d", &k);
		query(k);
		printf("%s\n", res);
	}
	return 0;
}
