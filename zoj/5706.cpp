#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <cstring>
using namespace std;
const int maxn = 100000 + 5;
typedef pair<int, int> pii;
typedef pair<int, pii> pipii;
vector<pipii> v2;
vector<pii> v1[maxn];
long long f[maxn];
int ff[maxn];
bool inq[maxn];
int F(int x) {return ff[x] == x ? x : (ff[x] = F(ff[x]));}
void U(int x, int y) {if (F(x) != F(y)) ff[F(x)] = F(y);}
#define x first
#define y second
long long build(int n)
{
	long long ans = 0;
	for (int i = 0; i < n; i++) ff[i] = i;
	for (int i = 0; i < v2.size(); i++)
		if (F(v2[i].y.x) != F(v2[i].y.y))
		{
			ans += v2[i].x;
			U(v2[i].y.x, v2[i].y.y);
		}
	return ans;
}

long long sol(int n)
{
	memset(f, 0x3f, sizeof(long long) * n);
	memset(inq, 0, sizeof(bool) * n);
	f[0] = 0;
	queue<int> q;
	long long ans = 0;
	q.push(0);
	while (!q.empty())
	{
		int v = q.front();q.pop();
		//cerr << v << endl;
		for (pii e : v1[v])
		{
			if (f[e.y] > f[v] + e.x)
			{
				f[e.y] = f[v] + e.x;
				if (!inq[e.y])
				{
					q.push(e.y);
					inq[e.y] = true;
				}
			}
		}
		inq[v] = 0;
	}
	for (int i = 0; i < n; i++)
		ans += f[i];
	return ans;
}

void sol()
{
	int n, m, x, y, d, e;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		v1[i].clear();
	v2.clear();
	for (int i = 0; i < m; i++)
	{
		cin >> x >> y >> d >> e;
		v1[x].push_back(pii(d, y));
		v1[y].push_back(pii(d, x));
		v2.push_back(pipii(e, pii(x, y)));
	}
	sort(v2.begin(), v2.end());
	cout << sol(n) << " " << build(n) << "\n";
}
int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin >> t;
	while (t--)
		sol();
	return 0;
}

