#include <bits/stdc++.h>
using namespace std;
const int maxn = 90000 + 5, maxl = 270000;
struct Sam{
	struct node{
		node *n[26], *fa;
		int val, vis;
		long long sz;
		void init(int _v){val = _v;memset(n, 0, sizeof n);}
	}*root, *last, mem[maxl], *go[maxl];
	// maxl = about 3 * maxlen
	int mems;
	int b[maxl];
	node* getmem(int val) {
		auto ret = &mem[mems++];
		ret->init(val);
		return ret;
	}
	Sam(){mems = 0;last = root = getmem(0);}
	void extend(int w) {
		node *p = last;
		node *np = getmem(p->val + 1);
		while (p != nullptr && p->n[w] == 0)
			p->n[w] = np, p = p->fa;
		if (p == nullptr)
			np->fa = root;
		else {
			node *q = p->n[w];
			if (p->val + 1 == q->val)
				np->fa = q;
			else {
				node *nq = getmem(p->val + 1);
				memcpy(nq->n, q->n, sizeof q->n);
				nq->fa = q->fa;
				q->fa = nq;
				np->fa = nq;
				while (p != nullptr && p->n[w] == q)
					p->n[w] = nq, p = p->fa;
			}
		}
		last = np;
	}
	void prep()
	{
		for (int i = 0; i < mems; i++)
			b[mem[i].val]++;
		for (int i = 1; i < mems; i++)
			b[i] += b[i - 1];
		for (int i = 0; i < mems; i++)
			go[b[mem[i].val]--] = &mem[i];
		for (int i = mems; i; i--)
		{
			go[i]->sz = 1;
			for (int j = 0; j < 26; j++)
				if (go[i]->n[j] != nullptr)
					go[i]->sz += go[i]->n[j]->sz;
		}
	}
}sam;
char s[maxn], res[maxn];
void query(int k)
{
	int len = 0;
	auto cur = sam.root;
	while (k)
	{
		for (int i = 0; i < 26; i++)
		{
			if (cur->n[i] != nullptr)
			{
				if (cur->n[i]->sz >= k)
				{
					res[len++] = 'a' + i;
					cur = cur->n[i];
					k--;
					break;
				} else {
					k -= cur->n[i]->sz;
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
