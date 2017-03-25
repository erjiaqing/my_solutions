#include <bits/stdc++.h>
using namespace std;
const int maxn = 7000 + 5;
int k;
int ans[maxn * 2], ins[maxn * 2], ind[maxn * 2], n;

int flg[maxn * 2];
vector<int> e[2];

int main()
{
	memset(ans, -1, sizeof ans);
	ios::sync_with_stdio(0);
	cin >> n;
	ans[0] = 0;
	ans[1] = 0;
	for (int i = 0; i < 2; i++)
	{
		cin >> k;
		for (int j = 0; j < k; j++)
		{
			int t;
			cin >> t;
			e[i].push_back(t);
			for (int p = 1; p < n; p++)
			{
				int nxt = p + t;
				if (nxt >= n) nxt -= n;
				ind[(p << 1) | (i)]++;
			}
		}
	}
	queue<int> q;
	q.push(0);q.push(1);
	while (!q.empty())
	{
		int u = q.front();q.pop();
		int tu = ans[u];
		int cur = (u & 1);
		int id = u / 2;
		for (int v : e[cur ^ 1])
		{
			int rv = id - v;
			if (rv < 0) rv += n;
			(rv <<= 1) |= (cur ^ 1);
			if (tu == 0)
			{
				if (ans[rv] == -1)
				{
					ans[rv] = 2;
					q.push(rv);
				}
			} else {
				ins[rv]++;
				if (ins[rv] == ind[rv])
				{
					ans[rv] = 0;
					q.push(rv);
				}
			}
		}
	}
	for ( int i = 0; i < 2; i++)
	{
		for (int j = 1; j < n; j++)
		{
			switch(ans[(j << 1) | i])
			{
				case -1:
					printf("Loop");
					break;
				case 0:
					printf("Lose");
					break;
				case 1:
					printf("Loop");
					break;
				case 2:
					printf("Win");
					break;
			}
			printf("%c", " \n"[j == n - 1]);
		}
	}
	return 0;
}
