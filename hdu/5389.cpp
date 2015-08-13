#include <bits/stdc++.h>
using namespace std;
const int mod = 258280327;
const int maxn = 100000 + 5;
int dp[2][10];
int n , a , b , sum;
void work()
{
    int id = 0;
    scanf("%d%d%d" , &n , &a , &b);
    memset(dp , 0 , sizeof(dp));
    dp[0][0] = 1;
    sum = 0;
    for (int j = 1 ; j <= n ; j++)
    {
        int np = j & 1;
        int n2 = np ^ 1;
        int lsum = sum;
        scanf("%d" , &id);
//        id = id % 9;
        if (id == 0)
            id = 9;
        sum = sum + id;
        memset(dp[np] , 0 , sizeof(dp[np]));
        for (int i = 0 ; i <= 9 ; i++)
        {
            int ni = (i + id - 1) % 9 + 1;
            if (ni == 0)
                ni = 9;
            (dp[np][ni] += dp[n2][i]) %= mod;
            (dp[np][i] += dp[n2][i]) %= mod;
        }
    }
    int ans = 0;
    if (sum % 9 == b % 9)
        ans++;
//    sum = (sum - 1) % 9 + 1;
    ans = (ans + dp[n & 1][a]) % mod;
    printf("%d\n" , ans);
}
int main()
{
    int t;
    scanf("%d" , &t);
    while (t--)
        work();
    return 0;
}
