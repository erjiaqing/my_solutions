#include <bits/stdc++.h>
using namespace std;
int getmid(int l, int r)
{
    int cnt = r - l;
    int ret = (cnt / 3) + (cnt % 3);
    return ret;
}
int main()
{
    int n , s , t;
    cin >> n >> s >> t;
    if (s > t) swap(s , t);
    int x , k , y;
    x = (s - 1);
    k = (t - s) - 1;
    y = (n - t);
    if (x && y)
    {
        if (k == 0)
            return 0 & printf("-1\n");
        if (k == 1)
            return 0 & printf("2\n");
        else
            return 0 & printf("%d\n" , 2 + getmid(s + 1 , t - 1));
    }
    if (x == 0 && y == 0)
        return 0 & printf("%d\n" , getmid(s , t));
    else
    {
        if (k == 0)
            return 0 & printf("1\n");
        return 0 & printf("%d\n" , 1 + getmid(s , t - 1));
    }
    return 0;
}
