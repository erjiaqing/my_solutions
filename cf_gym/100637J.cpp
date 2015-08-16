#include <bits/stdc++.h>
using namespace std;
long long gcd(long long a , long long b)
{
    return b == 0 ? a : gcd(b , a % b);
}
int main()
{
    long long p , q;
    cin >> p >> q;
    for (int i = 1 ; i <= 1e6 ; i++)
    {
        p *= i;
        long long pg = gcd(p , q);
        p /= pg;
        q /= pg;
        printf("%s%lld" , i == 1 ? "" : " " , p / q);
        p %= q;
        if (p == 0)
            break;
    }
    return 0;
}
