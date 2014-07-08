#include <cstdio>
const int maxn=505;
int x[maxn],a,b,c,n,m;
double ans=0;
inline double max(const double &__a,const double &__b) {return (__a<__b)?__b:__a;}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&x[i]);
	for (int i=1;i<=m;i++) scanf("%d%d%d",&a,&b,&c),ans=max(ans,double(x[a]+x[b])/c);
	printf("%.15f\n",ans);
}
