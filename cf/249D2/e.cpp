#include <bits/stdc++.h>
using namespace std;
const int maxn=1005;
char mp[maxn][maxn],om[maxn][maxn],tm[maxn][maxn],co[]="1234";
int n,m;
bool check(int x,int y)
{
	return (mp[x][y]=='0' || mp[x][y]==om[x][y]);
}
bool check1()
{
	for (int i=0;i<2;i++)
		for (int j=2;j<m;j++)
		{
			om[i][j]=om[i][j-2];
			if (!check(i,j))
				return false;
		}
	for (int i=2;i<n;i++)
	{
		bool fi=true;
		om[i][0]=om[i-2][0];om[i][1]=om[i-2][1];
		fi=(check(i,0)&&check(i,1));
		for (int j=2;j<m;j++) om[i][j]=om[i][j-2],fi&=check(i,j);
		if (fi) continue;
		swap(om[i][0],om[i][1]);
		fi=(check(i,0)&&check(i,1));
		for (int j=2;j<m;j++) om[i][j]=om[i][j-2],fi&=check(i,j);
		if (!fi) return false;
	}
	return true;
}
bool check2()
{
	for (int i=2;i<n;i++)
		for (int j=0;j<2;j++)
		{
			om[i][j]=om[i-2][j];
			if (!check(i,j))
				return false;
		}
	for (int j=2;j<m;j++)
	{
		bool fi=true;
		om[0][j]=om[0][j-2];om[1][j]=om[1][j-2];
		fi=(check(0,j)&&check(1,j));
		for (int i=2;i<n;i++) om[i][j]=om[i-2][j],fi&=check(i,j);
		if (fi) continue;
		swap(om[0][j],om[1][j]);
		fi=(check(0,j)&&check(1,j));
		for (int i=2;i<n;i++) om[i][j]=om[i-2][j],fi&=check(i,j);
		if (!fi) return false;
	}
	return true;
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++) scanf("%s",mp[i]);
//	for (int i=0;i<n;i++)
//		for (int j=0;j<m;j++)
//			mp[i][j]-='0';
//	co[0]=1,co[1]=2,co[2]=3,co[3]=4;
	for (int i=0;i<24;i++)
	{
		om[0][0]=co[0];om[0][1]=co[1];
		om[1][0]=co[2];om[1][1]=co[3];
		if (check(0,0) && check(0,1) && check(1,0) && check(1,1))
		{
			if (check1()||check2())
			{
				for (int i=0;i<n;i++)
				{
					for (int j=0;j<m;j++)
						printf("%c",om[i][j]);
					printf("\n");
				}
				return 0;
			}
		}
		next_permutation(co,co+4);
	}
	printf("0\n");
	return 0;
}
