#include <bits/stdc++.h>
using namespace std;
vector<int> s;
int n,v,t,c,m;
int main()
{
	scanf("%d%d",&n,&v);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&c);
		t=0x3f3f3f3f;
		while (c--)
			scanf("%d",&m),t=min(t,m);
		if (t<v) s.push_back(i);
	}
	printf("%d\n",s.size());
	for (int i=0;i<s.size();i++) printf("%d ",s[i]);
	printf("\n");
	return 0;
}
