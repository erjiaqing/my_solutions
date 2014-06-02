#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
const int maxn=100005,M=131072;
int n,k;
int rk[maxn],hi[maxn],tp[maxn],sa[maxn];
int bi[262150];
unsigned long long hash[maxn];
unsigned long long hash2[maxn];
unsigned long long hash3[maxn];
char str[maxn];
vector<pair<int,int> >ANS;
bool comp(int i,int j)
{
	if (rk[i] != rk[j])
		return rk[i]<rk[j];
	int ri =(( i+k <=n)?rk[i+k]:-1);
	int rj =(( j+k <=n)?rk[j+k]:-1);
	return ri<rj;
}
void calc()
{
	n=strlen(str);
	for (int i=0;i<=n;i++)
	{
		sa[i]=i;
		rk[i]=i<n?str[i]:-1;
	}
	for (k=1;k<=n;k*=2)
	{
		sort(&sa[0],&sa[n+1],comp);
		tp[sa[0]]=0;
		for (int i=1;i<=n;i++)
			tp[sa[i]]=tp[sa[i-1]]+(comp(sa[i-1],sa[i])?1:0);
		for (int i=0;i<=n;i++)
			rk[i]=tp[i];
	}
	int i,j,k=0;
	for (i=1;i<=n;i++) rk[sa[i]]=i;
	for (i=0;i<n;hi[rk[i++]]=k)
		for (k?k--:0,j=sa[rk[i]-1];str[i+k]==str[j+k];k++);
}
int segmin(int l,int r)
{
	int ans=n+n;
	l=l+M-1;r=r+M+1;
	while (l^r^1)
	{
		if (~l&1) ans=min(ans,bi[l+1]);
		if ( r&1) ans=min(ans,bi[r-1]);
		l>>=1;r>>=1;
	}
	return ans;
}
void segedit(int pos,int val)
{
	int l=(pos+M)>>1;
	bi[pos+M]=val;
	while (l>=1)
	{
		bi[l]=min(bi[l<<1],bi[l<<1|1]);
		l>>=1;
	}
}
int findpos(int beg)
{
	int l=beg,r=n,mid,tar=n-sa[beg-1],tmp,tval;
	tval=bi[beg+M];
	segedit(beg,tar);
	while (l<r-1)
	{
		mid=(l+r)>>1;
		tmp=segmin(beg,mid);
//		printf("%d %d %d %d %d %d\n",beg+1,l,r,mid,tmp,tar);
		if (tmp>=tar)
			l=mid;
		else
			r=mid-1;
	}
	while (segmin(beg,l+1)>=tar) l++;
	segedit(beg,tval);
	return l;
}
int main()
{
	scanf("%s",str);
	calc();
	for (int i=0;i<n;i++)
	{
		sa[i]=sa[i+1],hi[i]=hi[i+1];
		rk[i]--;
		bi[i+M+1]=hi[i];
//		printf("%d %d %d\n",sa[i],hi[i],rk[i]);
	}
	for (int i=M;i>0;i--)
		bi[i]=min(bi[i<<1],bi[i<<1|1]);
//	unsigned long long k=1,l=1,p=1,nowhash=0,nowhash2=0,nowhash3=0;
//	for (int i=n-1,j=0;i>=0;i--,j++,k*=27,l*=37,p*=29)
//		hash[i]=hash[i+1]+(str[i]-'A'+1)*k,
//		hash2[i]=hash2[i+1]+(str[i]-'A'+1)*l,
//		hash3[i]=(hash3[i+1]+(str[i]-'A'+1)*p);
	int tmp,tval;
	for (int i=0;i<n;i++)
	{
//		nowhash=nowhash*27+str[i]-'A'+1;
//		nowhash2=nowhash2*37+str[i]-'A'+1;
//		nowhash3=(nowhash3*29+str[i]-'A'+1);
		tval=bi[rk[n-i-1]+1+M];
		segedit(rk[n-i-1]+1,n-sa[rk[n-i-1]]);
//		printf("%d %d %d\n",i,rk[n-i-1],rk[0]);
//		cerr<<i<<endl;
		if (rk[n-i-1]<=rk[0] && segmin(rk[n-i-1]+1,rk[0]+1)==n-sa[rk[n-i-1]])
		{
//			printf("%d %d %d %d\n",i,rk[n-i-1],rk[0],segmin(rk[n-i-1]+1,rk[0]+1));
//			cerr<<"~"<<endl;
			tmp=findpos(rk[n-i-1]+1);
//			cerr<<"!"<<endl;
			ANS.push_back(make_pair(i+1,tmp-rk[n-i-1]));
		}
		segedit(rk[n-i-1]+1,tval);
	}
//	ANS.push_back(make_pair(n,1));
	printf("%d\n",ANS.size());
	for (int i=0;i<ANS.size();i++)
		printf("%d %d\n",ANS[i].first,ANS[i].second);
	return 0;
}
