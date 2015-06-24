#include <set>
#include <cstdio>
#include <cstring>
using namespace std;
#define _max( _a, _b) ( (_a) > (_b) ? (_a) : (_b) )
int N;
int St, Yr;
int d;
int VI[15][2];
int interest[1000000];
void work()
{
	scanf("%d%d", &St, &Yr);
	scanf("%d", &d);
	for (int i = 0; i < d; i++) scanf("%d%d", &VI[i][0], &VI[i][1]),VI[i][0]/=1000;
	for (int i = 0; i < d; i++)
		for (int j = VI[i][0]; j < 1000000; j++)
			interest[j] = _max( interest[j] , interest[ j - VI[i][0] ] + VI[i][1] );
	for (int i = 0; i < Yr; i++) St += interest[St/1000];
	printf("%d\n", St);
}
void clear()
{
	memset(interest, 0, sizeof(interest));
}
int main()
{
	int T;
	scanf("%d", &T);
	while (T--) work(),clear();
	return 0;
}

