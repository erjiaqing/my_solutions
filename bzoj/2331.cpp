#include <bits/stdc++.h>
using namespace std;
//Hash
const int Hash=100007,maxn=2000005,mod=20110520;
struct node
{
	int st[maxn],cnt[maxn],sz,h[Hash],n[maxn];
	void e()
	{
		sz=0;
		memset(h,-1,sizeof(h));
	}
	void ins(int s,int x)
	{
		int t=s%Hash;
		for (int i=h[t];~i;i=n[i])
		{
			if (st[i]==s)
			{
				cnt[i]=(cnt[i]+x)%mod;
				return;
			}
		}
		st[sz]=s;
		cnt[sz]=x;
		n[sz]=h[t];
		h[t]=sz++;
	}
}f[2];
int pre,cur;
int n,m;
char Map[105][105],MMap[105][105];

#define get_bit(st,k) (((st)>>((k)+(k)))&3)
#define set_0(st,k)   ((st)&(~(3<<((k)+(k)))))
#define set_1(st,k)   (((st)&(~(3<<((k)+(k)))))|(1<<((k)+(k))))
#define set_3(st,k)   ((st)|(3<<((k)+(k))))
#define add(s,x)      (f[cur].ins((s),(x)))

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%s",&Map[i][1]);
	if (m>n)
	{
		for (int j=1;j<=m;j++)
			for (int i=1;i<=n;i++)
				MMap[j][i]=Map[i][j];
		swap(m,n);
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
				Map[i][j]=MMap[i][j]; 
	}
	pre=0;cur=1;
	f[pre].e();f[pre].ins(0,1);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			f[cur].e();
			int k,x,y,s,cnt;
			for (int k=0;k<f[pre].sz;k++)
			{
				s=f[pre].st[k];
				cnt=f[pre].cnt[k];
				if (j==1)
				{
					if (get_bit(s,m)) continue;
					s<<=2;
				}
				x=get_bit(s,j-1);
				y=get_bit(s,j);
				s=set_0(s,j-1);
				s=set_0(s,j);
				if (Map[i][j]=='*')
				{
					if (x||y) continue;
					add(s,cnt);
					continue;
				}
				if (!x && !y)
				{
					add(set_1(s,j),cnt);
					add(set_1(s,j-1),cnt);
					s=set_3(s,j-1);
					s=set_3(s,j);
					add(s,cnt);
				}else if (x&&y)
				{
					if (x==1 && y==1)
						add(s,cnt);
				}else if (x||y)
				{
					if (x==3) add(set_3(s,j),cnt),add(s,cnt);
					else if (x==1) add(set_1(s,j),cnt),add(set_3(s,j-1),cnt);
					if (y==3) add(set_3(s,j-1),cnt),add(s,cnt);
					else if (y==1) add(set_1(s,j-1),cnt),add(set_3(s,j),cnt);
				}
			}
			swap(pre,cur);
		}
	int ans=0;
	for (int i=0;i<f[pre].sz;i++)
		if (f[pre].st[i]==0)
			ans=f[pre].cnt[i];
	printf("%d\n",ans);
	return 0;
}
