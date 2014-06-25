#include <bits/stdc++.h>
using namespace std;
const int maxl=1000005,cnt=205;
int n;
char str[205][maxl];
struct trie_node{
	trie_node *n[27],*fa,*fail;
	int flag;
	trie_node(trie_node *_fa):
		fa(_fa)
	{for (int i=0;i<26;i++) n[i]=NULL;fail=NULL,flag=0;}
}*Q[maxl];
struct ac{
	trie_node *root;
	ac(){root=new trie_node(NULL);}
	void insert(char *str,int len)
	{
		trie_node *p=root;
		int x;
		for (int i=0;i<len;i++)
		{
			x=str[i]-'a';
			if (p->n[x]==NULL)
				p->n[x]=new trie_node(p);
			p=p->n[x];
			p->flag++;
		}
	}
	void build()
	{
		int l=0,r=0;
		trie_node *p=root,*q,*t;
		for (int i=0;i<26;i++)
		{
			if (p->n[i]!=NULL)
			{
				Q[r++]=p->n[i];
				p->n[i]->fail=p;
			}
		}
		while (l<r)
		{
			p=Q[l++];
			for (int i=0;i<26;i++)
			{
				if (p->n[i]!=NULL)
				{
					Q[r++]=t=p->n[i];
					q=p->fail;
					while (q!=NULL && q->n[i]==NULL)
						q=q->fail;
					if (q!=NULL && q->n[i]!=NULL)
						t->fail=q->n[i];
					else
						t->fail=root;
				}
			}
		}
		for (int i=r-1;i>=0;i--)
		{
			Q[i]->fail->flag+=Q[i]->flag;
		}
	}
	int match(char *str,char endflag='\0')
	{
		trie_node *p=root;
		for (int i=0;str[i]!=endflag;i++)
		{
//			cerr<<str[i]<<endl;
			p=p->n[str[i]-'a'];
		}
		return p->flag;
	}
};
int main()
{
	ac ac;
	int n,len;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%s",str[i]);
		len=strlen(str[i]);
		ac.insert(str[i],len);
//		str[i][len]='#';
//		cerr<<len<<endl;
	}
	ac.build();
	for (int i=1;i<=n;i++)
		printf("%d\n",ac.match(str[i]));
	return 0;
}
