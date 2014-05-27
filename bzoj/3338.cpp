#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <utility>
using namespace std;
const int dx[]={ 0, 1, 0,-1},
	      dy[]={ 1, 0,-1, 0};
int this_map[9][9];
struct board{
	int t,s;
	pair<int,int> c[4];
}B,E;
#define x first
#define y second
int H[16777215];
int hash(board stat)
{
	int ret=0;
	sort(&stat.c[0],&stat.c[4]);
	for (int i=0;i<4;i++)
	{
		ret*=8;ret+=stat.c[i].x-1;
		ret*=8;ret+=stat.c[i].y-1;
	}
	return ret;
}
bool bfs()
{
	queue<board>Q;
	Q.push(B);
	Q.push(E);
}
int main()
{
	while (~scanf("%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
				&B.c[0].x,&B.c[0].y,&B.c[1].x,&B.c[1].y,&B.c[2].x,&B.c[2].y,&B.c[3].x,&B.c[3].y,
				&E.c[0].x,&E.c[0].y,&E.c[1].x,&E.c[1].y,&E.c[2].x,&E.c[2].y,&E.c[3].x,&E.c[3].y
				))
	{
		B.t= 1;B.s=0;
		E.t=-1;E.s=0;
	}
	return 0;
}
