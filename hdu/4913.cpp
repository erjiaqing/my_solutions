#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <vector>
#include <iostream>
using namespace std;
const int mod = 1000000007;
const int maxn = 100000 + 5;
typedef pair<long long,long long> pll;
typedef pair<int,int> pii;
#define a first
#define b second
vector< pii > x;
int b[maxn] , cb , n;
#undef a
#undef b
long long _pow(long long a,int b)
{
	long long ret = 1;
	for ( ; b ; b >>= 1)
	{
		if ( b & 1 ) (ret *= a) %= mod;
		(a *= a) %= mod;
	}
	return ret;
}
#define LOWBIT( _x) ((_x) & (-(_x)))
int bit[maxn << 2];
int get(int p)
{
	int ret = 0;
	for (; p ; p -= LOWBIT( p )) ret += bit[p];
	return ret;
}
void add(int p,int v)
{
	for (; p <= cb ; p += LOWBIT( p )) bit[p] += v;
}
#undef LOWBIT
#define ls( _x) ((_x) << 1)
#define rs( _x) ((_x) << 1 | 1)
#define sum first
#define lazy second
pll seg[maxn << 2];
void push_down(int p)
{
	if (seg[p].lazy != 1)
	{
		( seg[ls(p)].sum *= seg[p].lazy ) %= mod;
		( seg[rs(p)].sum *= seg[p].lazy ) %= mod;
		( seg[ls(p)].lazy *= seg[p].lazy ) %= mod;
		( seg[rs(p)].lazy *= seg[p].lazy ) %= mod;
		seg[p].lazy = 1;
	}
}
void push_up(int p)
{
	seg[p].sum = seg[ls(p)].sum + seg[rs(p)].sum;
	if (seg[p].sum >= mod) seg[p].sum -= mod;
}
void build(int p,int l,int r)
{
	seg[p].sum = 0;
	seg[p].lazy = 1;
	if (l == r)
		return;
	int m = (l + r) >> 1;
	build(ls(p) , l , m);
	build(rs(p) , m + 1 , r);
}
#define b second
void add(int p,int l,int r,int n)
{
	if (l == r)
	{
		seg[p].sum += _pow( 2, get(l)) * _pow( 3, b[l]) % mod;
		if (seg[p].sum >= mod) seg[p].sum -= mod;
		add(l, 1);
		return;
	}
	int m = (l + r) >> 1;
	push_down(p);
	if ( n <= m) add(ls(p) , l , m , n);
	else add(rs(p) , m + 1 , r , n);
	push_up(p);
}
#undef b
void change(int p, int l , int r , int tl , int tr)
{
	if (tr < tl) return;
	if ( tl <= l && r <= tr )
	{
		(seg[p].sum *= 2) %= mod;
		(seg[p].lazy *= 2) %= mod;
		return;
	}
	int m = ( l + r ) >> 1;
	push_down(p);
	if ( tl <= m ) change(ls(p) , l , m , tl , tr);
	if ( tr >  m ) change(rs(p) , m + 1 , r , tl , tr);
	push_up(p);
}
long long sum_up(int p, int l , int r , int tl , int tr)
{
	if ( tl <= l && r <= tr ) return seg[p].sum;
	int m = ( l + r ) >> 1;
	long long ret = 0;
	push_down(p);
	if ( tl <= m ) ret += sum_up(ls(p) , l , m , tl , tr);
	if ( tr >  m ) ret += sum_up(rs(p) , m + 1, r , tl , tr);
	return ret % mod;
}
#undef sum
#undef lazy
#define a first
#define b second
void work()
{
	int ta,tb;
	long long ans = 0;
	for (int i = 0 ; i < n ; i++)
		scanf("%d%d" , &ta , &tb),x.push_back(pii( ta , tb)),
		b[++cb] = tb;
	sort(x.begin() , x.end());
	sort(&b[1] , &b[cb + 1]);
	cb = unique(&b[1] , &b[cb + 1]) - b - 1;
	build(1 , 1 , cb);
	for (int i = 0 ; i < n ; i++)
	{
		int pos = lower_bound(&b[1] , &b[cb + 1] , x[i].b) - b;
		long long tmp;
		tmp = _pow(2 , x[i].a) * ((sum_up(1 , 1 , cb , pos , cb) + _pow(3 , x[i].b)) % mod) % mod;
		ans += tmp;
		if (ans >= mod) ans -= mod;
		int tn = get(pos - 1);
		tmp = _pow(2 , x[i].a) * ( (_pow(2 , tn) - 1) * _pow(3 , x[i].b) % mod ) % mod;
		ans += tmp;
		if (ans >= mod) ans -= mod;
		add(1 , 1 , cb , pos);
		change(1 , 1 , cb , pos + 1 , cb);
	}
	printf("%lld\n" , ans);
}
void reset()
{
	cb = 0;
	x.clear();
	memset(bit , 0 , sizeof(bit));
	memset(b , 0 , sizeof(b));
}
#undef a
#undef b
int main()
{
	while (~scanf("%d" , &n))
	{
		work();
		reset();
	}
	return 0;
}
