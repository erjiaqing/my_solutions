#include <bits/stdc++.h>
using namespace std;
const int maxn = 105;
struct mq{
	int x, y, z, a;
	mq(){}
	mq(int _x, int _y, int _z, int _a):
		x(_x), y(_y), z(_z), a(_a){}
}m[100000], q[100000];

long long p1[maxn][maxn], p2[maxn][maxn];
int n, M, Q;

long long ans[100000];

void process_single_lay(int lay)
{
	memset(p1, 0, sizeof(p1));
	memset(p2, 0, sizeof(p2));
	for (int i = 0; i < M; i++)
	{
		int x, y, z, a, bx, by, ex, ey;
		x = m[i].x, y = m[i].y, z = m[i].z, a = m[i].a;
		//cerr << z << ' ' << z + a << endl;
		if (z <= lay && z + a > lay)
		{
			bx = x + lay - z;
			ex = x + a - 1;
			by = y + lay - z;
			ey = y + a - 1;
			p1[bx][by]++;
			p1[ex + 1][ey + 1]--;
			p2[ex + 1][by]--;
			p2[ex + 1][ey + 1]++;
			//cerr << bx << ' ' << by << ' ' << ex << ' ' << ey << endl;
		}
	}
	for (int i = lay; i <= n; i++)
		for (int j = lay; j <= i; j++)
		{
			p1[i][j] += p1[i - 1][j - 1];
			p2[i][j] += p2[i][j - 1];
		}
	for (int i = lay; i <= n; i++)
		for (int j = lay; j <= i; j++)
			p1[i][j] += p2[i][j];
	for (int i = lay; i <= n; i++)
		for (int j = lay; j <= i; j++)
			p1[i][j] += p1[i - 1][j];
	for (int i = lay; i <= n; i++)
		for (int j = lay; j <= i; j++)
			p2[i][j] = p2[i][j - 1] + p1[i][j];
	for (int i = lay; i <= n; i++)
		for (int j = lay; j <= i; j++)
			p1[i][j] = p1[i - 1][j - 1] + p2[i][j];
	for (int i = lay; i <= n; i++)
		for (int j = lay; j <= i; j++)
			p2[i][j] += p2[i - 1][j];
	//---
	/*
	printf("Lay %d\n", lay);
	for (int j = n; j >= 1; j--)
	{
		for (int i = 1; i <= n; i++)
			printf("%d\t", p1[i][j]);
		printf("\n");
	}
	printf("------\n");
	for (int j = n; j >= 1; j--)
	{
		for (int i = 1; i <= n; i++)
			printf("%d\t", p2[i][j]);
		printf("\n");
	}*/

	for (int i = 0; i < Q; i++)
	{
		int x, y, z, a, bx, by, ex, ey;
		x = q[i].x;y = q[i].y;z = q[i].z;a = q[i].a;
		if (z <= lay && z + a > lay)
		{
			bx = x + lay - z;
			by = y + lay - z;
			ex = x + a - 1;
			ey = y + a - 1;
			ans[i] += p1[ex][ey] - p1[bx - 1][by - 1] - p2[ex][by - 1] + p2[bx - 1][by - 1];
		}
	}
}

int main()
{
	scanf("%d%d%d", &n, &M, &Q);
	for (int i = 0; i < M; i++)
		scanf("%d%d%d%d", &m[i].x, &m[i].y, &m[i].z, &m[i].a);
	for (int i = 0; i < Q; i++)
		scanf("%d%d%d%d", &q[i].x, &q[i].y, &q[i].z, &q[i].a);
	for (int i = 1; i <= n; i++)
		process_single_lay(i);
	for (int i = 0; i < Q; i++)
		printf("%lld\n", ans[i]);
	return 0;
}

