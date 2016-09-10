#include <bits/stdc++.h>
using namespace std;

int a[405], b[405];

int aw, bw;

int main()
{
	int a0, b0, a1, b1;
	cin >> a0 >> b0 >> a1 >> b1;
	for (int i = a0; i <= b0; i++)
		for (int j = a1; j <= b1; j++)
			a[i + j]++;
	cin >> a0 >> b0 >> a1 >> b1;
	for (int i = a0; i <= b0; i++)
		for (int j = a1; j <= b1; j++)
			b[i + j]++;
	for (int i = 0; i <= 400; i++)
		for (int j = 0; j < i; j++)
			aw += a[i] * b[j];
	for (int j = 0; j <= 400; j++)
		for (int i = 0; i < j; i++)
			bw += a[i] * b[j];
	if (aw > bw) puts("Gunnar");
	if (aw < bw) puts("Emma");
	if (aw == bw) puts("Tie");
	return 0;
}
