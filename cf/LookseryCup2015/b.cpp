#include <bits/stdc++.h>
using namespace std;
const int maxn = 100 + 5;
int c[maxn][maxn];
int a[maxn];
bool sel[maxn];
queue <int> ds;
int n , sl;
int main()
{
	scanf("%d" , &n);
	for (int i = 1 ; i <= n ; i++)
		for (int j = 1 ; j <= n ; j++)
			scanf("%1d",&c[i][j]);
	for (int i = 1 ; i <= n ; i++)
		scanf("%d" , &a[i]);
	for (int i = 1 ; i <= n ; i++)
		if (a[i] == 0) ds.push(i) , sel[i] = 1 , sl++;
	while(!ds.empty())
	{
		int u = ds.front();ds.pop();
		for (int i = 1 ; i <= n ; i++)
		{
			a[i] -= c[u][i];
			if (a[i] == 0 && !sel[i])
				ds.push(i) , sel[i] = 1 , sl++;
		}
	}
	printf("%d\n" , sl);
	for (int i = 1 ; i<= n ; i++)
		if (sel[i])
			printf("%d " , i);
	printf("\n");
	return 0;
}
