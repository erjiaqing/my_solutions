#include <cstdio>
using namespace std;
const long long mod = 1000000007;
long long epow(long long a , long long b)
{
    long long ret = 1;
    while (b)
    {
        if (b & 1)
            ret = ret * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ret;
}
int main()
{
    int t , p;
    scanf("%d" , &t);
    while (t--)
    {
        scanf("%d" , &p);
        printf("%lld\n" , ((epow(2 , p - 1) - 1) % mod + mod) % mod);
    }
    return 0;
}