/**********************
 * CF::GYM 100625 / G *
 * EJQ                *
 **********************/
#include <cstdio>
#include <cmath>
#include <queue>
#include <cstring>
using namespace std;
const int maxn = 1000 + 5;
const double eps = 1e-8;
struct Point{
	double x , y , r;
}P[maxn];
int n , w;
bool vis[maxn];
double d[maxn][maxn];
double sqr(double x)
{
	return x * x;
}
double dist(const Point &a , const Point &b)
{
	return (sqrt(sqr(a.x - b.x) + sqr(a.y - b.y)) - a.r - b.r);
}
bool bi(double r0)
{
	memset(vis , 0 , sizeof(vis));
	queue<int> q;
	q.push(0);
	vis[0] = 1;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int v = 1 ; v <= n + 1 ; v++)
		{
			if (!vis[v] && d[u][v] - 2 * r0 < eps)
			{
				vis[v] = true;
				q.push(v);
			}
		}
	}
	return vis[n + 1];
}
void work()
{
	scanf("%d" , &w);
	scanf("%d" , &n);
	for (int i = 1 ; i <= n ; i++)
		scanf("%lf%lf%lf" , &P[i].x , &P[i].y , &P[i].r);
	for (int i = 1 ; i <= n ; i++)
	{
		d[0][i] = d[i][0] = P[i].x - P[i].r;
		d[i][n + 1] = d[n + 1][i] = w - P[i].x - P[i].r;
		for (int j = i + 1 ; j <= n ; j++)
			d[i][j] = d[j][i] = dist(P[i] , P[j]);
	}
	d[0][n + 1] = d[n + 1][0] = w;
	double l = 0 , r = w / 2.0 , m;
	while (r - l > eps)
	{
		m = (r + l) / 2;
		if (bi(m))
			r = m;
		else
			l = m;
	}
	printf("%.8f\n" , r);
}
int main()
{
	int t;
	scanf("%d" , &t);
	while (t--)
		work();
	return 0;
}
