#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 10000 + 5;
int pre[maxn], nxt[maxn];
int pos[maxn];
int len;
char str[maxn];
void swp(int l, int m, int r)
{
	int pl = pre[l], nr = nxt[r], nm = nxt[m];
	//int ll = l, mm = m, rr = r;
	pre[nm] = pl;
	nxt[pl] = nm;
	pre[nr] = m;
	nxt[m] = nr;
	pre[l] = r;
	nxt[r] = l;
}
void getlr()
{
	int pp = 1;
	for (int i = nxt[0]; pp <= len; i = nxt[i], pp++)
		pos[pp] = i;
}
int main()
{
	scanf("%s", str + 1);
	len = strlen(str + 1);
	for (int i = 1; i <= len; i++)
	{
		pre[i] = i - 1;
		nxt[i] = i + 1;
	}
	nxt[0] = 1;
	pre[len + 1] = len;
	int m;
	int l, r, k;
	getlr();
	scanf("%d", &m);
	while (m--)
	{
		scanf("%d%d%d", &l, &r, &k);
		k = -k;
		k = (k % (r - l + 1) + (r - l + 1)) % (r - l + 1);
//		cerr << k << endl;
		if (k == 0) continue;
		swp(pos[l], pos[l + k - 1], pos[r]);
		getlr();
//for (int i = 1; i <= len; i++) printf("%d,", pos[i]);
//puts("");
	}
	for (int i = 1; i <= len; i++) printf("%c", str[pos[i]]);
	puts("");
	return 0;
}
