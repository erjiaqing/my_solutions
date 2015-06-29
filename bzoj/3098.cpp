#include <bits/stdc++.h>
using namespace std;
long long xa = 0x19088737 , xb = 0x89abcdef , xc = 44321267 , ls = xa ^ xb ^ xc;
char generate_char()
{
	ls = (ls * xc + xb ) % xa;
	return ls % 26 + 'a';
}
int main()
{
	printf("100000 8\n");
	for (int i = 0 ; i < 100000 ; i++) printf("%c",generate_char());
	return 0;
}
