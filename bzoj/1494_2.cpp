#include<cstdio>
#include<iostream>
#include<algorithm>
#include<sstream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<climits>
#include<cmath>
#include<queue>
#include<vector>
#include<stack>
#include<set>
#include<map>
#define INF 0x3f3f3f3f
#define eps 1e-8
using namespace std;

const long long MOD = 65521;
const int MAXK=5,MAXS=60;
int status[MAXS],hash[1<<(3*MAXK)];
int p[MAXK+1],cot[MAXK];
int val[6]= {1,1,1,3,16,125};
long long n;
int k;
int tot;

struct Matrix
{
    int h,w;
    long long mx[MAXS][MAXS];

    Matrix()
    {
        h=0;
        w=0;
        memset(mx,0,sizeof(mx));
    }
    Matrix operator* (const Matrix& b) const
    {
        Matrix tmp;
        memset(tmp.mx,0,sizeof(tmp.mx));
        tmp.h=h;
        tmp.w=b.w;
        for (int i=0; i<h; i++)
        {
            for (int j=0; j<b.w; j++)
            {
                for (int k=0; k<w; k++)
                {
                    tmp.mx[i][j]=(tmp.mx[i][j]+(mx[i][k]*b.mx[k][j])%MOD)%MOD;
                }
            }
        }
        return tmp;
    }

    void initE()
    {
        memset(mx,0, sizeof(mx));
        for (int i=0 ; i<w ; i++)
        {
            mx[i][i]=1LL;
        }
    }

    Matrix mpow(long long  k)
    {
        Matrix c,b;
        c=(*this);
        memset(b.mx,0,sizeof(b.mx));
        b.w=w;
        b.h=h;
        b.initE();
        while(k)
        {
            if(k&1LL)
            {
                b=b*c;
            }
            c=c*c;
            k>>=1LL;
        }
        return b;
    }
};
Matrix g,f;

void dfs(int mask, int dep)
{
    if(dep==k)
    {
        g.mx[0][tot]=1;
        memset(cot,0,sizeof(cot));
        for(int i=0; i<k; i++)
        {
            cot[mask>>(i*3)&7]++;
        }
        for(int i=0; i<k; i++)
        {
            g.mx[0][tot]*=val[cot[i]];
        }
        status[tot]=mask;
        hash[mask]=tot++;
        return;
    }
    int tmp=-1;
    for(int i=0; i<dep; i++)
    {
        tmp=max(tmp,mask>>(i*3)&7);
    }
    for(int i=0; i<=tmp+1&&i<k; i++)
    {
        dfs(mask<<3|i,dep+1);
    }
}

int findp(int x)
{
    return p[x]==-1?x:p[x]=findp(p[x]);
}

int justify()
{
    bool vis[MAXK];
    memset(vis,0,sizeof(vis));
    int tot=0;
    int mask=0;
    for(int i=k-1; i>=0; i--)
    {
        if(!vis[i])
        {
            vis[i]=true;
            mask|=tot<<(i*3);
            for(int j=i-1; j>=0; j--)
            {
                if(findp(i+1)==findp(j+1))
                {
                    vis[j]=true;
                    mask|=tot<<(j*3);
                }
            }
            tot++;
        }
    }
    return hash[mask];
}

void cal(int s, int mask)
{
    memset(p,-1,sizeof(p));
    for(int i=0; i<k; i++)
    {
        for(int j=i+1; j<k; j++)
        {
            if((status[s]>>(i*3)&7)==(status[s]>>(j*3)&7))
            {
                int px=findp(i);
                int py=findp(j);
                if(px!=py)
                {
                    p[px]=py;
                }
            }
        }
    }
    for(int i=0; i<k; i++)
    {
        if((mask>>i)&1)
        {
            int px=findp(i);
            int py=findp(k);
            if(px==py)
            {
                return;
            }
            p[px]=py;
        }
    }
    bool flg=false;
    for(int i=1; i<=k; i++)
    {
        if(findp(i)==findp(0))
        {
            flg=true;
            break;
        }
    }
    if(!flg)
    {
        return;
    }
    f.mx[s][justify()]++;
}

int main()
{
    while(scanf("%d%lld",&k,&n)==2)
    {
        memset(f.mx,0,sizeof(f.mx));
        memset(g.mx,0,sizeof(g.mx));
        tot=0;
        dfs(0,0);
        g.h=1;
        g.w=f.w=f.h=tot;
        for(int i=0; i<tot; i++)
        {
            for(int mask=0; mask<(1<<k); mask++)
            {
                cal(i,mask);
            }
        }
        g=g*f.mpow(n-k);
        printf("%lld\n",g.mx[0][0]);
    }
    return 0;
}
