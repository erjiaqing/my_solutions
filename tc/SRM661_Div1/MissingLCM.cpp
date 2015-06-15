#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
class MissingLCM {
    public:
        const int maxn = 1000000+5;
        int getMin(int);
};
int MissingLCM::getMin(int N)
{
    bool prime[maxn];
    int ans=N+1;
    memset(prime,-1,sizeof(prime));
    for (int i=2;i<=N;i++)
    {
        if (prime[i])
        {
            long long p=i;
            for (int j=i+i;j<=N;j+=i) prime[j]=0;
            while (p*i <= N) p*=i;
            ans=max((long long)ans,p*(N/p+1));
        }
    }
    return ans;
}
int main()
{
    int n;
    MissingLCM Work;
    cin>>n;
    cout<<Work.getMin(n)<<endl;
    return 0;
}

