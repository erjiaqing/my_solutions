#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 5;
char str[maxn];
int main()
{
	str[0] = 'a';
	for (int i = 0 ; i < 14 ; i++)
		for (int j = 0 ; j < (1 << i) ; j++)
			str[(1 << i) + j] = (str[j] == 'a' ? 'b' : 'a');
	printf("16384 4096\n%s\n",str);
	return 0;
}
