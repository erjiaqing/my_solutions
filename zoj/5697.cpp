#include <iostream>
#include <utility>
#include <vector>
using namespace std;
const int maxn = 100000 + 5;
vector<int> q[maxn];
long long dep[maxn], val[maxn], ans[maxn];
long long rans = 0;
 dfs(int x)
{
	for (int i = 0; i < q[x].size(); i++)
	{
	}
}
long long sol()
{
	int n = 0;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> val[i];
		q[i].clear();
	}
	dep[1] = (val[1] != 0);
	rans = val[1] * dep[1];
	for (int i = 2; i <= n; i++)
	{
		int p = 0;
		cin >> p;
		q[p].push_back(i);
	}
	return rans;
}
int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin >> t;
	while (t--)
		cout << sol() << "\n";
	return 0;
}
