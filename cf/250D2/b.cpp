#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
pair<int,int> LowBit[maxn];
bool sel[maxn];
int lowbit(int x){return x&(-x);}
int sum,lim;
int main()
{
	for (int i=1;i<maxn;i++) LowBit[i]=make_pair(lowbit(i),i);
	scanf("%d%d",&sum,&lim);
	sort(&LowBit[1],&LowBit[lim+1]);
	int ans=0;
	for (int i=lim;i>0;i--)
	{
		if (LowBit[i].first<=sum)
		{
			sel[LowBit[i].second]=true;
			ans++;
			sum-=LowBit[i].first;
		}
	}
	if (sum)
	{
		printf("%d\n",-1);
	}else
	{
		printf("%d\n",ans);
		for (int i=1;i<=lim;i++)
			if (sel[i])
				printf("%d ",i);
		printf("\n");
	}
	return 0;
}
