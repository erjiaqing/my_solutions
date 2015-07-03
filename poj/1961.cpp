#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 1000000 + 5;
char str[maxn];
int nxt[maxn] , l ,T;
bool work()
{
	scanf("%d" , &l);
	if (!l) return false;
	printf("Test case #%d\n",++T);
	scanf("%s" , str + 1);
	// KMP
	int j = 0;
	nxt[1] = 0;
	for (int i = 2 ; i <= l ; i++)
	{
		while (j > 0 && str[j + 1] != str[i]) j = nxt[j];
		if (str[j + 1] == str[i]) j++;
		nxt[i] = j;
	}
	for (int i = 2 ; i <= l ; i++)
		if (i % (i - nxt[i]) == 0 && nxt[i] != 0)
			printf("%d %d\n",i,i/(i - nxt[i]));
	printf("\n");
	return true;
}
int main()
{
	while(work());
	return 0;
}
