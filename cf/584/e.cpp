#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <algorithm>
#include <set>
using namespace std;
const int maxn = 2000 + 1;
int p[maxn], s[maxn];
int pp[maxn], ps[maxn];
int pre[maxn], nxt[maxn], lst;
int n;
typedef pair<int, int> pii;
set<pii, greater<pii> > pq;
int k, cost;
pii op[maxn * maxn];
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &p[i]), pp[p[i]] = i;
	for (int i = 1; i <= n; i++)
		scanf("%d", &s[i]), ps[s[i]] = i;
	for (int i = 1; i <= n; i++)
		p[i] = ps[p[i]], pp[p[i]] = i;
	int pnt = 1;
	for (int i = n; i >= 1; i--)
	{
		int pos = pp[i] + 1;
		//cerr << i << " " << pos << endl;
		while (pos <= i)
		{
			if (p[pos] <= pp[i])
			{
				cost += pos - pp[i];
				op[k++] = pii(pos, pp[i]);
				//cerr << "SWP" << p[pos] << "," << p[pp[i]] << endl;
				swap(p[pos], p[pp[i]]);
				pp[p[pos]] = pp[i];
				pp[i] = pos;
			}
			pos++;
		}
	}
	printf("%d\n%d\n", cost, k);
	for (int i = 0; i < k; i++)
		printf("%d %d\n", op[i].first, op[i].second);
	return 0;
}
