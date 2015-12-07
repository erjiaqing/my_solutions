// After reading the editorial
// http://www.acmicpc-pacnw.org/ProblemSet/2015/Writeup.html
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
double dp[10000000 + 5];
int main()
{
	memset(dp, 0, sizeof(dp));
	int e, es, ef;
	scanf("%d%d%d", &e, &es, &ef);
	for (int i = 1; i <= e; i++)
		dp[i] = ((i - es) > 0 ? dp[i - es] : 0) + ((i - ef) > 0 ? dp[i - ef] : 0) + 1;
	printf("%.6f\n", min(225 / (dp[e] + 1), 200 / dp[e]));
	return 0;
}
