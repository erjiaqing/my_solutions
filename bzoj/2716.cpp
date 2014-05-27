#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

//#define abs(x) (((x)<0)?(-(x)):(x))

using namespace std;
const int maxn=2000005,inf=0x7f7f7f7f;
int n,m,q,x,y,ans,root,cmp_d;
struct kdnode{
	int l,r,d[2],Max[2],Min[2];
}T[maxn];
int abs(int x)
{
	return (x<0)?(-x):(x);
}
void update(int p)
{
	if (T[p].l)
	{
		if (T[p].Max[0]<T[T[p].l].Max[0]) T[p].Max[0]=T[T[p].l].Max[0];
		if (T[p].Min[0]>T[T[p].l].Min[0]) T[p].Min[0]=T[T[p].l].Min[0];
		if (T[p].Max[1]<T[T[p].l].Max[1]) T[p].Max[1]=T[T[p].l].Max[1];
		if (T[p].Min[1]>T[T[p].l].Min[1]) T[p].Min[1]=T[T[p].l].Min[1];
	}
	if (T[p].r)
	{
		if (T[p].Max[0]<T[T[p].r].Max[0]) T[p].Max[0]=T[T[p].r].Max[0];
		if (T[p].Min[0]>T[T[p].r].Min[0]) T[p].Min[0]=T[T[p].r].Min[0];
		if (T[p].Max[1]<T[T[p].r].Max[1]) T[p].Max[1]=T[T[p].r].Max[1];
		if (T[p].Min[1]>T[T[p].r].Min[1]) T[p].Min[1]=T[T[p].r].Min[1];
	}
}
bool comp(kdnode a,kdnode b)
{
	return ((a.d[cmp_d] < b.d[cmp_d])||((a.d[cmp_d] == b.d[cmp_d])&&(a.d[!cmp_d] < b.d[!cmp_d])));
}
void insert(int fuck)  //What ths f**k!!!
{
	int D,p;
	D=0;p=root;
	while (1)
	{
		if (T[fuck].Max[0]>T[p].Max[0]) T[p].Max[0]=T[fuck].Max[0];
		if (T[fuck].Max[1]>T[p].Max[1]) T[p].Max[1]=T[fuck].Max[1];
		if (T[fuck].Min[0]<T[p].Min[0]) T[p].Min[0]=T[fuck].Min[0];
		if (T[fuck].Min[1]<T[p].Min[1]) T[p].Min[1]=T[fuck].Min[1];
		if (T[fuck].d[D]>=T[p].d[D])
		{
			if (T[p].r==0)
			{
				T[p].r=fuck;
				return;
			}else
			{
				p=T[p].r;
			}
		}else
		{
			if (T[p].l==0)
			{
				T[p].l=fuck;
				return;
			}else
			{
				p=T[p].l;
			}
		}
		D=!D;
	}
}
int build(int l,int r,int D)
{
	int mid=(l+r)/2;
	cmp_d=D;
	nth_element(&T[l+1],&T[mid+1],&T[r+1],comp);
	T[mid].Max[0]=T[mid].Min[0]=T[mid].d[0];
	T[mid].Max[1]=T[mid].Min[1]=T[mid].d[1];
	if (l!=mid) T[mid].l=build(l,mid-1,!D);
	if (r!=mid) T[mid].r=build(mid+1,r,!D);
	update(mid);
	return mid;
}
int dist(int q,int px,int py)
{
	int ret=0;
	if (px<T[q].Min[0]) ret+=T[q].Min[0]-px;
	if (px>T[q].Max[0]) ret+=px-T[q].Max[0];
	if (py<T[q].Min[1]) ret+=T[q].Min[1]-py;
	if (py>T[q].Max[1]) ret+=py-T[q].Max[1];
	return ret;
}
void query(int q)
{
	int dl,dr,d0;
	d0=abs(T[q].d[0]-x)+abs(T[q].d[1]-y);
	if (d0<ans) ans=d0;
	if (T[q].l) dl=dist(T[q].l,x,y); else dl=inf;
	if (T[q].r) dr=dist(T[q].r,x,y); else dr=inf;
	if (dl<dr)
	{
		if (dl<ans) query(T[q].l);
		if (dr<ans) query(T[q].r);
	}else
	{
		if (dr<ans) query(T[q].r);
		if (dl<ans) query(T[q].l);
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%d%d",&T[i].d[0],&T[i].d[1]);
	root=build(1,n,0);
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&q,&x,&y);
		if (q==1)
		{
			n++;
			T[n].Max[0]=T[n].Min[0]=T[n].d[0]=x;
			T[n].Max[1]=T[n].Min[1]=T[n].d[1]=y;
			insert(n);
		}else
		{
			ans=inf;
			query(root);
			printf("%d\n",ans);
		}
	}
	return 0;
}
