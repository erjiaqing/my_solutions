#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
const int maxn = 100000 + 5;
typedef pair<pair<int , int> , int> pii;
vector<pii> v;
set<pair<int , int> > s;
typedef set<pair<int , int> >::iterator spiii;
int l[maxn] , r[maxn] , a[maxn] , mk[maxn] , ta;
int n;
void work()
{
    v.clear();
    s.clear();
    memset(mk , 0 , sizeof(mk));
    ta = 0;
    scanf("%d" , &n);
    for (int i = 1 ; i <= n ; i++)
        scanf("%d" , &l[i]);
    for (int i = 1 ; i <= n ; i++)
        scanf("%d" , &r[i]);
    for (int i = 1 ; i <= n ; i++)
        v.push_back(pii(make_pair(l[i], r[i]) , i));
    sort(v.begin() , v.end());
    int ans = 0 , j = 0;
    for (int i = 0 ; i < n ; i++)
    {
        while (j < n && v[j].x.x <= ans)
        {
            s.insert(make_pair(v[j].x.y , v[j].y));
            j++;
        }
        spiii rr = s.lower_bound(make_pair(ans , -1));
        if (rr != s.end())
        {
            ans++;
            a[ta++] = rr -> y;
            mk[rr -> y] = 1;
            s.erase(rr);
        }
    }
    for (int i = 1 ; i <= n ; i++)
        if (!mk[i])
            a[ta++] = i;
    printf("%d\n" , ans);
    for (int i = 0 ; i < n ; i++)
        printf("%d%s" , a[i] , (i == n - 1 ? "\n" : " "));
}
int main()
{
    int t;
	scanf("%d" , &t);
    while (t--)
        work();
    return 0;
}
