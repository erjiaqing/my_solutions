#include <bits/stdc++.h>
using namespace std;
set<long long> s;
int main()
{
#ifdef ONLINE_JUDGE
    freopen("nim.in", "r", stdin);
    freopen("nim.out", "w", stdout);
#endif
    long long curr = 2;
    s.insert(1e16);
    s.insert(2);
    for (long long sq = 1; sq <= 1000000 + 5; sq++)
    {
        long long curr2 = curr + sq + 1;
        while (curr2 < (sq + 1) * (sq + 1))
        {
            s.insert(curr2);
            curr = curr2;
            curr2 = curr + sq + 1;
        }
    }
    long long n;
    cin >> n;
    if ((*s.lower_bound(n)) == n)
        printf("LOSE\n");
    else
        printf("WIN\n");
    return 0;
}
