#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
int q;
void work()
{
	char buf[5];
	vector<long long> t;
	vector<long long> :: iterator it;
	long long num = 0;
	for (int i = 0 ; i < q ; i++)
	{
		scanf("%s" , buf);
		if (buf[0] == 'a')
		{
			scanf("%lld" , &num);
			t.insert(upper_bound(t.begin() , t.end() , num) , num);
		}
		else if (buf[0] == 'd')
		{
			scanf("%lld" , &num);
			t.erase(lower_bound(t.begin() , t.end() , num));
		}
		else if (buf[0] == 's')
		{
			long long ret = 0;
			for (int j = 2 ; j < t.size() ; j += 5)
				ret += t[j];
			printf("%lld\n" , ret);
		}
	}
}
int main()
{
	while (~scanf("%d" , &q))
		work();
	return 0;
}
