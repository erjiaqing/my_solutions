#include <bits/stdc++.h>
using namespace std;
long long n,m,k;
long long cut(long long x,long long y)
{
//	if (y==0)
//		return x;
	return x/(y+1);
}
long long tri()
{
	long long l,r,tl,tr;
	l=max(0ll,k-(m-1));r=min(n-1,k);
	return max(cut(n,l)*cut(m,k-l),cut(n,r)*cut(m,k-r));
}
int main()
{
	cin>>n>>m>>k;
	if ((n-1)+(m-1) < k)
	{
		printf("-1\n");
		return 0;
	}
	cout<<tri()<<endl;
	return 0;
}
