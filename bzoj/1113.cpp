#include <bits/stdc++.h>
using namespace std;
const int maxn=250005;
int n,sta[maxn],top,ans,a;
int main()
{
	ios::sync_with_stdio(0);
	cin>>n;
	while (n--)
	{
		cin>>a;cin>>a;
		while (top && sta[top]>a) top--;
		if (sta[top]!=a) ans++,sta[++top]=a;
	}
	cout<<ans<<endl;
	return 0;
}
