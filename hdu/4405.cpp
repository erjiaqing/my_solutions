#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 10;
const double six = 1.0 / 6;
double p[maxn] , e[maxn];
int fa[maxn];
int n , m;
int getfa(int x)
{
	return fa[x] == x ? x : fa[x] = getfa(fa[x]);
}
void unionfa(int x , int y)
{
	fa[getfa(x)] = y;
}
bool read()
{
	scanf("%d%d" , &n , &m);
	memset(p , 0 , sizeof(p));
	memset(e , 0 , sizeof(e));
	if (n == 0)
		return false;
	for (int i = 0 ; i <= n + 6 ; i++)
		fa[i] = i;
	for (int i = n + 1 ; i <= n + 6 ; i++)
		unionfa(i , n);
	for (int i = 0 ; i < m ; i++)
	{
		int x , y;
		scanf("%d%d" , &x , &y);
		unionfa(x, y);
	}
	p[0] = 1;
	e[0] = 0;
	for (int i = 0 ; i < n ; i++)
	{
//		printf("%.4f\n" , p[i]);
		for (int j = 1 ; j <= 6 ; j++)
		{
			int rj = getfa(i + j);
			p[rj] += p[i] * six;
			e[rj] += (e[i] + p[i]) * six;
		}
	}
	printf("%.4f\n" , e[n]);
	return true;
}
int main()
{
	while (read());
	return 0;
}
