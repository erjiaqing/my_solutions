#include "oops.h" // Problem Name
#include <message.h>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

using namespace std;
int main()
{
	int my_node = MyNodeId();
	int tot_node = NumberOfNodes();
	int N = GetN();
	long long __min = 0x7fffffffffffffffll, __max = 0x8000000000000000ll;
	int ec = N / tot_node + 1;
	int l = ec * my_node;
	int r = ec * (my_node + 1);
	//cerr << l << ' ' << r << endl;
	r = min(r, N);
	__min = __max = GetNumber(0);
	for (int i = l; i < r; i++)
	{
		long long curnum = GetNumber(i);
		__min = min(__min, curnum);
		__max = max(__max, curnum);
	}
	// ... Process
	if (my_node == 0)
	{
		long long ans = __max - __min;
		for (int i = 1; i < tot_node; i++)
		{
			for (int j = 0; j < 2; j++)
			{
			Receive(i);
			long long val = GetLL(i);
			__max = max(__max, val);
			__min = min(__min, val);
			}
			// Update ans via val
		}
		ans = __max - __min;
		printf("%lld\n", ans);
	} else {
		PutLL(0, __max);
		Send(0);
		PutLL(0, __min);
		Send(0);
	}
	return 0;
}
