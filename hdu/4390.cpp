#include <bits/stdc++.h>
using namespace std;
const int L=110,mod=1e9+7,L2=1e6;
long long a[L],inv[L];
int c[L][L];
int c2[L][L];
int p[L2],cnt[L2],pos[L2+10];
long long ans[20 + 5];
bool used[L2+10];
int len=0;
long long qpow(long long x,int y)
{
	long long t=x,re=1;
	while(y)
	{
		if(y&1)re=re*t%mod;
		y>>=1;
		t=t*t%mod;
	}
	return re;
}
void prepare()
{
	c[0][0] = 1;
	c2[0][0] = 1;
	for (int i = 1 ; i < L ; i++)
		c2[0][i] = 1;
	for (int i = 1 ; i < L; i++)
	{
		c[i][0] = 1;
		c2[i][0] = 1;
		for (int j = 1 ; j < L; j++)
		{
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
			c2[i][j] = (c2[i - 1][j] + c2[i][j - 1]) % mod;
		}
	}
	a[0]=1;
	inv[0]=1;
	for(int i=1;i<=100;++i)
	{
		a[i]=a[i-1]*i%mod;
		inv[i]=qpow(a[i],mod-2);
	}
	for(int i=2;i<=L2;++i)
	{
		if(!used[i])
		{
			p[++len]=i;
			pos[i]=len;
		}
		for(int j=1;j<=len;++j)
		{
			if(i*p[j]>L2)break;
			used[i*p[j]]=1;
			if(i%p[j]==0)break;
		}
	}
}
int main()
{
	prepare();
	int n,b,top;
	while(~scanf("%d",&n))
	{
		if(n==1)
		{
			scanf("%d" , &b);
			puts("1");
			continue;
		}
		memset(cnt,0,sizeof(cnt));
		top=0;
		for(int j=1;j<=n;++j)
		{
			scanf("%d",&b);
			for(int i=1;b>1;++i)
			{
				top=max(top,i);
				while(b%p[i]==0)
				{
					b/=p[i];
					++cnt[i];
				}
				if(pos[b])
				{
					top=max(top,pos[b]);
					++cnt[pos[b]];
					b=1;
				}
			}
		}
		ans[0] = 1;
		for (int tn = 1 ; tn <= n ; tn++)
		{
			assert(tn <= 20);
			ans[tn] = 1;
			for(int i=1;i<=top;++i)
			{
				assert(cnt[i] < 100);
				assert(tn >= 1);
				(ans[tn] *= c2[cnt[i]][tn - 1]) %= mod;
			}
			for (int i = 1 ; i < tn ; i++)
				ans[tn] = ((ans[tn] - ans[tn - i] * c[tn][tn - i] % mod) % mod + mod) % mod;
		}
		printf("%lld\n",ans[n]);
	}
}
