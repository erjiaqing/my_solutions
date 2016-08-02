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

long long cur[20000000];

long long esum[100];
long long rsum[100];

int main()
{
	int my_node = MyNodeId();
	int tot_node = NumberOfNodes();
	int N = GetNumStacks();
	long long ans_of_this_node = 0;
	if (tot_node == 1)
	{
		cout << "This will not happen!!!\n";
		return 0;
	}
	if (my_node == 0)
	{
		long long ans = 0;
		long long sum = 0;
		for (int i = 1; i < tot_node; i++)
		{
			Receive(i); // 1
			rsum[i] = GetLL(i); // 1
			sum += rsum[i];
			// To get sum of each part
		}
		for (int i = 1; i < tot_node; i++)
		{
			PutLL(i, sum); // 2
			Send(i); // 2
			// Tell others the sum
		}
		long long last = 0;
		for (int i = 1; i < tot_node; i++)
		{
			Receive(i); // 3
			long long th = GetLL(i); // 3
			// Tell me the sum after moves
			PutLL(i, last); // 4
			Send(i); // 4
			last += th;
		}
		for (int i = 1; i < tot_node; i++)
		{
			Receive(i); // 5
			// Get the answer of each part
			(ans += GetLL(i)) %= mod; // 5
		}
		printf("%lld\n", ans);
	} else {
		tot_node--;
		int each = N / tot_node + 1;
		int l = each * (my_node - 1);
		int r = each * my_node;
		if (r > N) r = N;
		long long this_sum = 0;
		for (int i = l; i < r; i++)
		{
			cur[i - l] = GetStackHeight(i + 1);
			this_sum += cur[i - l];
		}
		PutLL(0, this_sum); // 1
		Send(0); // 1
		// Tell host the sum of this part
		Receive(0); // 2
		// Get the global sum
		long long sum = GetLL(0); // 2
		long long sum2 = 0;
		long long lf = 0, lfs = 0, rfs = 0;
		long long _cur = 0;
		lf = sum % N;
		lfs = sum / N + 1;
		rfs = sum / N;
		for (int i = l; i < r; i++)
			if (i < lf)
				sum2 += lfs;
			else
				sum2 += rfs;
		PutLL(0, sum2 - this_sum); // 3
		Send(0); // 3
		// Tell host the diff. of this part
		Receive(0); // 4
		_cur = GetLL(0); // 4
		long long ans = 0;
		for (int i = l; i < r; i++)
		{
			if (i < lf)
				_cur += lfs - cur[i - l];
			else
				_cur += rfs - cur[i - l];
			ans += abs(_cur);
		}
		PutLL(0, ans); // 5
		Send(0); // 5
		// Tell host my answer
	}
	return 0;
}
