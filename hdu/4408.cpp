/*
 * HDU 4408
 * Author: EJQ
 */
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cassert>
using namespace std;
const int maxn = 100 + 5 , maxm = 1000 + 5;
struct edge{
	int u , v , w;
	edge(){}
	void read(){scanf("%d%d%d" , &u , &v , &w);}
	bool friend operator < (const edge &a ,const edge &b){return a.w < b.w;}
}e[maxm];
int n , m , mod;
int fa[maxn] , fu[maxn] , vis[maxn];
long long mat[maxn][maxn] , matc[maxn][maxn]; //Matrix-Tree
vector<int> v[maxn];
int sget(int u , int *f){return (f[u] == u) ? u : (sget(f[u] , f));}
void sunion(int u , int v , int *f){f[sget(u , f)] = sget(v , f);}
long long det(int n)
{
	for (int i = 0 ; i < n ; i++)
		for (int j = 0 ; j < n ; j++)
			mat[i][j] %= mod;
	long long ret = 1;
	for (int i = 1 ; i < n ; i++)
	{
		for (int j = i + 1 ; j < n ; j++)
		{
			while (mat[j][i])
			{
				int t = mat[i][i] / mat[j][i];
				for (int k = i ; k < n ; k++)
					mat[i][k] = (mat[i][k] - mat[j][k] * t) % mod;
				for (int k = i ; k < n ; k++)
					swap(mat[i][k] , mat[j][k]);
				ret = -ret;
			}
		}
		if (mat[i][i] == 0)
			return 0;
		ret = ret * mat[i][i] % mod;
	}
	return (ret + mod) % mod;
}
void work()
{
	//memset(mat , 0 , sizeof(mat));
	memset(matc , 0 , sizeof(matc));
	memset(vis , 0 , sizeof(vis));
	for (int i = 0 ; i < m ; i++)
		scanf("%d%d%d" , &e[i].u , &e[i].v , &e[i].w);
	sort(&e[0] , &e[m]);
	for (int i = 1 ; i <= n ; i++)
		fa[i] = i , v[i].clear();
	int lastw = -1;
	long long ans = 1;
	for (int en = 0 ; en <= m ; en++) // edge number
	{
		if ((e[en].w != lastw) || (en == m))
		{
			for (int i = 1 ; i <= n ; i++)
			{
				if (vis[i])
				{
					int u = sget(i , fu);
					v[u].push_back(i);
					vis[i] = 0;
				}
			}
			for (int i = 1 ; i <= n ; i++)
			{
				memset(mat , 0 , sizeof(mat));
				int cnt = v[i].size();
				assert(cnt <= n);
				if (cnt > 1)
				{
					for (int j = 0 ; j < cnt ; j++)
					{
						for (int k = j + 1 ; k < cnt ; k++)
						{
							int tu = v[i][j];
							int tv = v[i][k];
							mat[j][k] -= matc[tu][tv];
							mat[k][j] -= matc[tu][tv];
							mat[j][j] += matc[tu][tv];
							mat[k][k] += matc[tu][tv];
						}
					}
					(ans *= det(cnt)) %= mod;
					for (int j = 0 ; j < cnt ; j++)
						fa[v[i][j]] = i;
				}
			}
			for (int i = 1 ; i <= n ; i++)
			{
				fu[i] = fa[i] = sget(i , fa);
				v[i].clear();
			}
			if (en == m)
				break;
			lastw = e[en].w;
		}
		int tu = e[en].u;
		int tv = e[en].v;
		int ru = sget(tu , fa);
		int rv = sget(tv , fa);
		if (ru == rv)
			continue;
		vis[ru] = vis[rv] = 1;
		sunion(ru , rv , fu);
		matc[ru][rv]++;
		matc[rv][ru]++;
	}
	bool flg = true;
	for (int i = 2 ; i <= n && flg ; i++)
		flg = flg && (sget(i , fu) == sget(i - 1 , fu));
	flg = flg && m;
	printf("%lld\n" , flg ? ans : 0);
}
int main()
{
	while ((~scanf("%d%d%d" , &n , &m , &mod)) && mod)
		work();
	return 0;
}
