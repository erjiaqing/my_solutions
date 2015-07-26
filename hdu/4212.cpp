#include <bits/stdc++.h>
using namespace std;
const int maxn = 22 + 5;
vector<int> d[maxn];
set<int> *q1 , *q2;
int c[1 << 22];
void dfs(int l , int n , int t , int b)
{
	if (l == 23 || t == 0)
	{
		if (t == 0)
			d[n].push_back(b);
		return;
	}
	if (l > t && t != 0)
		return;
	dfs(l + 1 , n , t , b);
	if (l <= t)
		dfs(l + 1 , n , t - l , b | (1 << (l - 1)));
}
int lowbit(int x)
{
	int ret = 0;
	while (x)
	{
		x -= (x & (-x));
		ret++;
	}
	return ret;
}
void cal()
{
	for (int i = 0 ; i < (1 << 22) ; i++)
		c[i] = lowbit(i);
}
int n , v;
void work(int caseno)
{
	int u = 0 , ans = 0;
	int a[maxn];
	for (int i = 0 ; i < v ; i++)
		scanf("%d" , &a[i]);
	q1 = new set<int>;
	q2 = new set<int>;
	q2->insert(0);
	for (int i = 0 ; i < v ; i++)
	{
		swap(q1 , q2);
//		cerr << a[i] << endl;
//		cerr << d[a[i]].size() << endl;
		for (set<int> :: iterator sii = q1->begin() ; sii != q1->end() ; sii++)
		{
			int tq = *sii;
			for (int m = 0 ; m < d[a[i]].size() ; m++)
			{
				if (d[a[i]][m] >= (1 << n))
					break;
				if ( (tq & d[a[i]][m]) == 0)
				{
				//	cerr << tq << endl;
					q2->insert(tq | d[a[i]][m]);
					ans = max(ans , c[tq | d[a[i]][m]]);
				}
			}
		}
		q1->clear();
	}
	delete q1;
	delete q2;
	printf("Game %d: %d\n" , caseno , ans);
}
int main()
{
	int c = 0;
	for (int i = 1 ; i <= 22 ; i++)
	{
		dfs(1 , i , i , 0);
		sort(d[i].begin() , d[i].end());
//		cerr << d[i].size() << endl;
	}
	cal();
//	cerr << "fi\n";
	while (scanf("%d%d" , &n , &v) && n && v)
		work(++c);
	return 0;
}
