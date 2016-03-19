#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 1e6 + 10;

bool test[maxn];
long long p[maxn], ct = 0;

void prime()
{
    for (int i = 2 ; i < maxn ; i++)
    {
        if (test[i])
            continue;
        for (int j = i ; j < maxn ; j+=i)
            test[j] = true;
        p[ct++] = i;
    }
}

bool check(long long a, long long b)
{
	for (int i = 0 ; i < ct ; i++)
	{
		if (p[i] * p[i] > max(a, b))
			break;
		bool x = ((a % p[i]) == 0);
		bool y = ((b % p[i]) == 0);
		while (a % p[i] == 0) a /= p[i];
		while (b % p[i] == 0) b /= p[i];
		if (x && !y)
			return false;
	}
	return (a == 1) || (b % a == 0);
}


int main()
{
    prime();
    int t;
    scanf("%d", &t);
    for (int i = 1 ; i <= t ; i++)
    {
        long long a, b;
        scanf("%lld%lld", &a, &b);
        printf("Case #%d: %s", i, check(a, b) ? "YES\n" : "NO\n");
    }
    return 0;
}
