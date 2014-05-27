#include <iostream>
#include <cstdio>
#include <utility>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const char o[]="0123456789abcdef";
const int maxn=1047135;     //瞎敲的！
typedef pair<int,int> pii; //用于记录状态 当前状态和前一状态
pii q[maxn];
int l[maxn][16];
int n,m;
int ans[maxn],len;
int MAP[16][16];
bool check(int k)
{
	for (int i=0;i<n;i++)
		if (l[k][i])
			return false;
	return true;
}
void getans(int x)
{
	for (;x;x=q[x].second)
		ans[len++]=q[x].first;
}
bool diff(int f,int t)
{
	int flag,x,i;
	for (x=f;x;x=q[x].second)
	{
		flag=false;
		for (i=0;i<n;i++)
			if (l[t][i]!=l[x][i])
				flag=true;
		if (!flag)
			return true;
	}
	return false;
}
int bfs()
{
	int i,j,k;
	int beg=0,end=1;
	for (i=0;i<n;i++)
		l[0][i]=i;
	while (beg<end)
	{
		if (check(beg))
		{
			getans(beg);return true;
		}
		for (i=0;i<m;i++)
		{
			for (j=0;j<n;j++)
				l[end][j]=MAP[l[beg][j]][i];
			if (!diff(beg,end))
				q[end++]=pii(i,beg);
		}
		beg++;
	}
	return false;
}
void output()
{
//	cerr<<len<<endl;
	while (len--)
		printf("%c",o[ans[len]]);
	printf("\n");
}
int main()
{
	int i,j;
	scanf("%d%d",&n,&m);
	for (i=0;i<n;i++)
		for (j=0;j<m;j++)
			scanf("%d",&MAP[i][j]);
	if (bfs())
		output();
	else
		printf("*\n");
	return 0;
}
