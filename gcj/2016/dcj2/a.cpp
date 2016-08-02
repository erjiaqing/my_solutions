#include "again.h"
#include <message.h>
#include <cstdio>
const int mod = 1000000007;
long long min(int x, int y)
{
	return x < y ? x : y;
}
long long sumA[20];
long long sumB[20];
int main()
{
	int totnode = NumberOfNodes();
	int mynode = MyNodeId();
	int n = GetN();
	long long tsumA = 0, tsumB = 0;
	for (int i = mynode; i < n; i += totnode)
		(sumA[mynode] += GetA(i)) %= mod;
	for (int i = mynode; i < n; i += totnode)
		(sumB[mynode] += GetB(i)) %= mod;
	//fprintf(stderr, "%d %lld %lld\n", mynode, sumA[mynode], sumB[mynode]);
	if (mynode)
	{
		PutLL(0, sumA[mynode]);
		Send(0);
		PutLL(0, sumB[mynode]);
		Send(0);
		return 0;
	} else {
		for (int i = 1; i < totnode; i++)
		{
			Receive(i);
			(sumA[i] = GetLL(i)) %= mod;
			Receive(i);
			(sumB[i] = GetLL(i)) %= mod;
		}
		long long ans = 0;
		for (int i = 0; i < totnode; i++)
			for (int j = 0; j < totnode; j++)
				if ((i + j) % totnode)
					ans = (ans + sumA[i] * sumB[j]) % mod;
		printf("%lld\n", ans);
	}
	return 0;
}
