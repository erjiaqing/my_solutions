#include <bits/stdc++.h>
//#include <iostream>
using namespace std;
typedef long long ll;
#define rep(i,l,r) for (i=l;i<=r;i++)
#define drep(i,l,r) for (i=l;i>=r;i--)
const int maxn = (1 << 17);
const int P = 786433, t = 6, g = 10;
ll a1[maxn], a2[maxn], Y[maxn], Y2[maxn], Yl[maxn], yl[maxn], y2[maxn], A1[maxn], A2[maxn], A[maxn];
ll i,j,k,l,m,n,o,p,ni[P + 10];
ll Size[5];

inline ll fastpow(ll a, ll b)
{
	ll ret = 1;
	while (b)
	{
		if (b & 1) ret = ret * a % P;
		a = a * a % P;
		b >>= 1;
	}
	return ret;
}
inline ll get(ll n)
{
	return fastpow(g, (P - 1) / n);
}
struct arr
{
	ll a[maxn], y[maxn];
       ll len;
       inline void reset(ll Len)
       {
              len = Len;
			  memset(a, 0, sizeof(a));
			  memset(y, 0, sizeof(y));
       }
       inline void DFT(ll L, ll R)
       {
              ll i,j,k,l1 = 0,l2 = 0,n = R-L+1,w,now;
              if (n == 1) y[L] = a[L];
              else
              {
                  rep(i,L,R)
                  {
                    a1[++l1] = a[i]; i++; a2[++l2] = a[i];
                  }
                  rep(i,1,l1) a[i+L-1] = a1[i];
                  rep(i,1,l2) a[i+L+l1-1] = a2[i];
                              DFT(L,L+l1-1); DFT(R-l2+1,R);
                  rep(i,1,l1)Yl[i] = y[L+i-1];
                  rep(i,1,l2)Y2[i] = y[L+l1+i-1];
                  w = get(n); now = 1;
                  rep(i,1,n/2)
                  {
                     Y[i] = (Yl[i] + (now * Y2[i])%P)%P;
                     now = (now * w) %P;
                  }
                  now = 1; 
                  rep(i,n/2+1,n)
                  {
                     Y[i] = (Yl[i-n/2] - (now * Y2[i-n/2])%P + P)%P;
                     now = (now * w) %P;
                  }
                  rep(i,L,R) y[i] = Y[i-L+1];
              }
       }
       inline void DFTf(ll L, ll R)
       {
              ll i,j,k,l1 = 0,l2 = 0,n = R-L+1,w,now;
              if (n == 1) a[L] = (y[L])%P;
              else
              {
                  rep(i,L,R)
                  {
                    yl[++l1] = y[i]; i++; y2[++l2] = y[i];
                  }
                  rep(i,1,l1) y[i+L-1] = yl[i];
                  rep(i,1,l2) y[i+L+l1-1] = y2[i];
                              DFTf(L,L+l1-1); DFTf(R-l2+1,R);
                  rep(i,1,l1) A1[i] = a[L+i-1];
                  rep(i,1,l2) A2[i] = a[L+l1+i-1];
                  w = get(n); w = ni[w]; now = 1;
                  rep(i,1,n/2)
                  {
                     A[i] = (A1[i] + (now * A2[i])%P)%P;
                     now = (now * w) %P;
                  }
                  now = 1; 
                  rep(i,n/2+1,n)
                  {
                     A[i] = (A1[i-n/2] - (now * A2[i-n/2])%P + P) %P;
                     now = (now * w) %P;
                  }
                  rep(i,L,R)
                  {
                     a[i] = A[i-L+1];
                     if (n == len) a[i] = (a[i] * ni[n])%P;
                  }
              }
       }
       inline void put()
       {
              ll i;
              printf("PUT: ");
              rep(i,0,len-1)
              {
                            if (a[i]!=1)printf("%lld",a[i]);
                            printf("x^%lld",i);
                            if (i<len-1)printf(" + ");
              }
              puts("");
       }
}Ans[17], T[4];
inline void Solve()
{
	int len = 1 << 17;
	scanf("%lld%lld", &n, &k);
//	while (len < n) len <<= 1;
//	len <<= 1;
	k++;
	Ans[1].reset(len);
	Ans[1].a[1] = 1;
	Ans[2].reset(len);
	Ans[2].a[2] = 2;
	Ans[2].a[3] = 1;
//	cerr << Ans[1].len - 1 << endl;
//	cerr << Ans[2].len - 1 << endl;
//	for (int i = 0; i < maxn; i++) cerr << Ans[1].a[i] << " ";
	cerr << endl;
	Ans[1].DFT(0, Ans[1].len - 1);
	Ans[2].DFT(0, Ans[2].len - 1);
	T[0].reset(len);
	T[1].reset(len);
	for (int i = 3; i <= k; i++)
	{
		Ans[i].reset(len);
		for (int j = 0; j < len; j++)
		{
			T[0].y[j] = (Ans[i - 1].y[j] * Ans[i - 1].y[j]) % P;
			T[1].y[j] = (Ans[i - 1].y[j] * Ans[i - 2].y[j]) % P;
		}
		T[0].DFTf(0, T[0].len - 1);
		T[1].DFTf(0, T[1].len - 1);
		for (int j = 0; j < len; j++)
		{
			if (j < len - 1)
				Ans[i].a[j + 1] = (T[0].a[j] + T[1].a[j] * 2) % P;
		}
//		for (int j = 0; j < 20; j++) printf("%3lld ", Ans[i].a[j]);
//		printf("\n");
		Ans[i].DFT(0, Ans[i].len - 1);
	}
	Ans[k].DFTf(0, Ans[k].len - 1);
	printf("%lld\n", Ans[k].a[n]);
}
int main()
{
#ifdef ONLINE_JUDGE
	freopen("avl.in", "r", stdin);
	freopen("avl.out", "w", stdout);
#endif
	for (ll i = 1; i < P; i++)
		ni[i] = fastpow(i, P - 2);
	Solve();
	return 0;
}
