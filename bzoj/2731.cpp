#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=10005,maxw=2000000;
struct Link{
	int v,l,r;
	Link(){}
	Link(int _v,int _l,int _r):
		v(_v),l(_l),r(_r){}
}a[maxn];
bool cmp(Link a,Link b)
{
	return a.v<b.v;
}
int n,d,x,q,i,j,l[maxn],r[maxn],tl,w[20000005],tot,la,tmp;
double ans;
bool fi;
int tx,ty,td;
int main()
{
	scanf("%d",&n);
	for (i=1;i<=n;i++)
	{
		scanf("%d%d%d",&tx,&ty,&td);
		a[i]=Link(ty,tx+1,tx+td);
	}
	sort(&a[1],&a[n+1],cmp);
	for (int h=0,q=1;h<=2000000;h++,la=tot)
	{
		for (j=r[0];j;j=r[j])
		{
			i=a[j].r--;
			if (a[j].r<a[j].l)
			{
				tl=(j==tl)?l[j]:tl,
				r[l[j]]=r[j],
				l[r[j]]=l[j],
				tmp=l[j],
				l[j]=r[j]=0,
				j=tmp;
			}
			if ((--w[i])==0)
				tot--;
		}
		ans+=la+tot;
		while (q<=n && a[q].v==h)
		{
			if (a[q].l>a[q].r)
			{
				q++;
				continue;
			}
			for (j=r[0],fi=false;j&&!fi;j=r[j])
			{
				if (a[j].l<=a[q].l && a[j].r>=a[q].r)
					fi=true;
			}
			if (fi)
			{
				q++;
				continue;
			}
			r[tl]=q;l[q]=tl;tl=q;
			for (j=a[q].l;j<=a[q].r;j++)
				if ((w[j]++)==0)
					tot++;
			q++;
		}
	}
	printf("%.2lf\n",ans/2);
	return 0;
}
