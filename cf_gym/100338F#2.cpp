#include <bits/stdc++.h>
using namespace std;
const int maxwords = 1000 * 2000 * 2 + 5;
const int mod = 1e15 + 7;
double ps[maxwords] , pg[maxwords];
int cspam , cgood , cto , t;
map<unsigned long long , int> wdid;
int wcnt;
string buf;
void process_setense(double arr[])
{
	unsigned long long wd = 0;
	int len = 0;
	while (len == 0)
	{
		getline(cin , buf);
		len = buf.size();
	}
	buf = buf + "!!!";
	len = buf.size();
//	cerr << len << endl;
	set<int> word;
	for (int i = 0 ; i < len ; i++)
	{
		if ('a' <= buf[i] && buf[i] <= 'z')
			wd = (wd * 29 + buf[i] - 'a' + 1) % mod;
		else if ('A' <= buf[i] && buf[i] <= 'Z')
			wd = (wd * 29 + buf[i] - 'A' + 1) % mod;
		else
		{
			if (wd == 0)
				continue;
			int wid = wdid[wd];
			if (wid == 0)
				wdid[wd] = wid = (++wcnt);
			word.insert(wid);
			wd = 0;
		}
	}
	for (set<int>::iterator it = word.begin() ; it != word.end() ; it++)
		arr[*it] = arr[*it] + 1;
}
bool process_setense()
{
	unsigned long long wd = 0;
	int badcnt = 0;
	int totcnt = 0;
	int len = 0;
	while (len == 0)
	{
		getline(cin , buf);
		len = buf.size();
	}
	buf = buf + "!!!";
	len = buf.size();
	set<int> word;
	for (int i = 0 ; i < len ; i++)
	{
		if ('a' <= buf[i] && buf[i] <= 'z')
		{
			wd = (wd * 29 + buf[i] - 'a' + 1) % mod;
//			cerr << buf[i] << endl;
		}
		else if ('A' <= buf[i] && buf[i] <= 'Z')
		{
			wd = (wd * 29 + buf[i] - 'A' + 1) % mod;
//			cerr << buf[i] << endl;
		}
		else
		{
//			cerr << "--\n";
			if (wd == 0)
				continue;
			int wid = wdid[wd];
			if (wid == 0)
				wdid[wd] = wid = (++wcnt);

#ifndef ONLINE_JUDGE
			cerr << wd << endl;
#endif
			wd = 0;
			if (*word.lower_bound(wid) != wid)
				totcnt++;
			if (wid == 0)
				continue;
			word.insert(wid);
			wd = 0;
		}
	}
	for (set<int>::iterator it = word.begin() ; it != word.end() ; it++)
	{
//		totcnt++;
		if (ps[*it] + pg[*it] > 0.1 && ps[*it] > pg[*it] - 0.1)
			badcnt++;
	}
	if (totcnt == 0)
		return false;
#ifndef ONLINE_JUDGE
	printf("%d / %d\n" , badcnt , totcnt);
#endif
	return ((badcnt * 100 / totcnt) >= t);
}
int main()
{
#ifdef ONLINE_JUDGE
	freopen("spam.in" , "r" ,stdin);
	freopen("spam.out" , "w" , stdout);
#endif
	ios::sync_with_stdio(0);
	getline(cin , buf);
	sscanf(buf.c_str() , "%d%d%d%d" , &cspam , &cgood , &cto , &t);
	for (int i = 0 ; i < cspam ; i++)
		process_setense(ps);
	for (int i = 0 ; i < cgood ; i++)
		process_setense(pg);
	for (int i = 0 ; i < cto ; i++)
		printf("%s\n" , process_setense() ? "spam" : "good");
	return 0;
}
