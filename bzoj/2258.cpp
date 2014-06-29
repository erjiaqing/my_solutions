#include <bits/stdc++.h>
using namespace std;
const int maxn=50500,th=27;
unsigned long long h[maxn],ph[maxn];
char s[maxn],op[5],oop[5];
int pos[maxn],m,len,id[maxn];
unsigned long long get(int x,int l)
{
	return ((h[x+l-1]-h[x-1]*ph[l]));
}
int main()
{
	scanf("%s",s+1);
	len=strlen(s+1);
	ph[0]=1;
	for (int i=1;i<maxn;i++) ph[i]=ph[i-1]*th;
	for (int i=1;i<=len;i++) h[i]=h[i-1]*th+s[i]-'a'+1,pos[id[i]=i]=i;
	int q;
	scanf("%d",&q);
	while (q--)
	{
		scanf("%s",op);
		if (op[0]=='I')
		{
			int p;
			scanf("%s%d",op,&p);
			char c=op[0];
			for (int i=++len;i>p;i--)
			{
				s[i]=s[i-1];
				pos[id[i]=id[i-1]]=i;
			}
			s[p]=c;
			id[p]=0;
			for (int i=p;i<=len;i++) h[i]=h[i-1]*th+s[i]-'a'+1;
		}else
		{
			int x,y;
			scanf("%d%d",&x,&y);
			x=pos[x],y=pos[y];
			int l=-1,r=len-max(x,y)+2;
			while (l+1<r)
			{
				int mid=(l+r)/2;
				if (get(x,mid)==get(y,mid))
				{
					l=mid;
				}else
				{
					r=mid;
				}
			}
			printf("%d\n",l);
		}
	}
	return 0;
}
