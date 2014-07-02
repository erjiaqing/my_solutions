#include <bits/stdc++.h>
using namespace std;
const int maxn=605,maxm=9005;
struct Point
{
	int x,y;
	Point(){}
	Point(const Point &_p):x(_p.x),y(_p.y){}
	Point(const int &_x,const int &_y):x(_x),y(_y){}
	void Read(){scanf("%d%d",&x,&y);}
	friend bool operator < (const Point &a,const Point &b)
	{return (a.x<b.x)||(a.x==b.x && a.y<b.y);}
	friend bool operator ==(const Point &a,const Point &b)
	{return a.x==b.x && a.y==b.y;}
	friend bool operator !=(const Point &a,const Point &b)
	{return a.x!=b.x || a.y!=b.y;}
	friend Point operator + (const Point &a,const Point &b)
	{return Point(a.x+b.x,a.y+b.y);}
	friend Point operator - (const Point &a,const Point &b)
	{return Point(a.x-b.x,a.y-b.y);}
	friend long long operator * (const Point &a,const Point &b)
	{return a.x*b.y-a.y*b.x;}
	friend long long operator / (const Point &a,const Point &b)
	{return a.x*b.x+a.y*b.y;}
}Center[maxn];
map<Point,int> hash1;
typedef Point Vector;
struct Line
{
	Point a,b;
	Vector v;
	double rad;
	Line(){}
	Line(const Point &_a,const Point &_b):
		a(_a),b(_b)
	{
		v=b-a;
		rad=atan2(v.y,v.x);
	}
	friend bool operator < (const Line &_a,const Line &_b)
	{return (_a.a<_b.a)||(_a.a==_b.a && _a.b<_b.b);}
	friend bool operator != (const Line &_a,const Line &_b)
	{return (_a.a!=_b.a || _a.b!=_b.b);}
	friend bool operator == (const Line &_a,const Line &_b)
	{return (_a.a==_b.a && _a.b==_b.b);}
}L[maxm];
int tot=1;
bool comp(const Line &a,const Line &b){return a.rad<b.rad;}
map<Line,int> hash2;
vector<Line> P[maxm];
vector<int> ans[maxn];
bool across(const Line &a,const Line &b)
{return ((a.b-a.a)*(b.a-a.a))*((a.b-a.a)*(b.b-a.a))<=0 && ((b.b-b.a)*(a.a-b.a))*((b.b-b.a)*(a.b-b.a))<=0;}
struct Poly
{
	vector<Point> P;
	vector<int> edg;
	int area,num;
	friend bool operator < (const Poly &a,const Poly &b)
	{return a.area<b.area;}
	void Work()
	{
		edg.clear();
		for (int i=0;i<P.size()-1;i++)
			edg.push_back(hash2[Line(P[i],P[i+1])]);
		edg.push_back(hash2[Line(P[P.size()-1],P[0])]);
	}
	void Area()
	{
		area=0;
		for (int i=1;i<P.size()-1;i++)
			area-=(P[i]-P[0])*(P[i+1]-P[0]);
	}
	bool Chk(const Point &p)
	{
		bool ret=0;
		Line ejq=Line(Point(-100001,p.y),p);
		for (int i=0;i<P.size();i++)
		{
			Line now(P[i],P[(i+1)%P.size()]);
			if (p.y != min(now.a.y,now.b.y))
				if (across(now,ejq))
					ret^=1;
		}
		return ret;
	}
}Area[maxn];
int n,m;
bool use[maxm];
int pos[maxm],father[maxn];
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) Center[i].Read();
	Point a,b;int k=0,x,y;
	for (int i=1;i<=m;i++)
	{
		a.Read();b.Read();
		if (!hash1.count(a)) hash1[a]=++k;
		if (!hash1.count(b)) hash1[b]=++k;
		x=hash1[a];y=hash1[b];
		L[++tot]=Line(a,b);hash2[L[tot]]=tot;P[x].push_back(L[tot]);
		L[++tot]=Line(b,a);hash2[L[tot]]=tot;P[y].push_back(L[tot]);
	}
	for (int i=1;i<=k;i++)
	{
		sort(P[i].begin(),P[i].end(),comp);
		for (int j=0;j<P[i].size();j++)
			pos[hash2[P[i][j]]]=j;
	}
	Poly country;
	Line L1,L2;
	int s=0;
	for (int i=2;i<=tot;i++)
	{
		if (!use[i])
		{
			use[i]=true;
			L1=L[i];L2=Line(L[i].b,L[i].a);
			country.P.clear();
			country.P.push_back(L1.a);
			while (1)
			{
				int nxt=hash1[L2.a],k=hash2[L2];
				L1=P[nxt][(pos[k]+1)%P[nxt].size()];
				L2=Line(L1.b,L1.a);
				if (L1==L[i]) break;
				country.P.push_back(L1.a),use[hash2[L1]]=true;
			}
			country.Area();
			if (country.area>0) Area[++s]=country;
		}
	}
	for (int i=1;i<=s;i++)
		Area[i].Work();
	sort(&Area[1],&Area[n+1]);
//	for (int i=1;i<=n;i++)
//	{
//		for (int j=0;j<Area[i].P.size();j++)
//			printf("(%d,%d),",Area[i].P[j].x,Area[i].P[j].y);
//		printf("\n");
//	}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			if (Area[j].Chk(Center[i]))
			{
				Area[j].num=i;
//				cerr<<i<<"<-"<<j<<endl;
				break;
			}
	memset(pos,0,sizeof(pos));
	memset(father,0,sizeof(father));
	for (int i=1;i<=n;i++)
		for (int j=0;j<Area[i].P.size();j++)
			pos[Area[i].edg[j]]=i;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
		{
			if (j!=i)
			{
				bool flag=false;
				int x=Area[i].num,y=Area[j].num;
				for (int k=0;k<Area[i].P.size() && !flag ; k++)
					if (pos[Area[i].edg[k]^1]==j)
						flag=true,ans[x].push_back(y);
				if (!flag && !father[y])
				{
					bool flag2=0;
					for (int k=0;k<Area[j].P.size() && !flag2;k++)
						if (pos[Area[j].edg[k]^1]==0)
							flag2=true;
					if (flag2 && Area[i].Chk(Center[Area[j].num]))
						father[y]=x,ans[x].push_back(y),ans[y].push_back(x);
				}
			}
		}
	for (int i=1;i<=n;i++)
	{
		printf("%d%c",ans[i].size(),ans[i].size()==0?'\n':' ');
		sort(ans[i].begin(),ans[i].end());
		for (int j=0;j<ans[i].size();j++)
			printf("%d%c",ans[i][j],j<ans[i].size()-1?' ':'\n');
	}
//	cerr<<across(Line(Point(-10000,17),Point(12,17)),Line(Point(10,0),Point(10,10)))<<endl;
	return 0;
}
