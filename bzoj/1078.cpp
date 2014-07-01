#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
const int maxn=105;
int ls[maxn],rs[maxn];
vi dfs(int u)
{
	vi l,r,t;
	if (~ls[u]) l=dfs(ls[u]);
	if (~rs[u]) r=dfs(rs[u]);
	if (l.size()==0 && r.size()==0)
		t.push_back(u);
	else if (r.size()==0)
	{
		if (l.size()>1)
		{
			t.push_back(u);
			for (int i=0;i<l.size();i++)
				t.push_back(l[i]);
		}else
			t.push_back(l[0]),t.push_back(u);
	}else
	{
		int i,j;
		for (i=0,j=0;i<l.size()&&j<r.size();i++,j++)
			t.push_back(l[i]),t.push_back(r[j]);
		if (i<l.size())
		{
			if (i==l.size()-1)
				t.push_back(l[i]),t.push_back(u);
			else
			{
				t.push_back(u);
				for (;i<l.size();i++) t.push_back(l[i]);
			}
		}else if (j<r.size())
		{
			t.pop_back();j--;
			t.push_back(u);
			for (;j<r.size();j++) t.push_back(r[j]);
		}else
		{
			t.push_back(u);
		}
	}
	return t;
}
int main()
{
	memset(ls,-1,sizeof(ls));memset(rs,-1,sizeof(rs));
	int n,t;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&t),(t<100)?(ls[t]=i):(rs[t-100]=i);
	vi ans=dfs(0);
	for (int i=ans.size()-1;i>=0;i--) printf("%d ",ans[i]);
	printf("\n");
	return 0;
}

