#include "crates.h" // Problem Name
#include <message.h>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

const int mod = 1000000007;

long long sta[10000000 + 5];
long long tar[10000000 + 5];

/*
__int128 eabs(__int128 x)
{
	if (x < 0) return -x;
	return x;
}
*/
int main()
{
	int my_node = MyNodeId();
	int tot_node = NumberOfNodes();
	long long ans_of_this_node = 0;
	// ... Process
	int N = GetNumStacks();
	long long tot = 0;
	long long lf = 0, lfs = 0, rfs = 0;
//	if (N <= 1000000)
	{
		if (my_node != 0) return 0;
		for (int i = 0; i < N; i++)
		{
			sta[i] = GetStackHeight(i + 1) % mod;
			(tot += sta[i]);
		}
		lf = tot % N;
		lfs = tot / N + (lf != 0);
		rfs = tot / N;
		long long cur = 0;
		long long ans = 0;
		for (int i = 0; i < N; i++)
		{
			if (i < lf)
				cur += sta[i] - lfs;
			else
				cur += sta[i] - rfs;
			(ans += abs(cur)) %= mod;
		}
		printf("%lld\n", ans);
		return 0;
	}
	/*
	if (my_node == 0)
	{
		long long ans = 0;
		for (int i = 1; i < tot_node; i++)
		{
			Receive(i);
			long long val = GetLL(i);
			// Update ans via val
		}
		printf("%lld\n", ans);
	} else {
		PutLL(0, ans_of_this_node);
		Send(0);
	}*/
	return 0;
}
