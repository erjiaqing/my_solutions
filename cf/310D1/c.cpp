#include <bits/stdc++.h>
using namespace std;
const int maxq = (200000 + 5) * 100;
#define ls( _x ) ( Tnodes[_x].l )
#define rs( _x ) ( Tnodes[_x].r )
#define va( _x ) ( Tnodes[_x].m )
struct SegTree{
	int l , r , m;
	SegTree(int _l = 0 , int _r = 0 , int _m = 0):
		l(_l) , r(_r) , m(_m){}
};
SegTree Tnodes[maxq];
int totnodes = 0;
inline int get_id(int &id)
{
	return (id == 0)?(id = ++totnodes):(id);
}
void insert(int &t , int l , int r , int ql , int qr , int val)
{
	if ( ql > qr) return;
	t = get_id(t);
	if ( ql <= l && r <= qr)
	{
		va(t) = max(va(t) , val);
		return;
	}
	int m = (l + r) >> 1;
	if (ql <= m)
		insert(ls(t) , l , m , ql , qr , val);
	if (qr > m)
		insert(rs(t) , m + 1 , r , ql , qr , val);
}
int query(int &t , int l , int r , int q)
{
	if ( t == 0 )
		return 0;
	int ret = va(t),
		m = ( l + r ) >> 1;
	if ( q <= m )
		ret = max(ret , query( ls(t) , l , m , q));
	else
		ret = max(ret , query( rs(t) , m + 1 , r , q));
	return ret;
}
int main()
{
	int TrootL = 0 , TrootR = 0;
	get_id(TrootL);
	get_id(TrootR);
	int n , q;
	int qx , qy;
	char buf[5];
	scanf("%d%d" , &n , &q);
	for (int i = 0 ; i < q ; i++)
	{
		scanf("%d%d%s" , &qx , &qy , buf);
		if (buf[0] == 'U')
		{
			int target = query(TrootL , 1 , n , qx);
			printf("%d\n" , qy - target);
			insert(TrootL , 1 , n , qx , qx , qy);
			insert(TrootR , 1 , n , target + 1 , qy , qx);
		}else if (buf[0] == 'L')
		{
			int target = query(TrootR , 1 , n , qy);
			printf("%d\n" , qx - target);
			insert(TrootL , 1 , n , target + 1 , qx , qy);
			insert(TrootR , 1 , n , qy , qy , qx);
		}
	}
	return 0;
}
