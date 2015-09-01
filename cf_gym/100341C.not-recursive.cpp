#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
const int mod = 786433;
long long w[131075],INTs[18][131075];
long long x[131075];
long long w1[131075];
long long frac[65536];
//int maxsize[20];
int t = 6, g = 10;
int inv[mod];
int rev[18][131075];
inline long long fastpow(long long a, long long b)
{
	long long ret = 1;
	while (b)
	{
		if (b & 1) ret = ret * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ret;
}
inline long long get(long long n)
{
	if (w1[n]) return w1[n];
	return w1[n] = fastpow(g, (mod - 1) / n);
}
inline long long get_inv(long long n)
{
	if (inv[n]) return inv[n];
	return inv[n] = fastpow(n, mod - 2);
}
int totBit=17,M=65536;
int bit_rev(int a,int m) //Rev m bits
{
	int t=0;
	while (m--)
	{
		t<<=1;
		t|=a&1;
		a>>=1;
	}
	return t;
}
void init_w(int size,int dir)
{
	int i;
	if (dir==1)
	{
		w[1] = get(size);
		w[0] = 1;
		for (i=2;i<size;i<<=1)
		{
			w[i]=w[i/2] * w[i/2] % mod;
		}
	}else
	{
		w[0] = 1;
		w[1] = get_inv(get(size));;
		for (i=2;i<size;i<<=1)
		{
			w[i]=w[i/2] * w[i/2] % mod;
		}
	}
}
void bit_reverse_copy(long long which[],int size,int m)
{
	int i,j;
	long long tmp;
	int *revarr = rev[m];
	for (i=0;i<size;i++)
	{
		j=revarr[i];
		if (j>i)
			swap(which[i], which[j]);
	}
}
void fft_ifft_common(int size,long long which[],int flg = false)
{
	int i,j,m;
	long long high,low;
	i=size;
	m=0;
	while (i)
	{
		m++;
		i>>=1;
	}
	bit_reverse_copy(which,size,m-1);
	int group_num=size/2;
	int group_len=2;
	int group_step=1;
	while (m--)
	{
		for (i=0;i<group_num;i++)
		{
			long long ww = w[group_num];
			long long www = 1;
			int group_start=i*group_len;
			for (j=0;j<group_step;j++)
			{
				int a=group_start+j;
				int b=group_start+j+group_step;
				high=which[a];
				low=which[b] * www % mod;
				which[a] = (high+low) % mod;
				which[b] = ((high-low) % mod + mod) % mod;
				www = www * ww % mod;
			}
		}
		group_num>>=1;
		group_len<<=1;
		group_step<<=1;
	}
}
void fft(long long which[],int len)
{
	init_w(len,1);
	fft_ifft_common(len,which);
}
void ifft(long long which[],int len)
{
	int i;
	init_w(len,-1);
	fft_ifft_common(len,which,true);
	for (i=0;i<len;i++)
	{
		(which[i]*=get_inv(len)) %= mod;
	}
}
int n, k;
void solve()
{
	int fftsize = 131072;
	int maxsize = 0;
	int m = 0, tm;
	long long *i_1, *i_2, *t1, *t2, *th;
//	while(fftsize < n * 2) fftsize <<= 1;
	tm = fftsize;
	while (tm)
	{
		m++;
		tm>>=1;
	}
	x[1] = 1;
	INTs[0][1] = 1;
	INTs[1][2] = 2;
	INTs[1][3] = 1;
	fft(INTs[0], fftsize);
	fft(INTs[1], fftsize);
	fft(x, fftsize);
	for (int i = 2; i <= k; i++)
	{
		t1 = INTs[16];
		t2 = INTs[17];
		i_1 = INTs[i - 1];
		i_2 = INTs[i - 2];
		th = INTs[i];
		for (int j = 0; j < fftsize; j++)
		{
			t1[j] = i_1[j] * i_1[j] % mod;
			t2[j] = i_1[j] * i_2[j] % mod;
		}
		for (int j = 0; j < fftsize; j++)
			th[j] = ((t1[j] + t2[j] * 2) % mod) * x[j] % mod;
	}
	ifft(INTs[k], fftsize);
	printf("%lld\n", (INTs[k][n] % mod + mod) % mod);
}
int main()
{
#ifdef ONLINE_JUDGE
	freopen("avl.in", "r", stdin);
	freopen("avl.out", "w", stdout);
#endif
	for (int i = 0; i < 18; i++)
		for (int j = 0; j < 131072; j++)
			rev[i][j] = bit_rev(j ,i);
	scanf("%d%d", &n, &k);
	inv[n] = fastpow(n, mod - 2);
	solve();
	return 0;
}
