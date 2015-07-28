#include <bits/stdc++.h>
using namespace std;
const int maxn = 100 + 5;
int sze[maxn];
int n , k , ta , tb;
void work()
{
	vector<int> e[maxn];
	memset(sze , 0 , sizeof(sze));
	int que[maxn] , qh , qt , nt[maxn];
	memset(nt , 0 , sizeof(nt));
	for (int i = 1 ; i < n ; i++)
	{
		cin >> ta >> tb;
		e[ta].push_back(tb);
		nt[tb] = true;
	}
	int root = 0;
	for (int i = 1 ; i <= n ; i++)
		if (!nt[i])
		{
			root = i;
			break;
		}
	que[qh = qt = 0] = root;
	while (qh <= qt)
	{
		int u = que[qh++];
		sze[u] = 1;
//		cerr << u << endl;
		for (int i = 0 ; i < e[u].size() ; i++)
			que[++qt] = e[u][i];
	}
	for (int i = qt ; i >= 0 ; i--)
	{
		int u = que[i];
		for (int j = 0 ; j < e[u].size() ; j++)
			sze[u] += sze[e[u][j]];
	}
	int ans = 0;
	for (int i = 1 ; i <= n ; i++)
	{
//		cerr << sze[i] << endl;
		if (sze[i] == k + 1)
			ans++;
	}
	cout << ans << endl;
}
int main()
{
	while (cin >> n >> k)
		work();
	return 0;
}
