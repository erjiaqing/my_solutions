#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <utility>
#include <cassert>
#include <queue>
#include <algorithm>
using namespace std;
namespace sol{
    const int maxn = 200000 + 1;
    vector<int> edg[maxn];
    vector<int> ans;
	priority_queue<int> pq;
	int deg[maxn], n, m;
    int main()
    {
        int u, v;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < m; i++)
        {
            scanf("%d%d", &u, &v);
            edg[v].push_back(u);
            deg[u]++;
        }
        for (int i = 1; i <= n; i++)
        	if (deg[i] == 0) pq.push(i);
        for (int i = 1; i <= n; i++)
        {
            int rem = pq.top();
			pq.pop();
			ans.push_back(rem);
            for (int j = 0; j < edg[rem].size(); j++)
				if ((--deg[edg[rem][j]]) == 0)
					pq.push(edg[rem][j]);
        }
        for (int i = n - 1; i >= 0; i--)
            printf("%d%s", ans[i], i == 0 ? "\n" : " ");
        return 0;
    }
}
int main()
{
    return sol::main();
}
