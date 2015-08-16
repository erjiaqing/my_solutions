/*
 * CF::GYM 100203A
 * Author: EJQ
 */
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;
const int maxn = 10000 + 5 , maxk = 10;
int cnt[1 << maxk][maxn];
int score[maxn] , mask[maxn] , qmask[maxn * maxk] , ans[maxn * maxk];
int n , m , k;
pair<int , int> query[maxn * maxk];
vector<int> v[1 << maxk];

int main()
{
	scanf("%d%d" , &n , &k);
	for (int i = 0 ; i < n ; i++)
	{
		int y , f;
		scanf("%d%d" , &score[i] , &y);
		for (int j = 0 ; j < y ; j++)
		{
			scanf("%d" , &f);
			mask[i] |= (1 << (f - 1));
		}
	}
	scanf("%d" , &m);
	for (int i = 0 ; i < m ; i++)
	{
		int ty , tf;
		scanf("%d%d" , &qmask[i] , &ty);
		for (int j = 0 ; j < ty ; j++)
		{
			scanf("%d" , &tf);
			query[i].first |= ( 1 << (tf - 1));
		}
		query[i].second = i;
	}
	sort(&query[0] , &query[m]);
	int p = m - 1 , id , x , y;
	for (int i = (1 << k) - 1 ; i >= 0 ; i--)
	{
		if ( (~p) && i == query[p].first )
		{
			for (int j = 0 ; j < (1 << k) ; j++)
				v[j].clear() , v[j].push_back(1e9 + 1) , v[j].push_back(0);
			for (int j = 0 ; j < n ; j++)
				v[i & mask[j]].push_back(score[j]);
			for (int j = 0 ; j < (1 << k) ; j++)
				sort(v[j].begin() , v[j].end() , greater<int>());
			while ( (~p) && i == query[p].first )
			{
				id = query[p].second;
				x = ( query[p].first & mask[qmask[id] - 1] );
				y = score[qmask[id] - 1];
				ans[id] = (lower_bound(v[x].begin() , v[x].end() , y , greater<int>()) - v[x].begin());
				p--;
			}
		}
	}
	for (int i = 0 ; i < m ; i++)
		printf("%d\n" , ans[i]);
	return 0;
}
