#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
const int maxn = 20000 + 1;
struct complex
{
	double real,imag;
}w[262150],INTs[2][262150];
long long dataa[262150],datab[262150], delta[262150];
long long ans[262150];
complex operator + (complex c1,complex c2)
{
	complex ret={c1.real+c2.real,c1.imag+c2.imag};
	return ret;
}
complex operator * (complex c1,complex c2)
{
	complex ret={c1.real*c2.real-c1.imag*c2.imag,c1.real*c2.imag+c1.imag*c2.real};
	return ret;
}
complex operator - (complex c1,complex c2)
{
	complex ret={c1.real-c2.real,c1.imag-c2.imag};
	return ret;
}
const double __PI__=3.141592653589793;
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
		for (i=0;i<size;i++)
		{
			w[i].real=cos(2*__PI__*i/size);
			w[i].imag=-sin(2*__PI__*i/size);
		}
	}else
	{
		for (i=0;i<size;i++)
		{
			w[i].real=cos(2*__PI__*(-i)/size);
			w[i].imag=-sin(2*__PI__*(-i)/size);
		}
	}
}
void bit_reverse_copy(int which,int size,int m)
{
	int i,j;
	complex tmp;
	for (i=0;i<size;i++)
	{
		j=bit_rev(i,m);
		if (j>i)
		{
			tmp=INTs[which][i];
			INTs[which][i]=INTs[which][j];
			INTs[which][j]=tmp;
		}
	}
}
void fft_ifft_common(int size,int which)
{
	int i,j,m;
	complex high,low;
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
			int group_start=i*group_len;
			for (j=0;j<group_step;j++)
			{
				int a=group_start+j;
				int b=group_start+j+group_step;
				high=INTs[which][a];
				low=INTs[which][b]*w[j*group_num];
				INTs[which][a]=high+low;
				INTs[which][b]=high-low;
			}
		}
		group_num>>=1;
		group_len<<=1;
		group_step<<=1;
	}
}
void fft(int which,int len)
{
	init_w(len,1);
	fft_ifft_common(len,which);
}
void ifft(int which,int len)
{
	int i;
	init_w(len,-1);
	fft_ifft_common(len,which);
	for (i=0;i<len;i++)
	{
		INTs[which][i].real/=len;
		INTs[which][i].imag/=len;
	}
}
long long work()
{
	int n, m, l = 1;
	scanf("%d%d", &n, &m);
	memset(INTs, 0, sizeof(INTs));
	for (int i = 0 ; i < n; i++) scanf("%lld", &dataa[i]), INTs[0][i].real = dataa[i];
	for (int i = 0 ; i < m; i++) scanf("%lld", &datab[i]), INTs[1][m - i - 1].real = datab[i];
	while (l < n || l < m) l <<= 1;
	l <<= 1;
	fft(0, l);
	fft(1, l);
	for (int i = 0; i < l; i++)
		INTs[0][i] = INTs[0][i] * INTs[1][i];
	ifft(0, l);
	for (int i = 0; i < l; i++)
		delta[i] = round(INTs[0][i].real);
	long long ans = 0;
	for (int i = 0; i <= n - m; i++)
		ans = max(ans, delta[m + i - 1]);
	return ans;
}
int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++)
		printf("Case #%d: %lld\n", i, work());
	return 0;
}

/*
 * Problem:
 * Given two vectors A_1 .. A_n, B_1 .. B_m, n >= m
 * Find k, to make [A_k .. A_{k+m-1}] . [B_1 .. B_m] max.
 * 0 < m, n, A_i, B_i < 1e5
 * Sample Input:
 * 3
 * 4 2
 * 10 20 30 20
 * 30 20
 * 4 3
 * 1 0 0 0
 * 0 1 0
 * 4 2
 * 1 0 0 0
 * 0 1
 *
 * Sample Output:
 * 1300
 * 0
 * 0
 */
