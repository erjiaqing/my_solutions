#include <bits/stdc++.h>
using namespace std;
const int maxn = 64 + 5;
char str[maxn];
long long dfs(char *s , char A , char B , char C)
{
	int l = strlen(s);
	if (s[0] == 0) return 0;
	if (s[0] == A)
	{
		return (dfs(s + 1 , A , C , B) + (1ll << (l - 1)));
	}
	else if (s[0] == B)
	{
		return dfs(s + 1 , C , B , A);
	}
}
int main()
{
	while ((~scanf("%s" , str)) && (str[0] != 'X'))
	{
		int l = strlen(str);
		for (int i = 0 , j = l - 1 ; i <= j ; i++ , j--)
			swap(str[i] , str[j]);
		printf("%lld\n" , dfs(str , 'A' , 'B' , 'C'));
	}
	return 0;
}
