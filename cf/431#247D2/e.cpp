#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
const int maxn=100005;
struct oper{int op,p,x;long long v;}op[maxn];
int n,q,top,tp,tx;
long long tv;
set<int>S;
multiset<int>S2;
map<int,int>Pos;
int x[maxn],cnt;
double bit[maxn*2];
int bit2[maxn*2];
double val[maxn*2];
inline int lowbit(const int &x){return x&(-x);}
inline void      bitadd(int p,const int &v,int *b){for (;p<=cnt;p+=lowbit(p)) b[p]+=v;}
inline void      bitadd(int p,const int &v,double *b){for (;p<=cnt;p+=lowbit(p)) b[p]+=v;}
inline double bitsum(int p,double *b){double ret=0;for (;p;p-=lowbit(p)) ret+=b[p];return ret;}
inline int       bitsum(int p,int *b)      {int       ret=0;for (;p;p-=lowbit(p)) ret+=b[p];return ret;}
long long check(int x,bool flag=false)
{
	int t=bitsum(x-1,bit2);
	double v1=1.0*t*val[x]-bitsum(x-1,bit);
//if (flag) printf("%d %d %.0lf %.0lf\n",x,t,val[x],v1);
	return v1;
}
double find(long long v)
{
	int l=1,r=cnt,mid;
	double tans=0;
	while (l<r)
	{
		mid=(l+r)>>1;
		tans=check(mid);
		if (tans>=v)
			r=mid;
		else
			l=mid+1;
	}
//	cerr<<l<<"("<<val[l]<<endl;
	return val[l]-1.0*(check(l,1)-v)/bitsum(l-1,bit2);
}
int main()
{
	long long maxv=0;
	scanf("%d%d",&n,&q);
	for (int i=1;i<=n;i++){scanf("%d",&x[i]);S.insert(x[i]);S2.insert(x[i]);}
	for (int i=1;i<=q;i++)
	{
		scanf("%d",&top);
		if (top==1) scanf("%d%d",&tp,&tx),op[i].op=top,op[i].p=tp,op[i].x=tx,S.insert(tx);
		else        scanf("%lld",&tv),op[i].op=top,maxv=max(maxv,op[i].v=tv);
	}
	for (set<int>::iterator sii=S.begin();sii!=S.end();sii++){Pos[*sii]=++cnt;val[cnt]=*sii;}
	val[++cnt]=maxv*2;cnt++;
	for (int i=1;i<=n;i++) {bitadd(Pos[x[i]],x[i],bit);bitadd(Pos[x[i]],1,bit2);}
	int tp;
	for (int i=1;i<=q;i++)
	{
		if (op[i].op==1)
		{
			tp=op[i].p;
			bitadd(Pos[x[tp]],-x[tp],bit);
			bitadd(Pos[x[tp]],-1,bit2);
//			S2.erase(S2.find(x[tp]));
			x[tp]=op[i].x;
//			S2.insert(x[tp]);
			bitadd(Pos[x[tp]],x[tp],bit);
			bitadd(Pos[x[tp]],1,bit2);
		}else
		{
			printf("%.5lf\n",find(op[i].v));
		}
	}
	return 0;
}
