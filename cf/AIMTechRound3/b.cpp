#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
vector<int> x;

int main()
{
	int n, a;
	scanf("%d%d", &n, &a);
	for (int i = 0; i < n; i++)
	{
		int tx;
		scanf("%d", &tx);
		x.push_back(tx);
	}
	sort(x.begin(), x.end());
	if (n == 1) puts("0");
	else
	{
		int ans = 0x3f3f3f3f;
		for (int i = 0; i < 2; i++)
		{
			int l = x[i], r = x[n + i - 2];
			if (l >= a) ans = min(ans, r - a);
			else if (r <= a) ans = min(ans, a - l);
			else
			{
				ans = min(ans, r - l + a - l);
				ans = min(ans, r - l + r - a);
			}
		}
		printf("%d\n", ans);
	}
}
