#include <iostream>
#include <bits/stdc++.h>
#include <cstring>
#include <cstdio>
#include <vector>
#include <set>
#include <utility>
using namespace std;

const int maxn = 500000 + 5;

int bit[maxn];
int n, m;

int lowbit(int x)
{
	return x & (-x);
}

void add(int x, int v)
{
	for (; x < m + 4; x += lowbit(x))
		bit[x] += v;
}

int qury(int x)
{
	int ret = 0;
	for (; x; x -= lowbit(x))
		ret += bit[x];
	return ret;
}

typedef pair<pair<int, int>, int> ppiii;
typedef pair<int, pair<pair<int, int>, int> > pippiii;
set<int> qux;
vector<int> quy;

ppiii query[maxn];
vector<pippiii> edi0, edi1;

int pos[1000 + 5];
int s[2][1000 + 5];
int a[2][1000 + 5];


#define x first
#define y second

char ret[maxn];

void sol()
{
	edi0.clear();
	edi1.clear();
	qux.clear();
	quy.clear();
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[(i & 1) ^ 1][i]);
		pos[i] = pos[i - 1] + a[(i & 1) ^ 1][i];
		s[0][i] = s[0][i - 1] + a[0][i];
		s[1][i] = s[1][i - 1] + a[1][i];
	}
	quy.push_back(-1);
	for (int i = 0; i < m; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		query[i] = make_pair(make_pair(x, y), i);
		qux.insert(x);
		quy.push_back(y);
	}
	memset(ret, '0', sizeof(char) * m);
	ret[m] = 0;
	int ta = 0, tb = 0;
	quy.push_back(1000000009);
	sort(quy.begin(), quy.end());
	sort(&query[0], &query[m]);
	tb = unique(quy.begin(), quy.end()) - quy.begin();
	memset(bit, 0, sizeof(int) * tb);
	for (int i = 1; i <= n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			int ra = s[0][j] - s[0][i - 1];
			int la = ra - a[0][i] - a[0][j];
			int rb = s[1][j] - s[1][i - 1];
			int lb = rb - a[1][i] - a[1][j];
			edi0.push_back(make_pair(la, make_pair(make_pair(lb, rb), 1)));
			edi1.push_back(make_pair(ra, make_pair(make_pair(lb, rb), -1)));
		//	printf("0 in (%d, %d) while 1 in (%d, %d)\n", la, ra, lb, rb);
		}
	}
	sort(edi0.begin(), edi0.end());
	sort(edi1.begin(), edi1.end());
	int curr0 = 0, curr1 = 0;
	int currq = 0;
	for (int v : qux)
	{
		//cerr << "Curr: " << v << endl;
		while (curr0 < edi0.size() && edi0[curr0].x <= v)
		{
			add(lower_bound(&quy[0], &quy[tb], edi0[curr0].y.x.x) - &quy[0], 1);
			add(lower_bound(&quy[0], &quy[tb], edi0[curr0].y.x.y + 1) - &quy[0], -1);
		//	printf("ADD [%d, %d)\n", quy[lower_bound(&quy[0], &quy[tb], edi0[curr0].y.x.x) - &quy[0]], quy[lower_bound(&quy[0], &quy[tb], edi0[curr0].y.x.y + 1) - &quy[0]]);
			curr0++;
		}
		while (curr1 < edi1.size() && edi1[curr1].x < v)
		{
			add(lower_bound(&quy[0], &quy[tb], edi1[curr1].y.x.x) - &quy[0], -1);
			add(lower_bound(&quy[0], &quy[tb], edi1[curr1].y.x.y + 1) - &quy[0], 1);
			//printf("DEL [%d, %d)\n", quy[lower_bound(&quy[0], &quy[tb], edi1[curr1].y.x.x) - &quy[0]], quy[lower_bound(&quy[0], &quy[tb], edi1[curr1].y.x.y + 1) - &quy[0]]);
			curr1++;
		}
		while (currq < m && query[currq].x.x <= v)
		{
			ret[query[currq].y] = qury(lower_bound(&quy[0], &quy[tb], query[currq].x.y) - &quy[0]) ? '1' : '0';
		//	printf("QRY %d\n", quy[lower_bound(&quy[0], &quy[tb], query[currq].x.y) - &quy[0]]);
			currq++;
		}
	}
	printf("%s\n", ret);
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
		sol();
	return 0;
}
