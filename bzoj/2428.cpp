#include <bits/stdc++.h>
using namespace std;
const int maxn=30,maxm=10;
int a[maxn],b[maxn],s[maxm],m,n;
double avg;
inline double sqr(const double &x) {return x*x;}
inline double cal()
{
	double ret=0;
	memset(s,0,sizeof(s));
	for (int i=0;i<n;i++) s[b[i]]+=a[i];
	for (int i=0;i<m;i++)
		if (s[i])
			ret+=sqr(s[i]-avg);
		else
			return 1e10;
	return ret;
}
int main()
{
	srand(251123);
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++) scanf("%d",&a[i]),avg+=a[i];avg/=m;
	for (int i=0;i<n;i++) b[i]=rand()%m;
	double ans,best,tans,p1,p2;
	ans=best=cal();
	int t1,t2,t3,t4,s1,s3;
	int t0=16,t=t0;
	for (int i=1;i<100000;i++)
	{
//		for (int i=0;i<n;i++) printf("%d ",b[i]);printf("\n");
		t1=rand()%n;t2=rand()%m;
		t3=rand()%n;t4=rand()%m;
		s1=b[t1];s3=b[t3];
		b[t1]=t2;b[t3]=t4;
		tans=cal();
//		for (int i=0;i<n;i++) printf("%d ",b[i]);//printf("\n");
//		cerr<<tans<<endl;
		if (tans<ans)
		{
			ans=tans;
			if (tans<best)
				best=tans;
			b[t1]=t2;b[t3]=t4;
		}else
		{
			p1=rand()%10000/10000.0;
			p2=exp((ans-tans)/t);
			if (p1<p2)
				ans=tans,b[t1]=t2,b[t3]=t4;
			else
				b[t1]=s1,b[t3]=s3;
		}
		t=t0/log(i+1);
	}
	printf("%.2lf\n",sqrt(best/m));
	return 0;
}
