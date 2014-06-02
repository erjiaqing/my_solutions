#include <bits/stdc++.h>
using namespace std;
int n,ai;
char Map[2050][2050];
//int x[2050],y[2050];
int main()
{
	scanf("%d",&n);
	memset(Map,' ',sizeof(Map));
	int nowx=0,nowy=1000;
	int miny=1000,maxy=1000;
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&ai);
		for (int x=nowx;x<nowx+ai;x++)
		{
			if (i&1)
			{
				Map[nowy][x]='/';
				maxy=max(maxy,nowy++);
			}else
			{
				Map[--nowy][x]='\\';
				miny=min(miny,nowy);
			}
		}
		nowx+=ai;
	}
	for (int i=maxy;i>=miny;i--)
	{
		for (int j=0;j<nowx;j++)
			printf("%c",Map[i][j]);
		printf("\n");
	}
	return 0;
}

