#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
long long x[maxn],s[maxn];
int r,l;
long long b;
long long calc(int L,int R)
{
	int mid=(L+R)/2;
	return (s[R]-s[mid])-x[mid]*(R-mid)+x[mid]*(mid-L)-(s[mid-1]-s[L-1]);
}
int main()
{
	ios::sync_with_stdio(0);
	cin>>r>>l>>b;
	for (int i=1;i<=r;i++){cin>>x[i];s[i]+=s[i-1]+x[i];}
	int s=1,t=1,ans=0;
	for (s=1;s<=r;s++)
	{
		while (t<r && calc(s,t+1)<=b) t++;
		ans=max(ans,(t-s+1));
//		cerr<<s<<"-"<<t<<endl;
	}
	cout<<ans<<endl;
//	while (cin>>s>>t) cerr<<calc(s,t)<<endl;
	return 0;
}
