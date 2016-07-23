#include <bits/stdc++.h>
using namespace std;
const int maxn = 3000 + 5;
int _i[maxn], _o[maxn], n;
int op1[maxn], op2[maxn], top;
int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &_i[i]);
		_o[i] = _i[i];
	}
	sort(&_o[0], &_o[n]);
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (_i[j] == _o[i])
			{
				op1[top] = i;
				op2[top] = j;
				swap(_i[i], _i[j]);
				top++;
				break;
			}
		}
	}
	printf("%d\n", top);
	for (int i = 0; i < top; i++)
		printf("%d %d\n", op1[i], op2[i]);
	return 0;
}
