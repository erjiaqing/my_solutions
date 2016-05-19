#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

namespace ejq{
const int maxn = 50 + 1;
struct edge{
    int t, c, v, n;
    edge(){}
    edge(int _t, int _c, int _v, int _n):
        t(_t), c(_c), v(_v), n(_n){}
}edg[maxn * maxn * 2 * 4 * 4];
int h[maxn * maxn * 2];

int dist[maxn * maxn * 2];
int prev[maxn * maxn * 2];
int pree[maxn * maxn * 2];
bool inq[maxn * maxn * 2];

int nid[maxn][maxn][2], tn = 2;
const int S = 0, T = 1;

int te;

void addedge(int s, int t, int c, int v)
{
    int e1 = te++;
    int e2 = te++;
    edg[e1] = edge(t, c, v, h[s]);h[s] = e1;
    edg[e2] = edge(s, -c, 0, h[t]);h[t] = e2;
}

int spfa()
{
    queue<int> q;
    memset(dist, 0x3f, sizeof(int) * tn);
    memset(prev, -1, sizeof(int) * tn);
    memset(pree, -1, sizeof(int) * tn);
    dist[S] = 0;
    q.push(S);
    int u, v;
    while (!q.empty())
    {
        u = q.front();q.pop();
        inq[u] = false;
        for (int p = h[u]; ~p; p = edg[p].n)
        {
            v = edg[p].t;
            if (edg[p].v)
            {
                if (dist[v] > dist[u] + edg[p].c)
                {
                    dist[v] = dist[u] + edg[p].c;
                    prev[v] = u;
                    pree[v] = p;
                    if (!inq[v])
                    {
                        inq[v] = true;
                        q.push(v);
                    }
                }
            }
        }
    }
    return ~prev[T];
}

int min_cost_max_flow(int tot)
{
    int u;
    int totflow = 0, totcost = 0;
    while (spfa())
    {
        int tmpf = 0x3f3f3f3f;
        for (u = T; ~prev[u]; u = prev[u])
            tmpf = min(tmpf, edg[pree[u]].v);
        for (u = T; ~prev[u]; u = prev[u])
        {
            edg[pree[u]].v -= tmpf;
            edg[pree[u] ^ 1].v += tmpf;
            totcost += tmpf * edg[pree[u]].c;
        }
        totflow += tmpf;
    }
    return totflow == tot ? totcost : -1;
}

int sol()
{
    int m, n, tv;
    int c0 = 0, c1 = 0, c2 = 0;
    scanf("%d%d", &m, &n);
    memset(h, -1, sizeof(int) * (m * n * 2 + 2));
    te = 0;
    tn = 2;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            scanf("%d", &tv);
            //cin >> tv;
            nid[i][j][0] = tn++;
            nid[i][j][1] = tn++;
            if (tv == 0)
            {
                addedge(S, nid[i][j][0], 0, 1);
                addedge(nid[i][j][1], T, 0, 1);
                c0++;
            } else if (tv & 1)
            {
                addedge(S, nid[i][j][0], 0, 1);
                c1++;
            } else if ((tv & 1) ^ 1)
            {
                addedge(nid[i][j][1], T, 0, 1);
                c2++;
            }
        }
    }
    for (int i = 1; i < m; i++)
        for (int j = 1; j <= n; j++)
        {
            scanf("%d", &tv);
            addedge(nid[i][j][0], nid[i + 1][j][1], tv, 1);
            addedge(nid[i + 1][j][0], nid[i][j][1], tv, 1);
        }
    for (int i = 1; i <= m; i++)
        for (int j = 1; j < n; j++)
        {
            scanf("%d", &tv);
            addedge(nid[i][j][0], nid[i][j + 1][1], tv, 1);
            addedge(nid[i][j + 1][0], nid[i][j][1], tv, 1);
        }
    if (c1 != c2) return -1;
    return min_cost_max_flow(c0 + c1);
}

int main()
{
    int c;
    scanf("%d", &c);
    for (int i = 1; i <= c; i++)
        printf("Case #%d: %d\n", i, sol());
    return 0;
}
}

int main()
{
    return ejq::main();
}
