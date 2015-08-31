#include <bits/stdc++.h>
using namespace std;
const int maxn = 300 + 5;
typedef pair<int, int> pii;
#define x first
#define y second
int ans = 0;
int cross(const pii &a, const pii &b)
{
    return a.x * b.y - a.y * b.x;
}
pii p[maxn];
int main()
{
#ifdef ONLINE_JUDGE
    freopen("cottages.in", "r", stdin);
    freopen("cottages.out", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> p[i].x >> p[i].y;
    sort(&p[0], &p[n]);
    int cnt = unique(&p[0], &p[n]) - &p[0];
    for (int i = 0; i < cnt; i++)
        for (int j = i + 1; j < cnt; j++)
        {
            pii tp(p[i].x - p[j].x, p[i].y - p[j].y);
            bool flg = true;
            for (int k = 0; k < cnt; k++)
            {
                pii tp1(p[k].x - p[i].x, p[k].y - p[i].y);
                if (k == i || k == j) continue;
                if (cross(tp1, tp) == 0)
                {
                    if ((p[i].x <= p[k].x && p[k].x <= p[j].x) && (min(p[i].y,p[j].y) <= p[k].y && p[k].y <= max(p[i].y,p[j].y)) )
                    {
                        flg = false;
                        break;
                    }
                }
            }
            ans += flg;
        }
    cout << ans * 2 << endl;
    return 0;
}
