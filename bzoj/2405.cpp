#include <bits/stdc++.h>
using namespace std;
const int magic=22680;
int ans[magic+10];
inline int D(int x) {return (x-1)%9+1;}
void prep()
{
//	ans[0]=1;
	for (int i=1;i<=magic;i++)
		if (i * D(i) <= magic)
			ans[i*D(i)]=1;
	for (int i=1;i<=magic;i++)
		ans[i]+=ans[i-1];
}
long long getAns(long long r)
{
	if (r<0)
		return 0;
	return ((r/magic)*ans[magic])+ans[r%magic];
}
int main()
{
	prep();
	int t;
	long long l,r;
	cin>>t;
	while (t--)
	{
		cin>>l>>r;
		cout<<getAns(r)-getAns(l-1)<<endl;
	}
	return 0;
}
