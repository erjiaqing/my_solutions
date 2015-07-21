#include <bits/stdc++.h>
using namespace std;
const int maxm = 60000 + 5;
const int maxn = 2000 + 5;
struct Edge {
	int v , c , n;
}E[maxm * 2];
struct Edge2{
	int u , v , c , n;
}E2[maxm * 2];
int h[maxn] , h2[maxn] , te1 , te2;
int ds[maxn] , dt[maxn] , cnt[maxn] , lay[maxn] , inq[maxn];
int n , m;
void addedge(int u , int v , int c)
{
	int e1 = te2++ , e2 = te2++;
	E2[e1].u = u;E2[e1].v = v;E2[e1].c = c;E2[e1].n = h2[u];h2[u] = e1;
	E2[e2].u = v;E2[e2].v = u;E2[e2].c = c;E2[e2].n = h2[v];h2[v] = e2;
}
void addedge(int u , int v)
{
	E[te1].v = v;
	E[te1].c = 1;
	E[te1].n = h[u];
	h[u] = te1++;
	E[te1].v = u;
	E[te1].c = 0;
	E[te1].n = h[v];
	h[v] = te1++;
}
bool build()
{
	int u;
	memset(lay , -1 , sizeof(lay));
	queue <int> Q;
	Q.push(1);lay[1] = 0;
	while (!Q.empty())
	{
		u = Q.front();Q.pop();
		for (int c = h[u] ;~c ; c=E[c].n)
		{
			if (E[c].c && lay[E[c].v] == -1)
			{
				lay[E[c].v] = lay[u] + 1;
				Q.push(E[c].v);
			}
		}
	}
	return lay[n] != -1;
}
int find(int u, int low)
{
	if (u == n)
		return low;
	int ans = 0 , tans;
	for (int c = h[u] ; (~c) && low ; c = E[c].n)
		if (lay[E[c].v] == lay[u] + 1 && (tans = find(E[c].v , min(low , E[c].c))))
		{
			E[c].c -= tans;
			E[c^1].c += tans;
			ans += tans;
			low -= tans;
		}
	return ans;
}
int dinic()
{
	int ans = 0 , tans;
	while (build())
		while ((tans = find(1 , maxm * 10)))
			ans += tans;
	return ans;
}
bool work()
{
	te1 = te2 = 0;
	memset(h , -1 , sizeof(h));
	memset(h2, -1 , sizeof(h2));
	memset(ds, 0x3f , sizeof(ds));
	memset(dt, 0x3f , sizeof(dt));
	memset(cnt , 0x3f , sizeof(cnt));
	if (scanf("%d%d" , &n , &m) == -1)
		return false;
	int __u , __v , __c;
	for (int i = 0 ; i < m ; i++)
	{
		scanf("%d%d%d" , &__u , &__v , &__c);
		addedge(__u , __v , __c);
	}
	ds[1] = dt[n] = cnt[1] = 0;
	queue <int> Q;
	Q.push(1);
	while (!Q.empty())
	{
		int u = Q.front();Q.pop();
		inq[u] = false;
		for (int i = h2[u] ; ~i ; i = E2[i].n)
		{
			int v = E2[i].v;
			if (ds[v] >= ds[u] + E2[i].c)
			{
				if ((ds[v] > ds[u] + E2[i].c) && !inq[v])
				{
					Q.push(v);
					inq[v] = true;
				}
				if ((ds[v] == ds[u] + E2[i].c))
				{
					cnt[v] = min(cnt[v] , cnt[u] + 1);
				}
				else
				{
					cnt[v] = cnt[u] + 1;
					ds[v] = ds[u] + E2[i].c;
				}
			}
		}
	}
	Q.push(n);
	while (!Q.empty())
	{
		int u = Q.front();Q.pop();
		inq[u] = false;
		for (int i = h2[u] ; ~i ; i = E2[i].n)
		{
			int v = E2[i].v;
			if (dt[v] > dt[u] + E2[i].c)
			{
				dt[v] = dt[u] + E2[i].c;
				if (!inq[v])
				{
					Q.push(v);
					inq[v] = true;
				}
			}
		}
	}
	int min_len = ds[n];
	for (int i = 0 ; i < te2 ; i++)
		if (ds[E2[i].u] + E2[i].c + dt[E2[i].v] == min_len)
			addedge(E2[i].u , E2[i].v);
	printf("%d %d\n" , dinic() , m - cnt[n]);
	return true;
}
int main()
{
	while (work());
	return 0;
}
