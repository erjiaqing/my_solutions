#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000 + 5;
vector<int> e[maxn * 2];

int n;
string sa[maxn][2];
char buf1[50], buf2[50];
int vis[maxn * 2];


int S[maxn], top;
bool dfs(int u)
{
	if (vis[u ^ 1]) return false;
	if (vis[u]) return true;
	vis[u] = true;
	S[top++] = u;
	for (int v : e[u])
		if (!dfs(v)) return false;
	return true;
}

bool twosat(int n)
{
	memset(vis, 0, sizeof vis);
	for (int i = 0; i < n; i += 2)
	{
		if (vis[i] || vis[i ^ 1]) continue;
		top = 0;
		if (!dfs(i))
		{
			while (top) vis[S[--top]] = false;
			if (!dfs(i ^ 1)) return false;
		}
	}
	return true;
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		scanf("%s%s", buf1, buf2);
		buf1[3] = 0;
		sa[i][0] = sa[i][1] = buf1;
		sa[i][1][2] = buf2[0];
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (i == j) continue;
			for (int k = 0; k < 2; k++)
			{
				for (int l = 0; l < 2; l++)
					if (sa[i][k] == sa[j][l])
					{
						e[(i << 1) | k].push_back((j << 1) | (l ^ 1));
						if (k == 0)
							e[(i << 1) | k].push_back((j << 1) | l);
					}
			}
		}
	if (twosat(n * 2))
	{
		puts("YES");
		for (int i = 0; i < n * 2; i++)
			if (vis[i])
				puts(sa[i >> 1][i & 1].c_str());
	} else 
	{
		puts("NO");
	}
	return 0;
}
