#include <bits/stdc++.h>
using namespace std;
int n;
int m[1000 + 1];
int q[1000][1000];
int qmx[1000];
int rq[1000][1000];
int tq[1000][1000];
int check()
{
	int cur = 0;
	int ans = 0;
	priority_queue<pair<int, int> > pq;
	for (int i = 0; i < n; i++)
	{
		qmx[i] = 0;
		for (int j = 0; j < m[i]; j++)
		{
			tq[i][j] = q[i][j] - j;
			qmx[i] = max(qmx[i], tq[i][j]);
		}
		pq.push(make_pair(-qmx[i], i));
	}
	while (!pq.empty())
	{
		auto tp = pq.top();
		int tmp = 0;
		pq.pop();
		int tr = -tp.first;
		if (cur < tr)
		{
			ans += tr - cur;
			tmp = tr - cur;
		}
		cur += tmp + m[tp.second];
	}
	return ans;
}
int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &m[i]);
		for (int j = 0; j < m[i]; j++)
			scanf("%d", &q[i][j]);
	}
	int qq;
	scanf("%d", &qq);
	while (qq--)
	{
		int a, b, x_, y_;
		scanf("%d%d%d%d", &x_, &a, &y_, &b);
		x_--;y_--;
		for (int i = 0; i < b; i++)
			rq[x_][i] = q[y_][i];
		for (int i = b; i < m[x_] + b - a; i++)
			rq[x_][i] = q[x_][i - b + a];
		for (int i = 0; i < a; i++)
			rq[y_][i] = q[x_][i];
		for (int i = a; i < m[y_] + a - b; i++)
			rq[y_][i] = q[y_][i - a + b];
		m[x_] += b - a;
		m[y_] -= b - a;
		for (int i = 0; i < m[x_]; i++)
			q[x_][i] = rq[x_][i];
		for (int i = 0; i < m[y_]; i++)
			q[y_][i] = rq[y_][i];
//		for (int i = 0; i < n; i++)
//		{
//			for (int j = 0; j < m[i]; j++)
//			{
//				printf("%d ", q[i][j]);
//			}
//			printf("\n");
//		}
		printf("%d\n", check());
	}
	return 0;
}
