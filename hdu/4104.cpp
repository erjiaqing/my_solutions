#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
bool work()
{
	int n , t , a = 0;
	if (scanf("%d" , &n) != 1) return false;
	vector <int> v;
	for (int i = 0 ; i < n ; i++)
		scanf("%d" , &t) , v.push_back(t);
	sort(v.begin() , v.end());
	for (int i = 0 ; i < n ; i++)
	{
		if (v[i] > a + 1)
		{
			printf("%d\n" , a + 1);
			return true;
		}
		a += v[i];
	}
	printf("%d\n" , a + 1);
	return true;
}
int main()
{
	while (work());
	return 0;
}
