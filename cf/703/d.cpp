#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000000 + 5;
struct query{
	int x, y, id;
}que[maxn];
int n, m;
int a[maxn], b[maxn], r[maxn];
int blk[maxn], blsz;
int ans[maxn], cnt[maxn], curans;
void update(int x, int delta)
{
	int tx = cnt[x];
	if ((cnt[x] += delta) != 0 && tx != 0)
		curans ^= r[x];
}
int main()
{
	scanf("%d", &n);
	blsz = sqrt(n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		b[i - 1] = a[i];
		blk[i] = i / n;
	}
	sort(&b[0], &b[n]);
	int tb = unique(&b[0], &b[n]) - b;
	for (int i = 0; i < tb; i++)
		r[i] = b[i];
	for (int i = 1; i <= n; i++)
		a[i] = lower_bound(&b[0], &b[tb], a[i]) - b;
	scanf("%d", &m);
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d", &que[i].x, &que[i].y);
		que[i].id = i;
	}
	sort(&que[0], &que[m], [](const query &a, const query &b){
			if (blk[a.x] == blk[b.x]) return a.y < b.y;
			return a.x < b.x;
			});
	int curl = 0, curr = 0;
	for (int i = 0; i < m; i++)
	{
		if (i % 1000 == 0) cerr << i << endl; 
	//	cerr << que[i].x << ' ' << que[i].y << endl;
		for (; curl < que[i].x; curl++) update(a[curl], -1);
		for (; curl > que[i].x; curl--) update(a[curl - 1], 1);
		for (; curr < que[i].y; curr++) update(a[curr + 1], 1);
		for (; curr > que[i].y; curr--) update(a[curr], -1);
		ans[que[i].id] = curans;
	}
	for (int i = 0; i < m; i++)
	{
		printf("%d\n", ans[i]);
	}
	return 0;
}
