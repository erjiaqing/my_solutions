#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int maxl = 20000 + 5;
int n , B , D , f , F;
int ans = 0x7fffffff;
int a , b , c;
char s[maxl];
bool work()
{
	if (scanf("%d%d%d%d%d" , &n , &B , &D , &f , &F) != 5) return false;
	ans = 0x7fffffff;
	a = B + D + f;
	b = B * 2 + D * 2 + F;
	c = B * 3 + D * 3 + F * 2;
	while ( n-- )
	{
		int ta = 0;
		scanf("%s" , s);
		int l = strlen(s);
		for (int i = 0 ; i < l ; i++)
		{
			if (s[i] == 'A') ta += a;
			else if (s[i] == 'B') ta += b;
			else if (s[i] == 'C') ta += c;
		}
		ans = min ( ans , ta );
	}
	printf("%d\n" , ans);
	return true;
}
int main()
{
	while(work());
}
