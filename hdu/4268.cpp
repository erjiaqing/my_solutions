#include <set>
#include <cstdio>
#include <utility>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define x first
#define y second
const int maxn = 100000 + 5;
typedef pair<int,int> pii;
typedef set<int>::iterator sii;
int N;
int n, tx, ty, ans;
pii Axy[maxn], Bxy[maxn];
set<int> P;
void work()
{
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf("%d%d", &Axy[i].x, &Axy[i].y);
	for (int i=0;i<n;i++)
		scanf("%d%d", &Bxy[i].x, &Bxy[i].y);
	sort(&Axy[0], &Axy[n]);sort(&Bxy[0], &Bxy[n]);
	int pos = 0;
	for (int i = 0; i < n; i++)
	{
		while (pos < n && Bxy[pos].x <= Axy[i].x) P.insert(Bxy[pos++].y);
		sii p = P.upper_bound(Axy[i].y);
		if (p == P.begin()) continue;
		p--;ans++;P.erase(p);
	}
	printf("%d\n",ans);
}
void reset()
{
	ans = 0;
	P.clear();
}
int main()
{
	scanf("%d",&N);
	while (N--)
		work(),reset();
	return 0;
}
