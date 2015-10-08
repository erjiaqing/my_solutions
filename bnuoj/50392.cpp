#include <cstdio>
#include <cmath>
using namespace std;
int n;
bool sol()
{
	int a;
	bool ret = true;
	while (n--)
	{
		scanf("%d", &a);
		int b = sqrt(a);
		ret = ret && (b * b == a);
	}
	return ret;
}
int main()
{
	while (~scanf("%d", &n))
		printf("%s\n", sol() ? "Yes" : "No");
	return 0;
}
