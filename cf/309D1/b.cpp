#include <bits/stdc++.h>
using namespace std;
const int maxn = 50 + 5;
unsigned long long fib[maxn],l;
int k,pos;
int main()
{
	fib[0] = fib [1] = 1;
	for (int i = 2 ; i <= 50 && fib[i-1] <= 1e18 ; i++)
		fib[i] = fib[i - 1] + fib[i - 2];
	scanf("%d%lld", &k , &l);
	for (int i = 1;i <= k;)
		if (l > fib[k - i])
			printf("%s%d %d",(i==1?"":" "),i + 1,i),l -= fib[k - i],i += 2;
		else
			printf("%s%d",(i==1?"":" "),i),i++;
	printf("\n");
	return 0;
}
