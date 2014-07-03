#include <bits/stdc++.h>
using namespace std;
int n,k;
int main()
{
	cin>>n>>k;
	if (k>n-k+1) k=n-k+1;
	cout<<((n==1)?1:2*k)<<endl;
	return 0;
}
