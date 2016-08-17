#include <bits/stdc++.h>
using namespace std;
const int maxn = 5000005;
struct PalinTree {
	struct node{
		int nxt[2], fail, len;
	}nd[maxn];
	char S[maxn];
	int last, n, p;
	int newnode(int l) {
//		memset(nxt[p], 0, sizeof(nxt[p]));
//		num[p] = 0;
		nd[p].len = l;
		return p++;
	}
	void init() {
		p = 0;
		newnode(0);newnode(-1);
		last = n = 0;S[n] = -1;
		nd[0].fail = 1;
	}
	int get_fail(int x)
	{
		while (S[n - nd[x].len - 1] != S[n]) x = nd[x].fail;
		return x;
	}
	int extend(int c) {
		S[++n] = c;
		int cur = get_fail(last), ret = 0;
		if (!nd[cur].nxt[c]) {
			int now = newnode(nd[cur].len + 2);
			ret = 1;
			nd[now].fail = nd[get_fail(nd[cur].fail)].nxt[c];
			nd[cur].nxt[c] = now;
//			num[now] = num[fail[now]] + 1;
		}
		last = nd[cur].nxt[c];
//		cnt[last]++;
		return ret;
	}
//	void count() {
//		for (int i = p - 1; i >= 0; i--)
//			cnt[fail[i]] += cnt[i];
//	}
}palintree;
char s[maxn];
int main()
{
	scanf("%s", s);
	palintree.init();
	for (int i = 0; s[i]; i++)
		s[i] = palintree.extend(s[i] - 'a') + '0';
	printf("%s\n", s);
}
