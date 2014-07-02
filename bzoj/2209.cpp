#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
struct node{
	node *s[2],*f;
	int lmin,lmax,rmin,rmax;
	int val,sum,sz;
	int fo1,fo2;
	void op2()
	{
		fo2^=1;
		swap(lmin,rmin),swap(lmax,rmax),swap(s[0],s[1]);
	}
	void op1()
	{
		fo1^=1;
		val=-val;sum=-sum;
		lmin=-lmin,lmax=-lmax,rmin=-rmin,rmax=-rmax;
		swap(lmin,lmax),swap(rmin,rmax);
	}
}*root,pool[maxn],*nullnode;int cnt;
bool good(node *p)
{
	return p!=nullnode && (p!=&pool[1]) && (p!=&pool[2]);
}
void push_up(node *p)
{
	if (p==nullnode) return;
	p->sz=p->s[0]->sz+p->s[1]->sz+1;
	p->sum=p->s[0]->sum+p->s[1]->sum+p->val;

	p->lmin=p->s[0]->lmin;
	p->lmin=min(p->lmin,p->s[0]->sum+p->val);
	p->lmin=min(p->lmin,p->s[0]->sum+p->val+p->s[1]->lmin);
	
	p->lmax=p->s[0]->lmax;
	p->lmax=max(p->lmax,p->s[0]->sum+p->val);
	p->lmax=max(p->lmax,p->s[0]->sum+p->val+p->s[1]->lmax);
	
	p->rmin=p->s[1]->rmin;
	p->rmin=min(p->rmin,p->s[1]->sum+p->val);
	p->rmin=min(p->rmin,p->s[1]->sum+p->val+p->s[0]->rmin);
	
	p->rmax=p->s[1]->rmax;
	p->rmax=max(p->rmax,p->s[1]->sum+p->val);
	p->rmax=max(p->rmax,p->s[1]->sum+p->val+p->s[0]->rmax);
}
void push_down(node *p)
{
	if (p==nullnode) return;
	if (p->fo1)
	{
		if (good(p->s[0])) p->s[0]->op1();
		if (good(p->s[1])) p->s[1]->op1();
		p->fo1=0;
	}
	if (p->fo2)
	{
		if (good(p->s[0])) p->s[0]->op2();
		if (good(p->s[1])) p->s[1]->op2();
		p->fo2=0;
	}
}
node *newnode(int val,node *f)
{
	node *ret=&pool[cnt++];
	ret->s[0]=ret->s[1]=nullnode;
	ret->f=f;
	ret->fo1=ret->fo2=0;
	ret->sz=1;
	ret->sum=ret->val=ret->lmin=ret->lmax=ret->rmin=ret->rmax=val;
	return ret;
}
void init()
{
	nullnode=NULL;
	nullnode=newnode(0,NULL);
	nullnode->sz=0;
	nullnode->lmin=nullnode->rmin=1e6;
	nullnode->lmax=nullnode->rmax=-1e6;
	nullnode->sum=0;
	root=newnode(0,nullnode);
	root->lmin=root->rmin=1e6;
	root->lmax=root->rmax=-1e6;
	root->sum=0;
	root->s[1]=newnode(0,root);
	root->s[1]->lmin=root->s[1]->rmin=1e6;
	root->s[1]->lmax=root->s[1]->rmax=-1e6;
	root->s[1]->sum=0;
	push_up(root);
}
//--
void rotate(node *p,node *x)
{
	int cx=(p==x->s[1]);
	node *y=p->s[cx^1],*z=x->f;
	if (y!=nullnode) y->f=x;
	if (x==z->s[0]) z->s[0]=p;
	if (x==z->s[1]) z->s[1]=p;
	p->s[cx^1]=x;p->f=z;x->s[cx]=y;x->f=p;
	push_up(x);
}
void splay(node *p,node *k)
{
	push_down(p);
	while (p->f!=k)
	{
		node *x=p->f,*y=x->f;
		push_down(y);push_down(x);push_down(p);
		if (y==k)
			rotate(p,x);
		else if ((p==x->s[0])^(x==y->s[0]))
			rotate(p,x),rotate(p,y);
		else
			rotate(x,y),rotate(p,x);
	}
	push_up(p);
	if (k==nullnode) root=p;
}
//--
void select(int rk,node *f)
{
	node *p=root;
	push_down(p);
	while (p->s[0]->sz+1 != rk)
	{
		if (p->s[0]->sz < rk)
		{
			rk-=p->s[0]->sz+1;
			p=p->s[1];
		}else
		{
			p=p->s[0];
		}
		push_down(p);
	}
	splay(p,f);
}
int val[maxn];
node *build(int l,int r,node *p)
{
	if (l>r) return nullnode;
	int mid=(l+r)/2;
	node *ret=newnode(val[mid],p);
	ret->s[0]=build(l,mid-1,ret);
	ret->s[1]=build(mid+1,r,ret);
	push_up(ret);
	return ret;
}
void insert(int p,int n)
{
	select(p+1,nullnode);
	select(p+2,root);
	node *r=build(1,n,root->s[1]);
	root->s[1]->s[0]=r;
	splay(r,nullnode);
}
void op1(int l,int r)
{
	select(l,nullnode),select(r+2,root);
	root->s[1]->s[0]->op1();
}
void op2(int l,int r)
{
	select(l,nullnode),select(r+2,root);
	root->s[1]->s[0]->op2();
}
int query(int l,int r)
{
	select(l,nullnode),select(r+2,root);
	return	-(root->s[1]->s[0]->lmin-1)/2
			+(root->s[1]->s[0]->rmax+1)/2;
}
int n,m;
char str[maxn];
int main()
{
	init();
	scanf("%d%d",&n,&m);
	scanf("%s",str+1);
	for (int i=1;i<=n;i++) val[i]=(str[i]=='('?1:-1);
	insert(0,n);
	int op,x,y;
	while (m--)
	{
		scanf("%d%d%d",&op,&x,&y);
		if (op==0) printf("%d\n",query(x,y));
		else if (op==1) op1(x,y);
		else if (op==2) op2(x,y);
	}
	return 0;
}
