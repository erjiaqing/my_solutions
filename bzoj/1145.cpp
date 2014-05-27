#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=200005;
int n,a[maxn],p[maxn],t[5][maxn],ans,re;
int lowbit(int x)
{
	return x&(-x);
}
void insert(int i,int x,int y)
{
	for (;x;x-=lowbit(x))
		t[i][x]+=y;
}
int find(int i,int x)
{
	for (re=0;x<=n;x+=lowbit(x))
		re+=t[i][x];
	return re;
}
int main()
{
	int y,z;
	long long x;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		p[a[i]]=i;
		y=n+1-a[i];
		x=(z=find(0,y))+y-i;
		ans=(ans+x*find(1,y)-x*(x-1)*(x-2)/6+x*(z*a[i]-find(2,y)-(z*(z+1)/2)))&16777215;
		insert(0,y,1);insert(1,y,z);insert(2,y,a[i]);
	}
	for (int i=1;i<=n;i++)
	{
		x=find(3,y=n+1-p[i]);
		ans=(ans+(x*p[i]-find(4,y)-((x*(x+1))/2))*(x+y-i))&16777215;
		insert(3,y,1);insert(4,y,p[i]);
	}
	printf("%d\n",ans&16777215);
	return 0;
}
