#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000 + 5;
const int maxl = 4 * maxn;

struct SAM{
	struct node{
		int n[27], f, s, s2, v;
		void init(int _v, int _s) {
			v = _v;s2 = 0;
			f = -1;
			memset(n, -1, sizeof(n));
		}
	}m[maxl];
	int mems, rt, ls;
	int appcnt[maxl], vis[maxl];
	int getmem(int v, int s) {
		int ret = mems++;
		m[ret].init(v, s);
		return ret;
	}
	SAM(){mems = 0;ls = rt = getmem(0, 0);}
	void clear()
	{
		mems = 0;
		ls = rt = getmem(0, 0);
		memset(appcnt, 0, sizeof(appcnt));
		memset(vis, 0, sizeof(vis));
		m[rt].s2 = 1;
	}
	void extend(int w, int sz) {
		int p = ls, np = getmem(m[p].v + 1, sz);
		while ((~p) && m[p].n[w] == -1)
			m[p].n[w] = np, p = m[p].f;
		if (p == -1)
			m[np].f = rt;
		else {
			int q = m[p].n[w];
			if (m[p].v + 1 == m[q].v)
				m[np].f = q;
			else {
				int nq = getmem(m[p].v + 1, sz);
				memcpy(m[nq].n, m[q].n, sizeof(m[q].n));
				m[nq].f = m[q].f;
				m[q].f = m[np].f = nq;
				while (p != -1 && m[p].n[w] == q)
					m[p].n[w] = nq, p = m[p].f;
			}
		}
		ls = np;
	}
	void process_right() {
		static int go[maxl], b[maxl];
		memset(b, 0, sizeof(b));
		for (int i = 0; i < mems; i++)
			b[m[i].v]++;
		for (int i = 1; i < mems; i++)
			b[i] += b[i - 1];
		for (int i = 0; i < mems; i++)
			go[b[m[i].v]--] = i;
		for (int i = 1; i <= mems; i++)
			for (int j = 0; j < 26; j++)
				if (~m[go[i]].n[j])
					m[m[go[i]].n[j]].s2 += m[go[i]].s2;
	}
	void process_appcnt(int cur) {
		vis[cur] = 1;
		if (cur != rt)
			appcnt[m[cur].s] += m[cur].v - m[m[cur].f].v;
		for (int j = 0; j < 26; j++)
			if (~m[cur].n[j])
				if (!vis[m[cur].n[j]])
					process_appcnt(m[cur].n[j]);
	}
	int match(char *s)
	{
		int cur = rt;
		for (int i = 0; s[i]; i++) {
			if (~m[cur].n[s[i] - 'a']) {
				cur = m[cur].n[s[i] - 'a'];
			} else {
				return 0;
			}
		}
		return m[cur].s2;
	}
}sam;

char q[maxn * 5];
int n, m;

void sol()
{
	sam.clear();
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		scanf("%s", q);
		for (int j = 0; q[j]; j++)
			sam.extend(q[j] - 'a', 0);
		sam.extend(26, (i == n - 1));
	}
	sam.process_right();
//	sam.process_appcnt(sam.rt);
	for (int i = 0; i < m; i++)
	{
		scanf("%s", q);
		int smatch = sam.match(q);
		printf("%d\n", smatch);
	}
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++)
		printf("Case #%d:\n", i), sol();
	return 0;
}
