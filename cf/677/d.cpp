#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
#define x first
#define y second

int n, m, p;

int getid(int x, int y) {return x * m + y;}
vector<pii> tp[300 * 300];
int label[300 * 300];
pii pos[300 * 300];
//vector<pii> edg[300 * 300];
int dist[300 * 300];

priority_queue<pii, vector<pii>, greater<pii> > que;

int main()
{
	scanf("%d%d%d", &n, &m, &p);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			int t;
			scanf("%d", &t);
			tp[t - 1].push_back(pii(i, j));
			label[getid(i, j)] = t - 1;
			pos[getid(i, j)] = pii(i, j);
		}
	memset(dist, 0x3f, sizeof(dist));
	for (pii nd : tp[0])
	{
		dist[getid(nd.x, nd.y)] = nd.x + nd.y;
		que.push(pii(dist[getid(nd.x, nd.y)], getid(nd.x, nd.y)));
	}
	/*
	for (int i = 0; i < p - 1; i++)
		for (pii nd : tp[i])
			for (pii ndd : tp[i + 1])
				edg[getid(nd.x, nd.y)].push_back(pii(getid(ndd.x, ndd.y), abs(nd.x - ndd.x) + abs(nd.y - ndd.y)));
				*/
	while (!que.empty())
	{
		pii queh = que.top();
		que.pop();
		if (label[queh.y] == p - 1) break;
		if (dist[queh.y] != queh.x) continue;
		for (pii nxt : tp[label[queh.y] + 1])
			if (dist[getid(nxt.x, nxt.y)] > dist[queh.y] + abs(pos[queh.y].x - nxt.x) + abs(pos[queh.y].y - nxt.y))
			{
				dist[getid(nxt.x, nxt.y)] = dist[queh.y] + abs(pos[queh.y].x - nxt.x) + abs(pos[queh.y].y - nxt.y);
				que.push(pii(dist[getid(nxt.x, nxt.y)], getid(nxt.x, nxt.y)));
			}
	}
	printf("%d\n", dist[getid(tp[p - 1][0].x, tp[p - 1][0].y)]);
	return 0;
}
