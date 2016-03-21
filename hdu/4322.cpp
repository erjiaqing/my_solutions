#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn = 30;
const int _s = 0, _t = maxn - 1;
struct edg {
	int source, target, volume, cost, next;
	edg(){}
	edg(const int &_s, const int &_t, const int &_v,
			const int &_c, const int &_n):
		source(_s), target(_t), volume(_v), cost(_c), next(_n){}
}edge[30 * 30 * 2];
int head[maxn], tot_edge;
int prev_edge[maxn], dist[maxn], in_queue[maxn];
int like[maxn][maxn], b[maxn], available[maxn];
int n, m, k;

void addedge(int s, int t, int volume, int cost) {
	edge[tot_edge] = edg(s, t, volume, -cost, head[s]);head[s] = tot_edge++;
	edge[tot_edge] = edg(t, s, 0, cost, head[t]);head[t] = tot_edge++;
}
bool find_flow() {
	queue<int> q;
	q.push(_s);
	memset(dist, 0x3f, sizeof(dist));
	memset(prev_edge, -1, sizeof(prev_edge));
	memset(in_queue, 0, sizeof(in_queue));
	dist[_s] = 0;
	while (!q.empty()) {
		int u = q.front();
		in_queue[u] = 0;
		q.pop();
		for (int _edg = head[u]; ~_edg; _edg = edge[_edg].next) {
			if (edge[_edg].volume && dist[u] + edge[_edg].cost < dist[edge[_edg].target]) {
				int target = edge[_edg].target;
				prev_edge[target] = _edg;
				dist[edge[_edg].target] = dist[u] + edge[_edg].cost;
				if (!in_queue[target]) {
					in_queue[target] = true;
					q.push(target);
				}
			}
		}
	}
	return ~prev_edge[_t];
}

int max_flow_1() {
	int tot_flow = 0;
	while (find_flow()) {
		int max_flow = 0x3f3f3f3f;
		for (int cur = prev_edge[_t]; ~cur; cur = prev_edge[edge[cur].source])
			max_flow = min(max_flow, edge[cur].volume);
		for (int cur = prev_edge[_t]; ~cur; cur = prev_edge[edge[cur].source])
			edge[cur].volume -= max_flow, edge[cur ^ 1].volume += max_flow;
		tot_flow += max_flow;
	}
	return tot_flow;
}

bool sol() {
	memset(head, -1, sizeof(head));
	tot_edge = 0;
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= m; i++) {
		scanf("%d", &b[i]);
		addedge(i + n, _t, b[i] / k, k);
		addedge(i + n, _t, b[i] % k ? 1 : 0, b[i] % k);
	}
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++) {
			scanf("%d", &like[i][j]);
			if (like[i][j])
				addedge(j, i + n, 1, 0);
		}
	for (int j = 1; j <= n; j++) addedge(_s, j, 1, 0);
	max_flow_1();
	int need_flow = 0;
	for (int i = 1; i <= m; i++) {
		b[i] = 0;
		for (int u = head[i + n]; ~u; u = edge[u].next)
			if (edge[u].target == _t)
				b[i] -= edge[u].cost * edge[u].volume;
		need_flow += b[i];
	}
	for (int u = head[_s]; ~u; u = edge[u].next)
		if (edge[u].target >= 1 && edge[u].target <= n)
			available[edge[u].target] = (edge[u].volume == 1);
	memset(head, -1, sizeof(head));
	tot_edge = 0;
	for (int j = 1; j <= n; j++) addedge(_s, j, available[j], 0);
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++)
			if (!like[i][j])
				addedge(j, i + n, 1, 0);
		addedge(i + n, _t, b[i], 0);
	}
	need_flow -= max_flow_1();
	return need_flow == 0;
}
int main() {
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t;)
		printf("Case #%d: %s", ++i, sol() ? "YES\n" : "NO\n");
	return 0;
}
