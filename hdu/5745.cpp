#include <bits/stdc++.h>
using namespace std;

const int maxn = 500000 + 5;
const int maxm = 5000 + 5;

char s1[maxn], s2[maxm], ret[maxn];

void sol()
{
	int n, m;
	scanf("%d%d", &n, &m);
	scanf("%s", s1);
	scanf("%s", s2);
	memset(ret, '0', sizeof(char) * n);
	ret[n] = 0;
	for (int i = 0; i + m <= n; i++)
	{
		int cur = i;
		bool flg = 1;
		for (int j = 0; j < m;)
		{
			if (s1[cur] == s2[j])
			{
				cur++;j++;
			} else if (s1[cur + 1] == s2[j] && s2[j + 1] == s1[cur])
			{
				cur += 2;
				j += 2;
			} else
			{
				flg = 0;
				break;
			}
		}
		ret[i] = '0' + flg;
	}
	printf("%s\n", ret);
}

int main()
{
	int t = 0;
	scanf("%d", &t);
	while (t--)
		sol();
	return 0;
}
