#include <bits/stdc++.h>

using namespace std;

int sg[1 << 20], rsg[20], t, n, w, st, q, res;
int main()
{
	for (int i = (1 << 20) - 1; i >= 0; i--)
	{
		memset(rsg, 0, sizeof(rsg));
		for (int j = 0; j < 19; j++)
			if (i & (1 << j))
				for (int k = j + 1; k < 20; k++)
					if ((i & (1 << k)) == 0)
					{
						for (int l = 0; l < 3; l++)
							rsg[sg[i ^ (1 << j) ^ (1 << k)]] = 1;
						break;
					}
		for (int j = 19; j >= 0; j--)
			if (rsg[j] == 0)
				sg[i] = j;
	}
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
	{
		res = 0;
		scanf("%d", &n);
		for (int j = 0; j < n; j++)
		{
			st = 0;
			scanf("%d", &w);
			for (int k = 0; k < w; k++)
			{
				scanf("%d", &q);
				st |= (1 << (q - 1));
			}
			res ^= sg[st];
		}
		puts(res ? "YES" : "NO");
	}
	return 0;
}
