#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const long double phi = (1 + sqrt(5)) / 2;
long long a , b;
long long ansa , ansb;
long long k , ak , ak1 , bk , bk1;
bool flg = false;
long long get_b(long long tk)
{
	return tk * phi + tk;
}
long long get_a(long long tk)
{
	return tk * phi;
}
void work()
{
	flg = false;
	if (b < a)
	{
		swap(a , b);
		flg = true;
	}
	if (a <= 3)
	{
		if (a == 3)
		{
			if (b == 3)
				printf("2\n");
			else
			{
				if (flg)
					printf("1 %lld 0\n" , b - 3);
				else
					printf("1 0 %lld\n" , b - 3);
			}
		}
		if (a == 2)
		{
			if (flg)
				printf("1 %lld 0\n" , b - 1);
			else
				printf("1 0 %lld\n" , b - 1);
		}
		return;
	}
	if (a == b)
	{
		printf("1 %lld %lld\n" , a - 3 , b - 3);
		return;
	}
	if (b == a + 1)
	{
		printf("1 %lld %lld\n" , a - 1 , a - 1);
		return;
	}
	a--;
	b--;
//	long long n = 0;
	long long k0 = 0;
	for (long long i = 1ll << 40 ; i > 0 ; i >>= 1)
	{
		long long rb = get_b(k0 + i);
		if (rb <= a)
		{
			k0 += i;
		}
	}
	if (get_b(k0) == a)
	{
		if (get_a(k0) == b)
		{
			printf("2\n");
			return;
		}
		long long ansa = 0;
		long long ansb = b - get_a(k0);
		if (flg)
			swap(ansa , ansb);
		printf("1 %lld %lld\n" , ansa , ansb);
		return;
	}
	//--
	k0 = 0;
	for (long long i = 1ll << 40 ; i > 0 ; i >>= 1)
	{
		long long ra = get_a(k0 + i);
		if (ra <= a)
		{
			k0 += i;
		}
	}
	if (get_a(k0) == a)
	{
		if (get_b(k0) == b)
		{
			printf("2\n");
			return;
		}
		if (get_b(k0) < b)
		{
			long long ansa = 0;
			long long ansb = b - get_b(k0);
			if (flg) 
				swap(ansa , ansb);
			printf("1 %lld %lld\n" , ansa , ansb);
			return;
		}
	}
	k0 = a;
	for (long long i = 1ll << 40 ; i ; i >>= 1)
	{
		if (k0 - i <= 0)
			continue;
		long long ra = get_a(k0 - i);
		long long rb = get_b(k0 - i);
		long long delta = a - ra;
		//cerr << k0 + i << " " << ra << " " << rb << endl;
		if (b - delta <= rb)
			k0 -= i;
	}
	ansa = a - get_a(k0);
	printf("1 %lld %lld\n" , ansa , ansa);
	return;
}
int main()
{
	int t;
	scanf("%d" , &t);
	while (~scanf("%lld%lld" , &a , &b))
		work();
	return 0;
}
