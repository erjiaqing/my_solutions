#include <bits/stdc++.h>
using namespace std;
const int maxn=100010;
long long c[maxn];
int fx[maxn],fy[maxn],tot[maxn];
int pos[maxn],n,s,q,p,m,d,k;
bool use[maxn];
int gcd(int a,int b){return a%b?gcd(b,a%b):b;}
int get(int p,int *f){return f[p]==p?p:f[p]=get(f[p],f);}
void del(int p)
{
	int pos=get(p%k,fx);
	fy[p]=get((p+d)%n,fy),tot[pos]--;
	if (tot[pos]==0) fx[pos]=get((pos+1)%k,fx);
}
void calc()
{
	for (int i=0;i<k;i++)
		fx[i]=i,tot[i]=n/k;
	for (int i=0;i<n;i++)
		fy[i]=i;
	pos[0]=s;del(s);
	for (int i=1;i<n;i++)
	{
		int a=c[i]%n%k,x,y;
		if (tot[a]==0) x=get(a,fx),y=get((c[i]+(x+k-a)%k)%n,fy);
		else y=get(c[i]%n,fy);
		pos[i]=y;del(y);
	}
}
int work()
{
	for (int i=0;i<n;i++) use[i]=false;
	int cnt=0;
	for (int i=0;i<n;i++)
	{
		if (use[i]==false && pos[i]!=i)
		{
			use[i]=true;cnt+=2;
			for (int j=pos[i];j!=i;j=pos[j])
				use[j]=true,cnt++;
		}
	}
	return cnt-2;
}
int main()
{
	int test;
	for (scanf("%d",&test);test>=1;test--)
	{
		scanf("%d%d%d%d%d%d",&n,&s,&q,&p,&m,&d);
		c[0]=0,k=gcd(n,d);
		for (int i=1;i<n;i++)
			c[i]=(c[i-1]*q+p)%m;
		calc();
		printf("%d\n",work());
	}
	return 0;
}
