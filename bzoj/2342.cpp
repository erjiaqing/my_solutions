#include <bits/stdc++.h>
using namespace std;
const int maxn=1000005;
int p[maxn],f[maxn],n,l;
char s[maxn],a[maxn];
int find(int u){return u==f[u]?u:f[u]=find(f[u]);}
int main()
{
	scanf("%d%s",&n,s);
	a[0]='$';
	for (int i=0;i<n;i++) a[++l]='@',a[++l]=s[i];
	a[++l]='~';
	//Manacher
	int q=0,mx=0;
	for (int i=1;i<l;i++)
	{
		f[i]=i+(a[i]!='@');
		p[i]=mx>i?min(p[2*q-i],mx-i):1;
		while (a[i-p[i]]==a[i+p[i]]) p[i]++;
		if (i+p[i]>mx) {q=i;mx=i+p[i];}
	}
	f[n]=n;
	int ans=0;
	for (int i=3;i<l;i+=2)
	{
		int l=max(i-p[i]/2,1),c=find(l);
		while (c<i && c+p[c]-1<i) c=f[c]=find(c+1);
		ans=max(ans,(i-c)*2);
	}
	printf("%d\n",ans);
	return 0;
}
