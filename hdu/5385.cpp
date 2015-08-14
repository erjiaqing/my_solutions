#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
typedef pair<int , int> pii;

const int maxn = 100005;

pii edg[maxn];
vector<int> e[maxn];
int nid[maxn];
int linked[maxn];

void prep(int node)
{
	for (int i = 0 ; i < e[node].size() ; i++)
		if ((linked[e[node][i]] == -1) && (nid[e[node][i]] == -1))
			linked[e[node][i]] = node;
}

void work()
{
	int n , m , id = 0;
	scanf("%d%d" , &n , &m);
	memset(nid , -1 , sizeof(nid));
	memset(linked , -1 , sizeof(linked));
	nid[1] = 0;
	for (int i = 1 ; i <= n ; i++)
		e[i].clear();
	for (int i = 0 ; i < m ; i++)
	{
		int u , v;
		scanf("%d%d" , &u , &v);
		e[u].push_back(v);
		edg[i] = pii(u , v);
	}
	prep(1);
	int l = 2 , r = n;
	while (l <= r)
	{
		if (~linked[l])
		{
			prep(l);
			nid[l] = ++id;
			l++;
			continue;
		}
		if (~linked[r])
		{
			prep(r);
			nid[r] = ++id;
			r--;
			continue;
		}
	}
	for (int i = 0 ; i < m ; i++)
		if (linked[edg[i].second] == edg[i].first)
			printf("%d\n" , nid[edg[i].second] - nid[edg[i].first]);
		else
			printf("%d\n" , n);
}

int main()
{
	int t;
	scanf("%d" , &t);
	while (t--)
		work();
	return 0;
}
