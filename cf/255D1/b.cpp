#include <bits/stdc++.h>
using namespace std;
const int maxn=1005,maxk=1000005;
long long a[maxk],b[maxk];
long long r[maxn],c[maxn];
priority_queue<long long> pr,pc;
int mat,m,n,k;
long long p;
int main()
{
	scanf("%d%d%d%lld",&n,&m,&k,&p);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			scanf("%d",&mat),r[i]+=mat,c[j]+=mat;
	for (int i=1;i<=n;i++)
		pr.push(r[i]);
	for (int i=1;i<=m;i++)
		pc.push(c[i]);
	for (int i=1;i<=k;i++)
	{
		long long q1,q2;
		q1=pr.top();pr.pop();a[i]=a[i-1]+q1;pr.push(q1-p*m);
		q2=pc.top();pc.pop();b[i]=b[i-1]+q2;pc.push(q2-p*n);
	}
	long long ans=0x8000000000000000ll;
	for (int i=0;i<=k;i++)
		ans=max(ans,a[i]+b[k-i]-((long long)(k-i))*i*p);
	printf("%lld\n",ans);
	return 0;
}
