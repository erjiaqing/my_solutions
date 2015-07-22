#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 100000 + 5;
struct Edge {
	int v , n;
	Edge(const int &_v , const int &_n):
		v(_v) , n(_n) {}
}E[maxn * 2];
int h[maxn] , dep[maxn] , f[maxn][20] , te , max_val[maxn] , sec_val[maxn] , smax_val[maxn] , que[maxn] , front , tail;
void reset()
{
	memset(h , 0 , sizeof(h));
}
bool work()
{
	int n , q;
	if (scanf("%d%d" , &n , &q) != 1) return false;
	for (int i = 1 ; i < n ; i++)
	{
		int u , v;
		scanf("%d%d" , &u , &v);
		E[++te] = Edge(v , h[u]);h[u] = te;
		E[++te] = Edge(u , h[v]);h[v] = te;
	}
	que[front = tail = 0] = 1;
	while ( front <= tail )
	{
		int u = que[front++];
		for (int j = h[u] ; j ; j = E[j].n)
		{
			if (!
		}
	}
	return true;
}
int main()
{
}
