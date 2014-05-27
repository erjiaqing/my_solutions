#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=5005,inf=0x7ffffffe;
int lcs[maxn][maxn];
char s1[maxn],s2[maxn];
int maxp1[maxn],maxp2[maxn];
int prep(char *a,char *b)
{
	int la=strlen(a+1),lb=strlen(b+1);
	for (int i=la;i>=1;i--)
		for (int j=lb;j>=1;j--)
			if (a[i]==b[j])
				lcs[i][j]=lcs[i+1][j+1]+1;
			else
				lcs[i][j]=0;
}
int main()
{
	int l1,l2;
	int pl1,pl2;
	scanf("%s%s",s1+1,s2+1);
	l1=strlen(s1+1);l2=strlen(s2+1);
	memset(lcs,0,sizeof(lcs));
	prep(s1,s1);
	for (int i=1;i<=l1;i++)
	{
		pl1=0;
		for (int j=1;j<=l1;j++)
			if (i==j)
				continue;
			else
				pl1=max(pl1,lcs[i][j]);
		maxp1[i]=++pl1;
	}
	memset(lcs,0,sizeof(lcs));
	prep(s2,s2);
	for (int i=1;i<=l2;i++)
	{
		pl2=0;
		for (int j=1;j<=l2;j++)
			if (i==j)
				continue;
			else
				pl2=max(pl2,lcs[i][j]);
		maxp2[i]=++pl2;
	}
	memset(lcs,0,sizeof(lcs));
	prep(s1,s2);
	int ans=inf;
	for (int i=1;i<=l1;i++)
		for (int j=1;j<=l2;j++)
			if (lcs[i][j]>=max(maxp1[i],maxp2[j]))
				ans=min(ans,max(maxp1[i],maxp2[j]));
	printf("%d\n",ans==inf?-1:ans);
	return 0;
}
