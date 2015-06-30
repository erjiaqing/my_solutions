#include <bits/stdc++.h>
using namespace std;
const int maxn = 200000 + 5;
#define x first
#define y second
typedef pair<long long , long long> pll;
typedef pair<pll , int> plli;
typedef pair<long long,int> pli;
typedef set<pli>::iterator splii;
long long l[maxn] , r[maxn];
set<pli> a;
plli range[maxn];
int p[maxn];
int n , m;
int main()
{
	long long ta;
	scanf("%d%d" , &n , &m);
	for (int i = 0 ; i < n ; i++)
		scanf("%lld%lld" , l + i , r + i);
	for (int i = 0 ; i < n - 1 ; i++)
		range[i] = plli(pll(r[i + 1] - l[i] , l[i + 1] - r[i]) , i);
	for (int i = 0 ; i < m ; i++)
		scanf("%lld" , &ta) , a.insert(pli(ta , i));
	sort(&range[0] , &range[n - 1]);
	plli *tmp;
	splii apos;
	for (int i = 0 ; i < n - 1 ; i++)
	{
		tmp = &range[i];
		apos = a.lower_bound(pli(tmp->x.y , 0));
		if (apos != a.end() && apos->x <= tmp->x.x)
		{
			p[tmp->y] = apos->y;
			a.erase(apos);
		}else
		{
			printf("No\n");
			return 0;
		}
	}
	printf("Yes\n");
	for (int i = 0 ; i < n - 1 ; i++)
		printf("%d%s" , p[i] + 1 , ((i == n - 2)?"\n":" "));
	return 0;
}
