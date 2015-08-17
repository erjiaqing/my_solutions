#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;
int t , n;
long long powmod(long long a , int b , int p)
{
	long long r = 1;
	while (b)
	{
		if (b & 1)
			r = r * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return r;
}
bool check_prime(int n)
{
	for (int i = 0 ; i < 40 ; i++)
	{
		int a = rand() % (n - 3) + 2;
		if (powmod(a , n - 1 , n) != 1)
			return false;
	}
	return true;
}
void work()
{
	if (n == 2)
		printf("1\n");
	else if (n == 3)
		printf("2\n");
	else if (n == 4)
		printf("2\n");
	else
		printf("%d\n" , check_prime(n) * (n - 1));
}
int main()
{
	scanf("%d" , &t);
	while (t--)
	{
		scanf("%d" , &n);
		work();
	}
	return 0;
}
