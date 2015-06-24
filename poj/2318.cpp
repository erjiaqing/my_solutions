#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 5000 + 5;
int n, m, _x1, _y1, _x2, _y2, tx, ty;
int U[maxn],L[maxn],C[maxn];
bool check(int i)
{
	if (U[i] != L[i])
	{
		return (tx - U[i])*(_y1 - _y2) + (U[i] - L[i]) * (_y1 - ty) > 0;
	}
	return U[i] < tx;
}
void work()
{
	for (int i = 1; i <= n; i++) scanf("%d%d", U + i, L + i);
	U[n + 1] = _x2;L[n + 1] = _x2;
	for (int i = 0; i < m; i++)
	{
		int ans = 0,t=8192;
		scanf("%d%d", &tx, &ty);
		if ( tx < _x1 || tx > _x2 || ty > _y1 || ty < _y2 ) continue;
		while (t)
		{
			if ((t + ans) <= n && check(ans + t))
				ans += t;
			t >>= 1;
		}
		C[ans]++;
	}
	for (int i = 0 ; i <= n ; i++)
		printf("%d: %d\n", i, C[i]);
	printf("\n");
}
void reset()
{
	memset( C, 0, sizeof(C));
}
int main()
{
	while (scanf("%d%d%d%d%d%d" , &n, &m, &_x1, &_y1, &_x2, &_y2) == 6)
		work(),reset();
	return 0;
}
