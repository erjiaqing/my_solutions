#include <bits/stdc++.h>
using namespace std;
char pstr[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int a[40],x[40];
int n,b,s;
void print()
{
	for (int i=0;i<n;i++) printf("%c",pstr[a[i]]);
	printf("\n");
}
int main()
{
	scanf("%d%d",&n,&b);
	s=1;
	for (int i=0;i<n;i++) s*=b,x[i]=1;
	print();
	while (--s)
	{
		for (int i=0;i<n;i++)
		{
			if (a[i]+x[i]>-1 && a[i]+x[i]<b)
			{
				a[i]+=x[i];
				break;
			}else
			{
				x[i]*=-1;
			}
		}
		print();
	}
	return 0;
}
