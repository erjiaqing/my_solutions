#include <bits/stdc++.h>
using namespace std;
const int maxn = 200000 + 5;
int ans[maxn][2];
int a[maxn];
int n;
char buf[maxn];
void work(int caseno)
{
    scanf("%s" , buf + 1);
    n = strlen(buf + 1);
    for (int i = 1 ; i <= n ; i++)
        scanf("%d" , &a[i]);
    buf[0] = '0';
    memset(ans , 0x80 , sizeof(ans));
    ans[0][0] = 0;
    for (int i = 1 ; i <= n ; i++)
    {
        if (buf[i] == '?')
        {
            ans[i][0] = max(ans[i - 1][0] , ans[i - 1][1] + a[i]);
            ans[i][1] = max(ans[i - 1][1] , ans[i - 1][0] + a[i]);
        }
        int ta = buf[i] - '0';
        if (ta == 0)
            ans[i][0] = max(ans[i - 1][0] , ans[i - 1][1] + a[i]);
        if (ta == 1)
            ans[i][1] = max(ans[i - 1][1] , ans[i - 1][0] + a[i]);
    }
    printf("Case #%d: %d\n" , caseno , max(ans[n][0] , ans[n][1]));
}
int main()
{
    int t;
    scanf("%d" , &t);
    for (int i = 1 ; i <= t ; i++)
        work(i);
    return 0;
}
