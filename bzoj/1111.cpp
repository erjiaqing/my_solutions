#include <bits/stdc++.h>
using namespace std;
const int maxn=10005,mod=1000000000;
char n[maxn];
int N[maxn],l,F[maxn],nf;
int f[maxn][2],g[maxn][2];
int Div()
{
	int m=0;
	for (int i=l-1;i>=0;i--)
	{
		(m*=10)+=N[i];
		N[i]=m/4;m%=4;
	}
	return m;
}
void process()
{
	while (l)
	{
		F[nf++]=Div();
		while (l && !N[l-1]) l--;
	}
}
int main()
{
//	int p=0;
	scanf("%s",n);
	l=strlen(n);
	reverse(&n[0],&n[l]);
	for (int i=0;i<l;i++) N[i]=n[i]-'0';
	process();
	g[nf][0]=g[nf][1]=f[nf][1]=1;
	for (int i=nf-1;i>=0;i--)
	{
//		p=i&1;
		for (int j=0;j<2;j++)
		{
			f[i][j]=min(f[i+1][0]+F[i]+j,f[i+1][1]+4-F[i]-j);
			if (f[i][j]==f[i+1][0]+F[i]+j)
				g[i][j]+=g[i+1][0];
			g[i][j]%=mod;
			if (f[i][j]==f[i+1][1]+4-F[i]-j)
				g[i][j]+=g[i+1][1];
			g[i][j]%=mod;
		}
	}
	printf("%d\n",g[0][0]);
	return 0;
}

