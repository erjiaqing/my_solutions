#include <bits/stdc++.h>
using namespace std;
const int maxn = 300000 + 5;
int curans = 0;
vector<int> no[maxn];
int vis[maxn];
int n, q;
int main()
{
	scanf("%d%d", &n, &q);
	vis[0] = 2;
	int totno = 0;
	for (int i = 1; i <= q; i++)
	{
		int tp, xx;
		scanf("%d%d", &tp, &xx);
		if (tp == 1)
		{
			totno++;
			no[xx].push_back(totno);
			curans++;
		} else if (tp == 2)
		{
			for (int v : no[xx])
			{
				if (vis[v] == 0)
				{
					vis[v] = 1;
					curans--;
				}
			}
			no[xx].clear();
		} else if (tp == 3)
		{
			while (vis[xx] != 2)
			{
				if (vis[xx] == 0)
					curans--;
				vis[xx] = 2;
				xx--;
			}
		}
		printf("%d\n", curans);
	}
	return 0;
}
