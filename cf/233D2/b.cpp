#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char buf[60];
int main()
{
	long long end=1,now=0;
	long long n;
	cin>>n;cin>>buf;
	for (int i=n-1;i>=0;i--)
	{
		now*=2;
		end*=2;
		if (buf[i]=='R')
			now+=1;
	}
	end--;
	cout<<end-now<<endl;
}
