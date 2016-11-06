#include <bits/stdc++.h>
using namespace std;

const int maxn = 200000 * 2 + 5;

typedef pair<int, int> pii;
#define x first
#define y second
struct TrieNode{
	int flg, fail, nxt[2];
}T[maxn];

int root, tnode;

char str[maxn];

int maxlen[maxn], vis[maxn];
int pref[maxn], prefchr[maxn];
int ins[maxn], vvis[maxn], lay[maxn];

char res[maxn];

void trie_ins(char *s)
{
	int p = root;
	for (int i = 0; s[i]; i++)
	{
		if (T[p].nxt[s[i] - '0'] == 0)
			T[p].nxt[s[i] - '0'] = ++tnode;
		p = T[p].nxt[s[i] - '0'];
	}
	T[p].flg = 1;
}

void trie_build()
{
	int u;
	queue<int> q;
	T[root].fail = root;
	q.push(root);
	while (!q.empty())
	{
		u = q.front();
		q.pop();
		for (int i = 0; i < 2; i++)
		{
			if (T[u].nxt[i])
			{
				if (u == root)
					T[T[u].nxt[i]].fail = root;
				else
				{
					int v = T[u].fail;
					while (v)
					{
						if (T[v].nxt[i])
						{
							T[T[u].nxt[i]].fail = T[v].nxt[i];
							break;
						}
						v = T[v].fail;
					}
					if (!v)
						T[T[u].nxt[i]].fail = root;
				}
				q.push(T[u].nxt[i]);
			} else
			{
				int v = T[u].fail;
	//			cerr << u << ' ' << v << endl;
				while (v != root && T[v].nxt[i] == 0)
				{
	//				cerr << v << endl;
					v = T[v].fail;
				}
				T[u].nxt[i] = T[v].nxt[i];
			}
			T[u].flg += T[T[u].fail].flg;
		}
	}
}

bool findloop(int lay, int u)
{
	vvis[u] = 1;
	::lay[u] = lay;
	for (int i = 0; i < 2; i++)
	{
		int v = T[u].nxt[i];
		if (T[v].flg) continue;
		if (vvis[v] == 1)
		{
			return true;
		} else if (vvis[v] == 0)
		{
			if (findloop(lay + 1, v)) return true;
		}
	}
	vvis[u] = 2;
	return false;
}


int main()
{
	int n;
	scanf("%d", &n);
	root = tnode = 1;
	for (int i = 0; i < n; i++)
	{
		scanf("%s", str);
		trie_ins(str);
	}
	trie_build();
	if (findloop(0, root))
	{
		puts("-1");
		return 0;
	}
	queue<pii> q;
	memset(maxlen, -1, sizeof maxlen);
	maxlen[root] = 0;
	q.push(pii(root, 0));
//	for (int i = root; i <= tnode; i++)
//	{
//		printf("%c %d : '0'-> %d '1'-> %d\n", T[i].flg ? '*' : ' ', i, T[i].nxt[0], T[i].nxt[1]);
//	}
	int curmx = 0, curmxu = 0;
	while (!q.empty())
	{
		pii fst = q.front();
		q.pop();
		int u = fst.x;
		if (fst.y != maxlen[u]) continue;
//		cerr << fst.x << ' ' << fst.y << endl;
		if (curmx < fst.y)
		{
			curmx = fst.y;
			curmxu = u;
		}
//		q.pop();
		vis[u]++;
		if (vis[u] > tnode)
		{
			printf("-1\n");
			return 0;
		}
		for (int i = 0; i < 2; i++)
		{
			if (T[T[u].nxt[i]].flg == 0)
			{
				int v = T[u].nxt[i];
	//			cerr << u << ' ' << v << ' ' << maxlen[v] << endl;
				if (maxlen[v] < maxlen[u] + 1)
				{
					maxlen[v] = maxlen[u] + 1;
					q.push(pii(v, maxlen[v]));
//					maxlen[v] = maxlen[u] + 1;
					pref[v] = u;
					prefchr[v] = i;
				}
			}
		}
	}
	int ii = curmx;
	int cu = curmxu;
	for (int i = ii - 1; i >= 0; i--)
	{
		res[i] = prefchr[cu] + '0';
		cu = pref[cu];
	}
	puts(res);
	return 0;
}
