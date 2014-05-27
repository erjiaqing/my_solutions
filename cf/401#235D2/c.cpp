#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=2000005;
char fig1[]="110";
char fig2[]="10";
char fig3[]="0";
char fig4[]="1";
char out[maxn];
int n,m,n1,m1;
int pnt;
int last=0;
int ccnt=0;
int main()
{
	scanf("%d%d",&n,&m);n1=n;m1=m;
	if ((m<n-1) || (m>2*n+2)){printf("-1\n");return 0;}
	if (n1>m1)
	{
		out[pnt++]='0';
		n1--;
	}else
	{
		out[pnt++]='1';
		m1--;
		last=1;
		ccnt++;
	}
	while (n1>0 || m1>0)
	{
		if (m1>n1 && n1>0 && last==0)
		{
			out[pnt++]='1';out[pnt++]='1';out[pnt++]='0';
			m1-=2;n1-=1;
			last=0;
			continue;
		}
		if ((m1>n1||last==0) && ccnt<2)
		{
			ccnt++;
			out[pnt++]='1';
			m1--;
			last=1;
		}else
		{
			ccnt=0;
			out[pnt++]='0';
			n1--;
			last=0;
		}
	}
	printf("%s\n",out);
	return 0;
}
