#include <bits/stdc++.h>
using namespace std;
typedef pair<long long, long long> pll;
vector<pll> pts, pt2;

int n;
#define x first
#define y second
long long det(const pll &a, const pll &b)
{
    return (a.x * b.y - a.y * b.x);
}
long long dot(const pll &a, const pll &b)
{
    return a.x * b.x + a.y * b.y;
}
bool comp(const pll &a, const pll &b)
{
	if (a.y == 0 && b.y == 0 && a.x * b.x <= 0) return a.x > b.x;
	if (a.y == 0 && a.x >= 0 && b.y != 0) return true; // a on x+
	if (b.y == 0 && b.x >= 0 && a.y != 0) return false; // b on x+
	if (b.y * a.y <= 0) return a.y > b.y; // 1.2. vs. 3.4.
	return det(a, b) > 0 || (det(a, b) == 0 && a.x < b.x); // a.b.o shares a line
}
pll _(const pll &a, const pll &b)
{
    return pll(a.x - b.x, a.y - b.y);
}
void sol()
{
    pts.clear();
    for (int i = 0; i < n; i++)
    {
        long long tx, ty;
        scanf("%lld%lld", &tx, &ty);
        pts.push_back(pll(tx, ty));
    }
	sort(pts.begin(), pts.end());
    //pt2.insert(pt2.end(), pts.begin(), pts.end());
    long long ans = 0;
    long long shline = 0;
    for (int i = 0; i < n; i++)
    {
        pt2.clear();
        for (int j = 0; j < n; j++)
        {
            if (i == j) continue;
            pt2.push_back(_(pts[j], pts[i]));
        }
        sort(pt2.begin(), pt2.end(), comp);
        //---

        int curl = 1, curr = 1, shareline = 0;
        for (int j = 0; j < n - 1; j++)
        {
            if (curl <= j) curl = j + 1;
            if (curr <= j) curr = j + 1;
            while(curl < n - 1 && dot(pt2[j], pt2[curl]) > 0 && det(pt2[j], pt2[curl]) >= 0)
                curl++;
            curr = max(curr, curl);
            while (curr < n - 1 && ((det(pt2[j], pt2[curr])) >= 0 || dot(pt2[j], pt2[curr])<= 0))
                curr++;
            ans += curr - curl;
			assert(curr >= curl);
			assert(curr - curl <= n - 1 - j);
//			printf("%d  --- %d %d\n", j, curl, curr);
        }
    }
    long long lln = n;
//	cerr << ans << ' ' << n << ' ' << lln * (lln - 1ll) * (lln - 2ll) / 6 << endl;
//	assert(ans <= lln * (lln - 1ll) * (lln - 2ll) / 6);
    ans = lln * (lln - 1ll) * (lln - 2ll) / 6 - ans;
    printf("%lld\n", ans);
}

int main()
{
    while (~scanf("%d", &n))
        sol();
    return 0;
}
