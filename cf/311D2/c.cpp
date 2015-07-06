#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
const int maxn = 100000 + 5;
typedef pair<int,int> pii;
pii dsk[maxn];
int cnt[200 + 5] , sum[maxn];
int n , sall;
int main()
{
    scanf("%d", &n);
    for (int i = 0 ; i < n ; i++) scanf("%d" , &dsk[i].x);
    for (int i = 0 ; i < n ; i++)
	{
		scanf("%d" , &dsk[i].y);
		sall += dsk[i].y;
	}
    sort(&dsk[0] , &dsk[n]);
	sum[0] = dsk[0].y;
	for (int i = 1 ; i < n ; i++) sum[i] = sum[i - 1] + dsk[i].y;
	int i = 0 , hh = 0 , j = 0 , tans , ans = 0x3f3f3f3f , maxu;
	while ( i < n )
	{
		hh = 0;
		tans = sall;
		for ( j = i ; dsk[j].x == dsk[i].x ; j++)
		{
			hh++;
			tans -= dsk[j].y;
		}
		maxu = hh - 1;
		for (int k = 200 ; k > 0 && maxu > 0 ; k--)
		{
			tans -= min(maxu , cnt[k]) * k;
			maxu -= min(maxu , cnt[k]);
		}
		ans = min(ans , tans);
		for ( j = i ; dsk[j].x == dsk[i].x ; j++)
			cnt[dsk[j].y]++;
		i += hh;
	}
    printf("%d\n", ans);
    return 0;
}
