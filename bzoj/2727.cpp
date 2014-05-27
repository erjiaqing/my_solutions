#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn=2000005;
const long long mod=1000000009;
long long bit1[maxn],bit2[maxn],bit3[maxn],ans=0;
int queue[maxn],l[maxn],r[maxn],d[maxn],c[maxn],zero[maxn];
int n,m;
int top,rear;
/*
 * 讨论一下
 * 对于一个点(i,j)
 * 它能向下拓展d[i],向做拓展l[i],向右拓展r[i]
 * 那么就有两行
 * 设c[i]=min(l[i],r[i])
 * 答案应该就是(Sigma(c[j]-{1->c[i]}))
 */
inline int getpos(int x,int y)
{
	return (x-1)*m+y;
}
inline int lowbit(int x)
{
	return x&(-x);
}
inline void bitadd(long long bit[],int n,long long k)
{
	for (int i=n;i<=m;i+=lowbit(i))
		(bit[i]+=k)%=mod;
}
inline long long get(long long bit[],int k)
{
	long long ret=0;
	for (int i=k;i;i-=lowbit(i))
		(ret+=bit[i])%=mod;
	return ret;
}
void preworks()
{
	for (int i=1;i<=n;i++)
	{
		l[getpos(i,1)]=zero[getpos(i,1)]?-1:0;
		r[getpos(i,m)]=zero[getpos(i,m)]?-1:0;
		for (int j=2;j<=m;j++)
		{
			if (zero[getpos(i,j)])
				l[getpos(i,j)]=-1;
			else
				l[getpos(i,j)]=l[getpos(i,j-1)]+1;
		}
		for (int j=m-1;j;j--)
		{
			if (zero[getpos(i,j)])
				r[getpos(i,j)]=-1;
			else
				r[getpos(i,j)]=r[getpos(i,j+1)]+1;
			c[getpos(i,j)]=min(l[getpos(i,j)],r[getpos(i,j)]);
		}
	}
	for (int j=1;j<=m;j++)
	{
		d[getpos(n,j)]=zero[getpos(n,j)]?-1:0;
		for (int i=n-1;i>=1;i--)
		{
			if (zero[getpos(i,j)])
				d[getpos(i,j)]=-1;
			else
				d[getpos(i,j)]=d[getpos(i+1,j)]+1;
		}
	}
}
void clear()
{
	top=rear=0;
	for (int i=1;i<=m;i++)
		bit1[i]=bit2[i]=bit3[i]=0;
}
void work()
{
	long long last=0;
	for (int j=1;j<=m;j++)
	{
		clear();
		for (int i=1;i<=n;i++)
		{
			int p=getpos(i,j);
			if (zero[p])
				clear();
			else if (top==0)
				top=i;
			else if (c[p]!=0)
			{
				long long sum1=get(bit1,c[p])*c[p]%mod,
					      sum2=get(bit2,c[p]),
						  sum3=c[p]*(c[p]-1)/2%mod*(get(bit3,m)-get(bit3,c[p]))%mod;
				last=(sum1-sum2+sum3+mod)%mod;
				(ans+=last*d[p])%=mod;
				if (queue[rear]==getpos(i-1,j))
				{
					int p=queue[rear],h=(p-1)/m+1;
					bitadd(bit1,c[p],c[p]*(h-top)%mod);
					bitadd(bit2,c[p],c[p]*(c[p]+1)/2%mod*(h-top)%mod);
					bitadd(bit3,c[p],h-top);
				}
				queue[++rear]=p;
				continue;
			}
			if (rear && queue[rear]==getpos(i-1,j))
			{
				int p=queue[rear],h=(p-1)/m+1;
				bitadd(bit1,c[p],c[p]*(h-top)%mod);
				bitadd(bit2,c[p],c[p]*(c[p]+1)/2%mod*(h-top)%mod);
				bitadd(bit3,c[p],h-top);
			}
		}
	}
	printf("%lld\n",ans);
}
int main()
{
	int tot;
	scanf("%d%d%d",&n,&m,&tot);
	for (int i=1,a,b;i<=tot;i++)
	{
		scanf("%d%d",&a,&b);
		zero[getpos(a,b)]=true;
	}
	preworks();
	work();
	return 0;
}
