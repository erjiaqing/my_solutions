#include <bits/stdc++.h>
using namespace std;
const int maxn = 500 + 5;
typedef pair< int , int > pii;
int n;
bool chkamb(pii a,pii b)
{
	int pa = n - a.first - a.second;
	if (a == pii(-1 , -1) || b == pii(-1 , -1))
		return false;
	return a == b || a.first + pa <= b.first;
}
void work()
{
	int ta , tb , ans = 0;
	vector<pii> a;
	vector<int> e[maxn];
	int maxd[maxn];
	memset(maxd , 0 , sizeof(maxd));
	for (int i = 0 ; i < n ; i++)
	{
		scanf("%d%d" , &ta , &tb);
		a.push_back(pii(ta , tb));
	}
	sort(a.begin() , a.end());
	for (int i = 0 ; i < n ; i++)
	{
		int tc = n - a[i].first - a[i].second;
		if (tc <= 0)
		{
			a[i] = pii(-1 , -1);
			continue;
		}
		for (int j = i + tc ; j < n ; j++)
		{
			if (a[j] == a[i])
				a[j] = pii(-1 , -1);
			else
				break;
		}
	}
	for (int i = 0 ; i < n ; i++)
		for (int j = i + 1 ; j < n ; j++)
			if (chkamb(a[i] , a[j]))
				e[i].push_back(j);
	for (int i = 0 ; i < n ; i++)
	{
		if (maxd[i] > 0) continue;
		if (a[i] == pii(-1 , -1)) continue;
		queue <int> q;
		maxd[i] = 1;
		q.push(i);
		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			for (int v = 0 ; v < e[u].size(); v++)
			{
				if (maxd[e[u][v]] < maxd[u] + 1)
				{
					q.push(e[u][v]);
					maxd[e[u][v]] = maxd[u] + 1;
				}
			}
		}
	}
	for (int i = 0 ; i < n ; i++)
		ans = max(ans , maxd[i]);
	printf("%d\n" , ans);
}
int main()
{
	while (~scanf("%d" , &n))
		work();
}
