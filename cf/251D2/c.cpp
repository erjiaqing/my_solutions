#include <bits/stdc++.h>
using namespace std;
stack<int> even,odd;
int n,k,p,t;
void process()
{
	printf("%d",even.size()+odd.size());
	while (!even.empty())
	{
		printf(" %d",even.top());
		even.pop();
	}
	while (!odd.empty())
	{
		printf(" %d",odd.top());
		odd.pop();
	}
	printf("\n");
}
int main()
{
	int os(0),es(0),u;
	scanf("%d%d%d",&n,&k,&p);
	u=k-p;
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&t);
		if (t&1) odd.push(t),os++;
		else     even.push(t),es++;
	}
//	int os=odd.size(),es=even.size();
	if ((os<u) || ((os-u)&1) || (es+(os-u)/2) < p)
	{
		printf("NO\n");
	}else
	{
		printf("YES\n");
		if (u)
		{
			for (int i=0;i<u-1;i++)
			{
				printf("1 %d\n",odd.top());
				odd.pop();
			}
			if (!p)
			{
				process();
				return 0;
			}
			printf("1 %d\n",odd.top()),odd.pop();
		}
		for (int i=0;i<p-1;i++)
		{
			if (i<es)
			{
				printf("1 %d\n",even.top());
				even.pop();
			}else
			{
				printf("2 %d",odd.top()),odd.pop();
				printf(" %d\n",odd.top()),odd.pop();
			}
		}
		process();
	}
	return 0;
}
