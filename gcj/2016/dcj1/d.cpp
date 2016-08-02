#include "winning_move.h" // Problem Name
#include <message.h>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <map>
using namespace std;

long long num[1000];
map<long long, int> ct;
int main()
{
	int my_node = MyNodeId();
	int tot_node = NumberOfNodes();
	int n = GetNumPlayers();
	// ... Process
	if (n <= 1000)
	{
		if (my_node == 0)
		{
			long long ans = 0;
			for (int i = 0; i < n; i++)
			{
				num[i] = GetSubmission(i);
				ct[num[i]]++;
			}
			for (int i = 0; i < n; i++)
				if (ct[num[i]] == 1)
					if (ans == 0 || num[i] < ans)
						ans = num[i];
			printf("%lld\n", ans);
		}
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
