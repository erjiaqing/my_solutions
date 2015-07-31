#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 5;
#define x first
#define y second
typedef pair<int , pair<int , int> > pipii;
int f[maxn];
pipii e[maxn];
bool flg[maxn];
int Find(int u){return f[u] == u ? u : f[u] = Find(f[u]);}
void Union(int u , int v)
{
	int fu = Find(u);
	int fv = Find(v);
	if (flg[fu])
		f[fv] = fu;
	else
		f[fu] = fv;
}
int n , q;
void work()
{
	long long ans = 0;
	int tn;
	scanf("%d%d" , &n , &q);
	memset(flg , 0 , sizeof(flg));
	for (int i = 0 ; i < n ; i++)
		f[i] = i;
	for (int i = 1 ; i < n ; i++)
		scanf("%d%d%d" , &e[i].y.x , &e[i].y.y , &e[i].x) , ans += e[i].x;
	for (int i = 0 ; i < q ; i++)
		scanf("%d" , &tn) , flg[tn] = true;
	sort(&e[1] , &e[n] , std::greater<pipii>());
	for (int i = 1 ; i < n ; i++)
	{
		int u = e[i].y.x , v = e[i].y.y;
		if ((flg[Find(u)] && flg[Find(v)]) == false)
		{
			Union(u , v);
			ans -= e[i].x;
		}
	}
	printf("%lld\n" , ans);
}
int main()
{
	int t;
	scanf("%d" , &t);
	while (t--)
		work();
	return 0;
}
