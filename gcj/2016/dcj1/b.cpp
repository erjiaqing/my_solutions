#include "rps.h" // Problem Name
#include <message.h>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

char f[4194304];
int RealId[64];
int N = 0;

int dfs(int l, int r)
{
	if (l == r) return l;
	int mid = (l + r) / 2;
	int ls = dfs(l, mid);
	int rs = dfs(mid + 1, r);
	if (f[ls] == 'S')
	{
		if (f[rs] == 'R') return rs;
		else return ls;
	} else if (f[ls] == 'P')
	{
		if (f[rs] == 'S') return rs;
		else return ls;
	} else
	{
		if (f[rs] == 'P') return rs;
		else return ls;
	}
}

void process_small_data()
{
	int tot_node = 1 << N;
	for (int i = 0; i < tot_node; i++)
		f[i] = GetFavoriteMove(i);
	printf("%d\n", dfs(0, tot_node - 1));
}

void process_large_data(int l, int r)
{
	for (int i = l; i < r; i++)
		f[i - l] = GetFavoriteMove(i);
	int this_res = dfs(0, r - l - 1);
	PutLL(0, this_res + l);
	Send(0);
	PutChar(0, f[this_res]);
	Send(0);
}

int main()
{
	int my_node = MyNodeId();
	int tot_node = NumberOfNodes();
	N = GetN();
	int totn = (1 << N);
	if (N <= 10)
	{
		if (my_node == 0) process_small_data();
		return 0;
	}
	if (my_node == 0)
	{
		for (int i = 0; i < 64; i++)
		{
			Receive(i + 1);
			RealId[i] = GetLL(i + 1);
			Receive(i + 1);
			f[i] = GetChar(i + 1);
		}
		printf("%d\n", RealId[dfs(0, 63)]);
	} else {
		if (my_node > 64) return 0;
		int l = totn / 64 * (my_node - 1);
		int r = totn / 64 * (my_node);
		process_large_data(l, r);
	}
//	long long ans_of_this_node = 0;
	// ... Process
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
