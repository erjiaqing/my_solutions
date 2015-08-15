/*
 * CF::GYM 100203D
 * Author: EJQ
 */
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <map>
using namespace std;
const int maxn = 10000 + 5 , maxk = 100 + 5;
const long long md = 101;
unsigned long long ha[maxn];
int s[maxn][maxk];
int rs[maxk];
int n , k;
map<int , int> app;
void work()
{
    memset(ha , 0 , sizeof(ha));
    scanf("%d%d" , &n , &k);
    for (int i = 0 ; i < n ; i++)
    {
        for (int j = 0 ; j < k ; j++)
        {
            scanf("%d" , &s[i][j]);
            rs[j] = 0;
        }
        app.clear();
        for (int j = 1 ; j <= k ; j++)
        {
            if (app[s[i][j - 1]])
                rs[app[s[i][j - 1]] - 1] = j;
            app[s[i][j - 1]] = j;
        }
        for (int j = 1 ; j <= k ; j++)
        {
            if (app[s[i][j - 1]])
                rs[app[s[i][j - 1]] - 1] = j;
            app[s[i][j - 1]] = j;
        }
        for (int j = 0 ; j < k ; j++)
            rs[j] = ((rs[j] - 1 - j) % k + k) % k;
        int mi = 0 , mj = 1 , mk = 0 , mt = 0;
        while (mi < k && mj < k && mk < k)
        {
            mt = rs[(mi + mk) >= k ? mi + mk - k : mi + mk] - 
                rs[(mj + mk) >= k ? mj + mk - k : mj + mk];
            if (!mt)
                mk++;
            else
            {
                if (mt > 0) mi = mi + mk + 1;
                else mj = mj + mk + 1;
                if (mi == mj) mj ++;
                mk = 0;
            }
        }
        mk = (mi < mj) ? mi : mj;
        for (int p = 0 ; p < k ; p++)
            ha[i] = ha[i] * md + rs[( mk + p ) % k] + 1;
    }
    sort(&ha[0] , &ha[n]);
    int ans = unique(&ha[0] , &ha[n]) - &ha[0];
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

