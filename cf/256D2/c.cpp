#include <bits/stdc++.h>
using namespace std;
const int maxn=8200*2,M=8192;
int a[maxn];
int t[maxn];
int n;
int rmq(int l,int r)
{
	int ans=r;
	l=l+M-1,r=r+M+1;
	for (;l^r^1;l>>=1,r>>=1)
	{
		if (~l&1) ans=a[t[l+1]]<a[ans]?t[l+1]:ans;
		if ( r&1) ans=a[t[r-1]]<a[ans]?t[r-1]:ans;
	}
	return ans;
}
int dfs(int l,int r,int b)
{
	if (l>r) return 0;
	int m=rmq(l,r);
	return min(r-l+1,dfs(l,m-1,a[m])+dfs(m+1,r,a[m])+a[m]-b);
}
int main()
{
	memset(a,0x7f,sizeof(a));
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]),t[i+M]=i;
//	for (int i=n+1;i<=M;i++) t[i+M]=n;
	for (int i=M;i>0;i--) t[i]=(a[t[i<<1]]<a[t[i<<1|1]])?t[i<<1]:t[i<<1|1];
	printf("%d\n",dfs(1,n,0));
	return 0;
}
/*
 * Just like NOIp 2013 Day2 Problem 1
 */
