#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=55,mod=1e7+7;
int a[maxn],f[2][maxn][maxn];
int bit=0;
int work(int less,int dep,int sum)
{
	if (!dep)
		return sum?sum:1;
	if (f[less][dep][sum])
		return f[less][dep][sum];
	f[less][dep][sum]=1;
	int ed=less?1:a[dep];
	for (int i=0;i<=ed;i++)
		f[less][dep][sum]=(long long)(f[less][dep][sum])*work(less||i<a[dep],dep-1,sum+i)%mod;
	return f[less][dep][sum];
}
int main()
{
	long long n;
	cin>>n;
	while (n)
	{
		a[++bit]=n&1;
		n>>=1;
	}
	cout<<work(0,bit,0)<<endl;
	return 0;
}
