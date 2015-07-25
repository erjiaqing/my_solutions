#include <cstdio>
using namespace std;
const int maxn = 20 + 5;
int n , c = 0;
int arr[maxn];
inline int abs(int x)
{
	return x < 0 ? -x : x;
}
bool check()
{
	bool flag = true;
	for (int i = 0 ; i < n - 1; i++)
		flag = flag && (arr[i] == arr[i + 1]);
	arr[n] = arr[0];
	for (int i = 0 ; i < n ; i++)
		arr[i] = abs(arr[i] - arr[i + 1]);
	return flag;
}
void work(int caseno)
{
	int ans = 0;
	for (int i = 0 ; i < n ; i++)
		scanf("%d" , &arr[i]);
	for ( ; ans <= 1000 ; ans++)
		if (check())
			break;
	if (ans <= 1000)
		printf("Case %d: %d iterations\n" , caseno , ans);
	else
		printf("Case %d: not attained\n" , caseno);
}
int main()
{
	int t = 0;
	while ((~scanf("%d" , &n)) && n)
		work(++t);
}
