#include <bits/stdc++.h>
using namespace std;
const int maxn = 1005 , maxm = 1005 * 1005;
#define x first
#define y second
typedef pair<int , int> Point;
struct Edge{
	int u , v;
	double w;
}Edg[maxm];
struct Edge2{
	int v , n;
	double w;
}Edg2[maxn * 2];
Point ap[maxn];
int pw[maxn] , f[maxn];
int h[maxn];
int q[maxn] , qh , qt;
double maxw[maxn][maxn];
int sqr(int x) {return x * x;}
bool comp(const Edge &A , const Edge &B){return A.w < B.w;}
int Find(int x)
{
	return ((f[x] == x) ? (x) : (f[x] = Find(f[x])));
}
void Union(int x , int y)
{
	f[Find(x)] = Find(y);
}
void work()
{
	int n;
	int te2 = 0 , te = 0;
	scanf("%d" , &n);
	memset(maxw , 0 , sizeof(maxw));
	memset(h , -1 , sizeof(h));
	memset(Edg2 , 0 , sizeof(Edg2));
	memset(Edg , 0 , sizeof(Edg));
	for (int i = 0 ; i < n ; i++)
		scanf("%d%d%d" , &ap[i].x ,  &ap[i].y , &pw[i]);
	for (int i = 0 ; i < n ; i++)
		for (int j = i + 1 ; j < n ; j++)
		{
			Edg[te].u = i;
			Edg[te].v = j;
			Edg[te].w = sqrt(sqr(ap[i].x - ap[j].x) + sqr(ap[i].y - ap[j].y));
			te++;
		}
	for (int i = 0 ; i < n ; i++)
		f[i] = i;
	sort(&Edg[0] , &Edg[te] , comp);
	double sz = 0;
	for (int i = 0 ; i < te ; i++)
	{
		if (Find(Edg[i].u) != Find(Edg[i].v))
		{
			Union(Edg[i].u , Edg[i].v);
			Edg2[te2].v = Edg[i].v;Edg2[te2].w = Edg[i].w;Edg2[te2].n = h[Edg[i].u];h[Edg[i].u] = te2++;
			Edg2[te2].v = Edg[i].u;Edg2[te2].w = Edg[i].w;Edg2[te2].n = h[Edg[i].v];h[Edg[i].v] = te2++;
			sz += Edg[i].w;
		}
	}
	for (int i = 0 ; i < n ; i++)
	{
		q[qh = qt = 0] = i;
		maxw[i][i] = 0;
		while (qh <= qt)
		{
			int u = q[qh++];
			for (int j = h[u] ; ~j ; j = Edg2[j].n)
			{
				if (Edg2[j].v != i && maxw[i][Edg2[j].v] == 0)
				{
					maxw[i][Edg2[j].v] = max(maxw[i][u] , Edg2[j].w);
					q[++qt] = Edg2[j].v;
				}
			}
		}
	}
	double ans = 0;
	for (int i = 0 ; i < te ; i++)
		ans = max(ans , (pw[Edg[i].u] + pw[Edg[i].v]) / (sz - maxw[Edg[i].u][Edg[i].v]));
	printf("%.2lf\n" , ans);
}
int main()
{
	int t;
	scanf("%d" , &t);
	while (t--) work();
	return 0;
}
