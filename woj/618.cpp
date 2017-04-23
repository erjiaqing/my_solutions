#include <bits/stdc++.h>
using namespace std;

const int maxn = 500000 + 5;

int n;
long long arr[maxn];
int mxlft[maxn], mxrgt[maxn], milft[maxn], mirgt[maxn];
int ar[maxn], ed;

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> arr[i];
	ed = 0;
	for (int i = 1; i <= n; i++)
	{
		while (ed && arr[ar[ed]] <= arr[i]) ed--;
		mxlft[i] = ar[ed] + 1;
		ar[++ed] = i;
	}
	ed = 0;
	for (int i = 1; i <= n; i++)
	{
		while (ed && arr[ar[ed]] >= arr[i]) ed--;
		milft[i] = ar[ed] + 1;
		ar[++ed] = i;
	}
	ar[ed = 0] = n + 1;
	for (int i = n; i >= 1; i--)
	{
		while (ed && arr[ar[ed]] <= arr[i]) ed--;
		mxrgt[i] = ar[ed] - 1;
		ar[++ed] = i;
	}
	ar[ed = 0] = n + 1;
	for (int i = n; i >= 1; i--)
	{
		while (ed && arr[ar[ed]] >= arr[i]) ed--;
		mirgt[i] = ar[ed] - 1;
		ar[++ed] = i;
	}
	return 0;
}
