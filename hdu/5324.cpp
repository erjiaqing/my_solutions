#include <bits/stdc++.h>
using namespace std;
typedef pair<unsigned short , unsigned short> pii;
const int maxn = 50000 + 5;
pair<int ,int> a[maxn] , b[maxn];
//int na[maxn] , nb[maxn];
int r[maxn] , f[maxn] , ans[maxn] , ans_end;
struct Node
{
	pii v;
	int ls , rs;
}N[maxn * 95];
int bit[maxn];
int tn = 0 , n;
void update(int x)
{
	if (N[x].ls == 0)
		N[x].v = N[N[x].rs].v;
	else if (N[x].rs == 0)
		N[x].v = N[N[x].ls].v;
	else
		N[x].v = max(N[N[x].ls].v , N[N[x].rs].v);
}
void insert(int &rt , int l , int r , int y , int v , int id)
{
	if (rt == 0)
		rt = ++tn;
	if (l == r)
	{
		N[rt].v = make_pair(v , id);
		return;
	}
	int mid = (l + r) / 2;
	if (y <= mid)
		insert(N[rt].ls , l , mid , y , v , id);
	else
		insert(N[rt].rs , mid + 1 , r , y , v , id);
	update(rt);
}
#define low_bit( _x ) ( ( _x ) & ( - ( _x ) ) )
void insert(int x , int y , int v , int id)
{
	for ( ; x <= n ; x += low_bit(x))
		insert(bit[x] , 1 , n , y , v , id);
}
pii query(int rt , int l , int r , int ql , int qr)
{
	if (rt == 0)
		return pii(0 , 0);
	if (ql <= l && r <= qr)
		return N[rt].v;
	int mid = ( l + r ) / 2;
	pii ret(0 , 0);
	if (ql <= mid)
		ret = max(ret , query(N[rt].ls , l , mid , ql , qr));
	if (mid < qr)
		ret = max(ret , query(N[rt].rs , mid + 1 , r , ql , qr));
	return ret;
}
pii query(int x , int y)
{
	pii ret(0 , 0);
	for ( ; x ; x -= low_bit(x))
		ret = max(ret , query(bit[x] , 1 , n , 1 , y));
	return ret;
}
void work()
{
	memset(r , 0 , sizeof(r));
	memset(f , 0 , sizeof(f));
	memset(N , 0 , sizeof(N));
	memset(bit , 0 , sizeof(bit));
	tn = 0;ans_end = 0;
	for (int i = 1 ; i <= n ; i++)
	{
		cin >> a[i].first;
		a[i].first = 1000000001 - a[i].first;
		a[i].second = i;
	}
	for (int i = 1 ; i <= n ; i++)
	{
		cin >> b[i].first;
		b[i].second = i;
	}
	sort(&a[1] , &a[n + 1]);
	sort(&b[1] , &b[n + 1]);
	for (int i = 1 ; i <= n ; i++)
	{
		a[a[i].second].first = i;
		b[b[i].second].first = i;
	}
	ans_end = 0;
	for (int i = n ; i > 0 ; i--)
	{
		pii tr = query(n - a[i].first + 1 , n - b[i].first + 1);
		r[i] = tr.first + 1;
		f[i] = 60000 - tr.second;
		insert(n - a[i].first + 1 , n - b[i].first + 1 , r[i] , 60000 - i);
		if (r[i] >= r[ans_end])
			ans_end = i;
	}
	int u = ans_end , l = 0;
//	cerr << tn << endl;
	for ( ; u != 60000 ; u = f[u])
		ans[++l] = u;
	cout << l << endl;
	for (int i = 1 ; i <= l ; i++)
		cout << ans[i] << ( i == l ? "\n" : " ");
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("1009.in" , "r" , stdin);
	freopen("1009.ans" , "w" , stdout);
#endif
	ios::sync_with_stdio(0);
	while (cin >> n)
		work();
	return 0;
}
