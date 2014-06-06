#include <bits/stdc++.h>
using namespace std;
/*special int*/
/*mod int*/
typedef long long i64d;
const int mod=998244353,maxm=262144*3;
struct Int{
	int a;
	Int (int _a)
	{
		a=_a%mod;
		if (a<0) a+=mod;
	}
	Int (long long _a)
	{
		a=_a%mod;
		if (a<0) a+=mod;
	}
	Int (){}
	Int operator - () const {return Int(-a);}
	friend Int operator + (const Int a,const Int b){return Int(a.a+b.a);}
	friend Int operator - (const Int a,const Int b){return Int(a.a-b.a);}
	friend Int operator * (const Int a,const Int b){return Int((long long)(a.a)*b.a);}
	inline Int div2() const {return Int((i64d(a)*((mod+1)/2)));}
};
inline long long mod_pow(long long a,int k)
{
	long long ret=1;
	while (k)
	{
		if (k&1) (ret*=a)%=mod;
		(a*=a)%=mod;k>>=1;
	}
	return ret;
}
int fft_size;
Int w[maxm],tmp[maxm],fft_a[maxm],fft_b[maxm];
Int ns[maxm],s[maxm],rs[maxm],nrs[maxm];
void fft(Int *t,int s,int d)
/*t=fft(t)*/
{
	if (fft_size==d)
		return;
	fft(t,s,d<<1);
	fft(t,s+d,d<<1);
	for (int i=s,j=s,p=0;i<fft_size/2;i+=d,j+=d<<1,p+=d)
	{
		Int y0(t[j]),y1(t[j+d]);
		tmp[i]=(y0+y1*w[p]);
		tmp[i+fft_size/2]=(y0+y1*w[p+fft_size/2]);
	}
	for (int i=s;i<fft_size;i+=d)
		t[i]=tmp[i];
}
void vector_mult(Int *aa,Int *bb,Int *c,int n)
{
//	Int fft_a=aa,fft_b=bb;
	for (int i=0;i<n;i++)
		fft_a[i]=aa[i],fft_b[i]=bb[i];
	fft_size=1;
	while (fft_size<n) fft_size<<=1;
	fft_size<<=1;
	w[0]=1;
	w[1]=mod_pow(3,(mod-1)/fft_size);
	for (int i=2;i<=fft_size;i++)
		w[i]=w[i-1]*w[1];
	fft(fft_a,0,1);
	fft(fft_b,0,1);
	for (int i=0;i<fft_size;i++)
		(fft_a[i]=fft_a[i]*fft_b[i]);
	for (int i=0;i<fft_size;i++)
		(fft_b[i]=fft_a[i?(fft_size-i):0]);
//	fft_size/=2;
	fft(fft_b,0,1);
	int inv=mod_pow(fft_size,mod-2);
	for (int i=0;i<fft_size;i++)
	{
		c[i]=fft_b[i]*inv;
		fft_a[i]=fft_b[i]=0;
	}
}
void poly_inv(int n,Int *f,Int *s)
{
	for (int i=1;i<n;i++) s[i]=0;s[0]=1;
	for (int m=2;m<=n;m<<=1)
	{
		int h=m>>1;
		for (int i=0;i<m;i++) ns[i]=f[i];
		vector_mult(s,ns,ns,m);
		for (int i=h;i<m;i++) ns[i]=-ns[i];
		vector_mult(s,ns,ns,m);
		for (int i=h;i<m;i++) s[i]=ns[i];
	}
}
void poly_sqrt(int n,Int *f,Int *s)
{
	for (int i=1;i<n;i++) s[i]=rs[i]=0;s[0]=rs[0]=1;
	for (int m=2;m<=n;m<<=1)
	{
		int h=m>>1;
		for (int i=0;i<h;i++) nrs[i]=s[i];
		for (int i=h;i<m;i++) nrs[i]=0;
		vector_mult(rs,nrs,nrs,m);
		for (int i=0;i<h;i++) nrs[i]=0;
		for (int i=h;i<m;i++) nrs[i]=-nrs[i];
		vector_mult(rs,nrs,nrs,m);
		for (int i=0;i<h;i++) nrs[i]=rs[i];
		vector_mult(f,nrs,nrs,m);
		for (int i=h;i<m;i++) s[i]=nrs[i]*((mod+1)/2);
		for (int i=0;i<m;i++) nrs[i]=s[i];
		vector_mult(rs,nrs,nrs,m);
		for (int i=0;i<h;i++) nrs[i]=0;
		for (int i=h;i<m;i++) nrs[i]=-nrs[i];
		vector_mult(rs,nrs,nrs,m);
		for (int i=h;i<m;i++) rs[i]=nrs[i];
	}
}
Int f[maxm],c[maxm],F[maxm];
int main()
{
	int n,m,t,N;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&t),c[t]=-4;
	c[0]=1;
	N=1;
	while (N<=m) N<<=1;
	poly_sqrt(N,c,f);
	(f[0]=f[0]+1);
	for (int i=0;i<N;i++) f[i]=f[i]*((mod+1)/2);
	poly_inv(N,f,F);
	for (int i=1;i<=m;i++)
		printf("%d\n",F[i].a);
	return 0;
}

