#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int arr[101];
void sol()
{
	int n, m, t, ai;
	scanf("%d%d", &n, &m);
	memset(arr, -1, sizeof(arr));
	int A, B;
	int aa, bb;
	while (m--)
	{
		scanf("%d%d", &t, &ai);
		arr[t] = ai;
	}
	int last = 0;
	A = B = 0;
	for (int i = n; i >= 3; i--)
	{
		if (arr[i] == -1) arr[i] = last;
		else last = arr[i];
		B += arr[i];
	}
	if (arr[1] == -1) arr[1] = 100;
	if (arr[2] == -1) arr[2] = arr[1];
	A = arr[1] + arr[2];
	aa = A;
	bb = A + B;
	int gg = __gcd(aa, bb);
	aa /= gg;
	bb /= gg;
	printf("%d/%d\n", aa, bb);
	return;
}
int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
		sol();
	return 0;
}
