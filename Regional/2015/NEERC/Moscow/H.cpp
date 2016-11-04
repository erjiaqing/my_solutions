#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <utility>
using namespace std;
const int maxn = 100000 + 5;
typedef pair<long long, int> pli;
pli ans[256][maxn];
int n, aa;
char ai[3];
int main()
{
	scanf("%d", &n);
	ans[0][0] = pli(0, -1);
	for (int i = 1; i < 256; i++) ans[i][0] = pli(0x8000000000000000ll, -1);
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", ai);
		sscanf(ai, "%X", &aa);
		for (int j = 0; j < 256; j++)
		{
			pli &lst = ans[j][i - 1];
			pli &llt = ans[(j + 255) & 255][i - 1];
			ans[j][i] = max(lst, pli(llt.first + (aa ^ (llt.second + 1)), llt.second + 1));
		}
	}
	long long aans = 0;
	for (int j = 0; j < 256; j++)
		aans = max(aans, ans[j][n].first);
	printf("%lld\n", aans);
	return 0;
}
