#include <bits/stdc++.h>
using namespace std;
multiset<long long> s;
multiset<long long>::iterator si , s2;
long long currmin = 0x7fffffffffffffffll;
long long ncurrmin = 0x7fffffffffffffffll;
int main()
{
    long long a , b , c;
    long long ans = 1;
    cin >> a >> b >> c;
    s.insert(a);
    si = s.lower_bound(b);
    if (si != s.end())
    {
        if (*si == b)
        {
            cout << 1 << endl;
            return 0;
        }
        currmin = min(currmin , *si - b);
    }
    if (si != s.begin())
    {
        si--;
        if (*si == b)
        {
            cout << 1 << endl;
            return 0;
        }
        currmin = min(currmin , b - *si);
    }
    s.insert(b);
    //--
    si = s.lower_bound(c);
    if (si != s.end())
    {
        if (*si == c)
        {
            cout << 1 << endl;
            return 0;
        }
        currmin = min(currmin , *si - c);
    }
    if (si != s.begin())
    {
        si--;
        if (*si == c)
        {
            cout << 1 << endl;
            return 0;
        }
        currmin = min(currmin , c - *si);
    }
    s.insert(c);
    while (1)
    {
        s.insert(currmin);
        ans++;
        si = s2 = s.lower_bound(currmin);
        ncurrmin = currmin;
        if ((++si) != s.end())
            ncurrmin = min(ncurrmin , *si - currmin);
        if (s2 != s.begin())
        {
            s2--;
            ncurrmin = min(ncurrmin , currmin - *s2);
        }
        if (ncurrmin == 0)
        {
            cout << ans << endl;
            break;
        }
        currmin = ncurrmin;
    }
    return 0;
}
