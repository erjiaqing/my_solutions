#include <bits/stdc++.h>
using namespace std;

const int maxn = 200000 + 5;

char s[maxn], ss[maxn], v[maxn];
int ls;
int ka[maxn];

int nxt[maxn][26];

bool check()
{
	int cur = 0;
	for (int i = 1; v[i]; i++)
	{
		cur = nxt[cur][v[i] - 'a'];
		if (cur > ls) return false;
	}
	return true;
}

void build(int len)
{
	memset(ss, 0, sizeof ss);
	memset(nxt, 0x3f, sizeof nxt);
	for (int i = len; i < ls; i++)
		ss[ka[i]] = s[ka[i]];
	for (int i = ls; i > 0; i--)
	{
		for (int j = 0; j < 26; j++)
			nxt[i - 1][j] = nxt[i][j];
		if (ss[i])
			nxt[i - 1][ss[i] - 'a'] = i;
	}
}

int main()
{
	scanf("%s", s + 1);
	scanf("%s", v + 1);
	ls = strlen(s + 1);
	for (int i = 0; i < ls; i++)
		scanf("%d", &ka[i]);
	int ans = 0;
	for (int i = 1 << 30; i > 0; i >>= 1)
	{
		if ((ans | i) <= ls)
		{
			build(ans | i);
			if (check())
				ans |= i;
		}
	}
	printf("%d\n", ans);
	return 0;
}
