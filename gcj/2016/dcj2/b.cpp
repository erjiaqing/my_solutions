#include "lisp_plus_plus.h"
#include <message.h>
#include <cstdio>
using namespace std;
int nodecnt[100];
char chr[10000000 + 5];
int min(int x, int y)
{
	return x < y ? x : y;
}
int max(int x, int y)
{
	return x < y ? y : x;
}
int main()
{
	int totnode = NumberOfNodes();
	int mynode = MyNodeId();
	int n = GetLength();
	int thisSum = 0;
	int tc = n / totnode + 1;
	int l = tc * mynode;
	int r = min(tc * (mynode + 1), n);
	int ans = 0;
	int last00 = 0;
	int first000 = -1;
	for (int i = l; i < r; i++)
	{
		chr[i - l] = GetCharacter(i);
		if (chr[i - l] == '(')
			nodecnt[mynode]++;
		else
			nodecnt[mynode]--;
		if (nodecnt[mynode] == 0)
		{
			if (first000 == -1)
				last00 = i + 1;
		}
		if (nodecnt[mynode] < 0)
		{
			first000 = i + 1;
		}
	}
//	if (l < r)
//		fprintf(stderr, "%d %d\n", l, r);
	if (mynode)
	{
//		fprintf(stderr, "%d %d %d\n", l, r, nodecnt[mynode]);
		PutInt(0, nodecnt[mynode]);
		Send(0);
		Receive(0);
		int cur = GetInt(0);
		int last0 = -1;
		int first00 = -1;
		for (int i = l; i < r; i++)
		{
			if (chr[i - l] == '(')
				cur++;
			else
				cur--;
			if (cur == 0)
			{
				if (first00 == -1)
					last0 = i + 1;
			} else if (cur < 0)
			{
				first00 = i;
				break;
			}
		}
		PutInt(0, last0);
		Send(0);
		PutInt(0, first00);
		Send(0);
		return 0;
	} else {
		int curcnt = 0;
		for (int i = 1; i < totnode; i++)
		{
			Receive(i);
			nodecnt[i] = GetInt(i);
		//	fprintf(stderr, "   %d %d\n", i, nodecnt[i]);
		}
		int pref = 0;
		for (int i = 1; i < totnode; i++)
		{
			pref += nodecnt[i - 1];
			PutInt(i, pref);
			Send(i);
		}
		for (int i = 1; i < totnode; i++)
		{
			Receive(i);
			int lll = GetInt(i);
			if (first000 == -1 && lll != -1)
				last00 = lll;
			Receive(i);
			lll = GetInt(i);
			if (first000 == -1)
				break;
		}
		pref += nodecnt[totnode - 1];
		//fprintf(stderr, "%d", pref);
		printf("%d\n", last00 == n ? -1 : last00);
	}
	return 0;
}
