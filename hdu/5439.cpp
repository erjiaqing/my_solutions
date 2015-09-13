#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int maxn = 1000000 + 1;
const int maxquery = 2000 + 1;
const long long mod = 1000000007;
int p[maxn];
long long lst[maxn];
pii q[maxquery];
long long ans[maxquery];
long long currans = 0;
#define x first
#define y second
int main()
{
    p[1] = 1;
    p[2] = 2;
    p[3] = 2;
    lst[1] = 1;
    lst[2] = 3;
    int tot = 3;
    for (int i = 3; i <= maxn; i++)
    {
        lst[i] = lst[i - 1] + p[i];
        for (int j = 0; tot < maxn - 1 && j < p[i]; j++)
            p[++tot] = i;
    }
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++)
    {
        scanf("%d", &q[i].x);
        q[i].y = i;
    }
    sort(&q[0], &q[t]);
    int currpos = 0;
    for (int i = 1; i < maxn; i++)
    {
        long long tq = (lst[i] - lst[i - 1]) * (lst[i] + lst[i - 1] + 1) / 2;
        tq %= mod;
        (currans += tq * i) %= mod;
        while (currpos < t && q[currpos].x >= lst[i] && q[currpos].x < lst[i + 1])
        {
            long long qs = (q[currpos].x + lst[i] + 1) * (q[currpos].x - lst[i]) / 2;
            qs = (qs * (i + 1)) % mod;
            ans[q[currpos].y] = (currans + qs) % mod;
            currpos++;
        }
    }
    for (int i = 0; i < t; i++)
        printf("%lld\n", ans[i]);
    return 0;
}
