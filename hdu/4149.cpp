#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define get( _x ) ( 1 << ( _x ) )

void work()
{
	int x[9] , s8 , m = 0 , ts0 = 0 , ts1 = 0 , mask = 0;
	scanf("%d%d%d%d%d%d%d%d%d" , &x[1] , &x[2] , &x[3] , &x[4] , &x[5] , &x[6] , &x[7] , &x[8] , &s8);
	for (int i = 0 ; i < 31 ; i++)
	{
		ts0 = 0 , ts1 = 0;
		mask |= get(i);
		for (int j = 1 ; j <= 8 ; j++)
		{
			ts0 += ((x[j] & mask));
			ts1 += (((x[j] & mask) ^ get(i)));
		}
		if (((s8) & mask) != (ts0 & mask))
		{
			m |= get(i);
			for (int j = 1 ; j <= 8 ; j++)
				x[j] ^= get(i);
			s8 ^= get(i);
		}
	}
	printf("%d\n" , m);
}
int main()
{
	int t;
	scanf("%d" , &t);
	while (t--)
		work();
	return 0;
}

