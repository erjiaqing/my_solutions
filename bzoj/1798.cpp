#include <bits/stdc++.h>
using namespace std;
const int maxn=400005;
long long p;
long long seg[maxn],val[maxn],m1[maxn],m2[maxn];
int sz[maxn];
int n;
#define ls(x) ((x)<<1)
#define rs(x) ((x)<<1|1)
void build(int x,int l,int r)
{
	if (l==r)
		return void(seg[x]=val[l],sz[x]=1);
	int mid=(l+r)/2;
	build(ls(x),l,mid);
	build(rs(x),mid+1,r);
	seg[x]=seg[ls(x)]+seg[rs(x)];
	sz[x]=sz[ls(x)]+sz[rs(x)];
}
int main()
{
	ios::sync_with_stdio(0);
	cin>>n>>p;
	for (int i=1;i<=n;i++) cin>>val[i];
	return 0;
}
