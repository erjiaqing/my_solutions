#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
typedef pair<int,int> pii;
vector<pii> v;
int n,m,k;
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	int x(1),y(1),dir(1);v.push_back(pii(x,y));
	while (1)
	{
		y+=dir;
		if (y>m) dir*=-1,y=m,x++;
		if (y<1) dir*=-1,y=1,x++;
		if (x>n) break;
		v.push_back(pii(x,y));
	}
	for (int i=0;i<k-1;i++)
		printf("%d %d %d %d %d\n",2,v[2*i].x,v[2*i].y,v[2*i+1].x,v[2*i+1].y);
	printf("%d",v.size()-2*(k-1));
	for (int i=2*(k-1);i<v.size();i++)
		printf(" %d %d",v[i].x,v[i].y);
	printf("\n");
	return 0;
}
