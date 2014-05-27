#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
const long long mod=1000000007,hash_mod=50009;
int a[20],t[20],n;
int delta[]={0,1,3};
vector<pair<long long,long long> >hash_map[12][hash_mod];
vector<pair<long long,long long> >::iterator lli;
long long hash_find(int lay,int has,long long val)
{
	for (lli=hash_map[lay][has].begin();lli!=hash_map[lay][has].end();lli++)
		if (lli->first==val)
			return lli->second;
	return -1;
}
long long hash_insert(int lay,int has,long long val,long long val2)
{
	hash_map[lay][has].push_back(make_pair(val,val2));
	return val2;
}
long long hash(int beg)
{
	for (int i=beg;i<=n;i++)
		t[i]=a[i];
	sort(&t[beg],&t[n]);
	long long ret=0;
	for (int i=beg;i<=n;i++)
		((ret*=30)+=t[i]);
	return ret;
}
long long dfs(int lay1,int lay2)
{
	if (lay1==n)
		return (a[lay1]==0);
	if (lay2==n)
	{
		if (a[lay1])
			return 0;
		long long has=hash(lay1);
		long long k=hash_find(lay1,has%hash_mod,has);
		if (~k)
			return k;
		else
			return hash_insert(lay1+1,has%hash_mod,has,dfs(lay1+1,lay1+2));
	}
	long long ret=0;
	for (int i=0;i<3;i++)
		if (a[lay1]>=delta[i] && a[lay2]>=delta[2-i])
		{
			a[lay1]-=delta[i];a[lay2]-=delta[2-i];
			(ret+=dfs(lay1,lay2+1))%=mod;
			a[lay1]+=delta[i];a[lay2]+=delta[2-i];
		}
	return ret;
}
int main()
{
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf("%d",&a[i]);
	sort(&a[0],&a[n]);
	printf("%lld\n",dfs(0,1));
	return 0;
}
