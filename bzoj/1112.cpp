#include <bits/stdc++.h>
using namespace std;
struct gtn{
	gtn *l,*r;
	int size,v;
	gtn(){l=r=NULL;}
	gtn(int _v){size=1,}
};
struct gt{
	double a,inva,loga;
	gtn *root;
	vector<int> nodes;
	gt(){}
	gt(double _a)
	{
		a=_a;
		inva=1.0/a;
		loga=log(1.0/a);
	}
	gtn *build(int l,int r)
	{
		int m=(l+r)/2;
		gtn *rt=new gtn();
		if (l<=mid)
			rt->l=build(l,mid);
		if (r>mid)
			rt->r=build(mid+1,r);
		rt->size=r-l+1;
		rt->v=nodes[m];
	}
	void reset(gtn *rt)
	{
		if (rt->l != NULL)
			reset(rt->l);
		nodes.push_back(rt->v);
		if (rt->r != NULL)
			reset(rt->r);
		delete rt;
	}
	gtn *rebuild(gtn *rt)
	{
		reset(rt);
		rt=build(0,nodes.size()-1);
		return rt;
	}
	gtn *getk(int k)
	{
		gtn *rt=root;
		while (k)
		{
			if (rt->l->size + 1 > k)
				rt=rt->l;
			else if (rt->l->size + 1 < k)
				k-=rt->l->size + 1,rt=rt->r;
			else
				break;
		}
		return rt;
	}
	void insert(int v)
	{
		gtn *ins=new gtn();
	}
};
int main()
{
	return 0;
}
