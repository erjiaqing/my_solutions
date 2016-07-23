#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	int t;
	scanf("%d", &t);
	while (t--)
	{
		int mx = 0x80000000;
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
		{
			int tt;
			scanf("%d", &tt);
			mx = max(mx, tt);
		}
		printf("%d\n", mx);
	}
}
