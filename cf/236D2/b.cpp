#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n,k;
int a[1005],b[1005];
int ans=99999999,tans=0,mid=0;
int abs(int x)
{
	return (x<0)?(-x):(x);
}
int main()
{
	scanf("%d%d",&n,&k);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for (int i=1;i<=n;i++)
	{
		tans=0;
		for (int j=1;j<=n;j++)
			b[j]=a[j];
		for (int j=i-1;j>0;j--)
		{
			if (b[j+1]-k<=0)
				tans=99999999;
			else
			{
				tans+=(abs(b[j]-(b[j+1]-k))!=0);
				b[j]=b[j+1]-k;
			}
		}
		for (int j=i+1;j<=n;j++)
		{
			tans+=(abs(b[j]-(b[j-1]+k))!=0);
			b[j]=b[j-1]+k;
		}
		if (tans<ans)
		{
			ans=tans;
			mid=i;
		}
	}
	printf("%d\n",ans);
	for (int j=1;j<=n;j++)
		b[j]=a[j];
	for (int j=mid-1;j>0;j--)
	{
		//tans+=abs(b[j]-(b[j+1]-k));
		if (b[j]>b[j+1]-k)
			printf("- %d %d\n",j,abs(b[j]-(b[j+1]-k)));
		else if (b[j]<b[j+1]-k)
			printf("+ %d %d\n",j,abs(b[j+1]-k-b[j]));
		b[j]=b[j+1]-k;
	}
	for (int j=mid+1;j<=n;j++)
	{
		//tans+=abs(b[j]-(b[j-1]+k));
		if (b[j]>b[j-1]+k)
			printf("- %d %d\n",j,abs(b[j]-(b[j-1]+k)));
		else if (b[j]<b[j-1]+k)
			printf("+ %d %d\n",j,abs(b[j-1]+k-b[j]));
		b[j]=b[j-1]+k;
	}
	return 0;
}
