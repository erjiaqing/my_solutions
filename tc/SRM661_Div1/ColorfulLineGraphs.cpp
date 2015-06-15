#include <bits/stdc++.h>
using namespace std;
class ColorfulLineGraphs{
    public:
        long long N,K,M;
        long long calc(long long x)
        {
            long long ret=1;
            for (int i=0;i<x;i++)
                (ret*=(K+i*(K-1))%M)%=M;
            return ret;
        }
        long long pow(long long a,long long b)
        {
            long long ret=1,tmp=a;
            while (b)
            {
                if (b&1) (ret*=tmp)%=M;
                (tmp*=tmp)%=M;
                b>>=1;
            }
            return ret;
        }
        int countWays(long long _n,long long _k,long long _m)
        {
            N=_n;K=_k;M=_m;
            return (int)((pow(calc(M),(N/M))*calc(N%M))%M);
        }
};
int main()
{
    ColorfulLineGraphs Work;
    long long n,k,m;
    cin>>n>>k>>m;
    cout<<Work.countWays(n,k,m)<<endl;
    return 0;
}

