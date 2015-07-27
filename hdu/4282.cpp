#include <bits/stdc++.h>
using namespace std;
const int maxx = 65536 + 5;
const int maxz = 32;
vector<pair<int , pair<int , int> > > vp;
typedef vector< pair<int , pair<int , int> > >::iterator it1;
vector<pair<int ,int> > vp2[maxz];
typedef vector< pair<int , int> >::iterator it2;
bool avail[maxx][maxz];
int k;
long long epow(long long x , long long z)
{
	long long ret = 1;
	while (z)
	{
		if (z & 1)
			ret *= x;
		x *= x;
		z >>= 1;
	}
	return ret;
}
int work()
{
	int ans = 0;
	it1 p = upper_bound(vp.begin() , vp.end() , make_pair(k , make_pair(0,0)));
	p--;
	for ( ; p != vp.begin() ; p--)
	{
		int tz = p->second.second;
		int ty = 0;
		int tx = p->second.first;
		int xz = p->second.first * tz;
//		cerr << tz << "\n";
		it2 p2 = upper_bound(vp2[tz].begin() , vp2[tz].end() , make_pair(k - p->first , p->second.first));
		p2--;
		for (int i = 32768 ; i ; i >>= 1)
			if (avail[ty | i][tz] && epow(ty | i , tz) + (ty | i) * xz <= k - p->first)
				ty |= i;
		if (ty > tx && epow(ty , tz) + ty * xz == k - p->first)
		{
			ans++;
//			cerr << p->second.first << " " << ty << " " << tz << endl;
		}
	}
	return ans;
}
int main()
{
	for (long long x = 2 ; x * x <= (1ll << 31) ; x++)
	{
		int z = 2;
		long long tmp;
		while ((tmp = epow(x , z)) <= (1ll << 31))
		{
			vp.push_back(make_pair(tmp , make_pair(x , z)));
			vp2[z].push_back(make_pair(tmp , x));
			avail[x][z] = 1;
			z++;
		}
	}
	for (int tz = 2 ; tz < 32 ; tz++)
	{
		vp.push_back(make_pair(1 , make_pair(1 , tz)));
		vp2[tz].push_back(make_pair(1 , 1));
	}
	sort(vp.begin() , vp.end());
	for (int i = 2 ; i < 32 ; i++)
		sort(vp2[i].begin() , vp2[i].end());
	while (1)
	{
		int ans = 0;
		scanf("%d" , &k);
		if (k == 0) break;
		ans += work();
		printf("%d\n" , ans);
	}
}
