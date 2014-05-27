#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
struct Task{
	int id,arrive,process,flag;
	Task(){}
	Task(int a,int b,int c,int d):
		id(a),arrive(b),process(c),flag(d){}
}T;
bool operator < (Task a,Task b)
{
	return (a.flag==b.flag)?(a.arrive>b.arrive):(a.flag<b.flag);
}
priority_queue<Task> H;
int nowtime=0;
int main()
{
	int pid,pstart,ppro,pf;
	while (~scanf("%d%d%d%d",&pid,&pstart,&ppro,&pf))
	{
		int delta;
		while (nowtime<pstart&&(!H.empty()))
		{
			T=H.top();H.pop();
			nowtime=max(nowtime,T.arrive);
			delta=min(T.process,pstart-nowtime);
			T.process-=delta;nowtime+=delta;
			if (T.process)
				H.push(T);
			else
				printf("%d %d\n",T.id,nowtime);
		}
		H.push(Task(pid,pstart,ppro,pf));
	}
	while (!H.empty())
	{
		T=H.top();
		H.pop();
		printf("%d %d\n",T.id,nowtime+=T.process);
	}
	return 0;
}
