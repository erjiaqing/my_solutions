#include <bits/stdc++.h>
using namespace std;
struct Int
{
	int a[105],len;
	bool read()
	{
		char buf[105];
		if (~scanf("%s",buf))
		{
			len=strlen(buf);
			reverse(&buf[0],&buf[len]);
			for (int i=0;i<len;i++) a[i]=buf[i]-'0';
			while (len>0 && a[len]==0) len--;
			return true;
		}else
		{
			return false;
		}
	}
	int div(int s)
	{
		int r=0;
		for (int i=len;i>=0;i--)
		{
			(r*=10)+=a[i];
			a[i]=r/s;r%=s;
		}
		while (len>0 && a[len]==0) len--;
		return r;
	}
};
int md[]={6,6,2,6,4,4,4,8,4,6};
Int a;
int solve()
{
	int ret=1,fi=0;
	while (a.len>0 || a.a[a.len]>1)
	{
		ret=ret*md[a.a[0]]%10;
		a.div(5);
		fi=(fi+a.a[1]*10+a.a[0])&3;
	}
	while (fi--)
		(ret*=8)%=10;
	return ret;
}
int main()
{
	while (a.read())
		printf("%d\n",solve());
	return 0;
}

