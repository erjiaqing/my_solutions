#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=1110005;
const int inf=0x7fffffff;
int l[maxn*4],r[maxn*4];
int size[maxn],fa[maxn],son[maxn][2],val[maxn],root[maxn],stk[maxn],h,node;
int a[maxn],b[maxn],m,n;
int opt,sq,sum,suc,pre,pos;
void pushup(int x)
{
	if (!x)
		return;
	size[x]=size[son[x][0]]+size[son[x][1]]+1;
}
void link(int x,int y,int c)
{
	fa[x]=y;son[y][c]=x;
}
void rotate(int x,int c)
{
	int y=fa[x];
	link(x,fa[y],son[fa[y]][1]==y);
	link(son[x][!c],y,c);
	link(y,x,!c);
	pushup(y);
}
void splay(int x,int g,int &rt)
{
//	printf("[SPLAY] %d %d %d\n",x,g,rt);
	while (fa[x]!=g)
	{
		int y=fa[x];
		int cy=(son[fa[y]][1]==y),cx=(son[y][1]==x);
//		printf("[SPLAY][WHILE] %d %d %d %d\n",x,cx,y,cy);
		if (fa[y]==g)
			rotate(x,cx);
		else
		{
			if (cx==cy)
				rotate(y,cy);
			else
				rotate(x,cx);
			rotate(x,cy);
		}
	}
	pushup(x);
	if (!g)
		rt=x;
//	printf("[SPLAY] FI\n");
}
int getnum()
{
	if (h)
		return stk[h--];
	else
		return ++node;
}
void newnode(int y,int &x,int sp)
{
	x=getnum();
	son[x][0]=son[x][1]=0;
	fa[x]=y;val[x]=sp;size[x]=1;
}
void pack(int &u,int l,int r,int f)
{
	if (r<l)
		return;
	int mid=(l+r)/2;
	newnode(f,u,a[mid]);
	pack(son[u][0],l,mid-1,u);
	pack(son[u][1],mid+1,r,u);
	pushup(u);
}
void bsplay(int u,int l,int r)
{
	newnode(0,root[u],-inf);
	newnode(root[u],son[root[u]][1],inf);
	size[root[u]]=2;
	pack(son[son[root[u]][1]][0],l,r,son[root[u]][1]);
	pushup(son[son[root[u]][1]][0]);
	pushup(son[root[u]][1]);
}
void build(int u,int l,int r)
{
//	printf("[BUILD] %d %d %d\n",u,l,r);
	::l[u]=l;::r[u]=r;
	if (l==r)
	{
		bsplay(u,l,r);
		return;
	}
	int mid=(l+r)/2;
	build(u*2,l,mid);
	build(u*2+1,mid+1,r);
	sort(&a[l],&a[r+1]);
	bsplay(u,l,r);
}
int getmin(int x)
{
	while (son[x][0])
		x=son[x][0];
	return x;
}
int Find(int sp,int x)
{
	while (x)
	{
		if (val[x]==sp)
			return x;
		x=son[x][val[x]<sp];
	}
}
int getmax(int x)
{
	while (son[x][1])
		x=son[x][1];
	return x;
}
void insert(int sp,int &rt)
{
	int x=rt;
//	printf("[INSERT] %d %d\n",sp,rt);
	while (son[x][val[x]<sp])
		x=son[x][val[x]<sp];
	newnode(x,son[x][val[x]<sp],sp);
	splay(son[x][val[x]<sp],0,rt);
}
void del(int sp,int &rt)
{
//	printf("[DELETE] %d %d\n",sp,rt);
	int x=Find(sp,rt);
	splay(x,0,rt);
	int y=getmax(son[x][0]),z=getmin(son[x][1]);
//	printf("[DELETE][INFO] %d{%d} %d{%d}\n",y,fa[y],z,fa[z]);
	splay(y,0,rt);splay(z,y,rt);
	stk[++h]=son[z][0];son[z][0]=0;
	pushup(z);pushup(y);
}
int pred(int x,int sp)
{
	int re=-inf;
	while (x)
	{
		if (val[x]<sp)
			re=max(val[x],re);
		x=son[x][val[x]<sp];
	}
	return re;
}
int succ(int x,int sp)
{
	int re=inf;
	while (x)
	{
		if (val[x]>sp)
			re=min(val[x],re);
		x=son[x][val[x]<=sp];
	}
	return re;
}
void query(int u,int l,int r)
{
//	printf("[QUERY] %d %d %d %d\n",u,l,r,sq);
	if (::l[u]>=l && ::r[u]<=r)
	{
		if (opt==1)
		{
			insert(sq,root[u]);
			sum+=size[son[root[u]][0]]-1;
			del(sq,root[u]);
		}else if (opt==3)
		{
			del(b[pos],root[u]);
			insert(sq,root[u]);
		}else if (opt==4)
		{
			pre=max(pre,pred(root[u],sq));
		}else if (opt==5)
		{
			suc=min(suc,succ(root[u],sq));
		}
		return;
	}
	int mid=(::l[u]+::r[u])/2;
	if (r<=mid)
	{
//		cerr<<"Query L\n";
		query(u*2,l,r);
	}else if (l>mid)
	{
//		cerr<<"Query R\n";
		query(u*2+1,l,r);
	}else
	{
//		cerr<<"Query Next\n";
		query(u*2,l,mid);
		query(u*2+1,mid+1,r);
	}
//	printf("[QUERY-FI] %d %d %d\n",u,l,r);
	if (opt==3)
	{
		del(b[pos],root[u]);
		insert(sq,root[u]);
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	build(1,1,n);
//	cerr<<"[FI] BUILD\n";
	int aa,bb,k;
	for (int i=1;i<=m;i++)
	{
		scanf("%d",&opt);
		if (opt==1)
		{
			scanf("%d%d%d",&aa,&bb,&sq);
			sum=0;
			query(1,aa,bb);
			printf("%d\n",sum+1);
		}else if (opt==2)
		{
			scanf("%d%d%d",&aa,&bb,&k);
			opt=1;
			int l=0,r=inf,ans;
			while (l<=r)
			{
				int mid=(l+r)/2;
				sum=0;
				sq=mid;query(1,aa,bb);
				if (sum+1<=k)
					ans=mid,l=mid+1;
				else
					r=mid-1;
			}
			printf("%d\n",ans);
		}else if (opt==3)
		{
			scanf("%d%d",&pos,&sq);
			query(1,pos,pos);
			b[pos]=sq;
		}else if (opt==4)
		{
			scanf("%d%d%d",&aa,&bb,&sq);
			pre=-inf;
			query(1,aa,bb);
			printf("%d\n",pre);
		}else
		{
			scanf("%d%d%d",&aa,&bb,&sq);
			suc=inf;
			query(1,aa,bb);
			printf("%d\n",suc);
		}
//		printf("[FI] Single Query\n");
	}
	return 0;
}
