#include <bits/stdc++.h>
using namespace std;
int beg , n , qn;
int main()
{
	int q;
	while (scanf("%d" , &n) == 1)
	{
		beg = qn = 0;
	if (n <= 3)
	{
		(printf("-1\n"));
		continue;
	}
	if (n == 4)
	{
		printf("1 * 2\n5 + 3\n6 + 4\n");
		continue;
	}else if (n == 5)
	{
		printf("1 * 2\n6 * 3\n7 - 4\n8 / 5\n");
		continue;
	}
	else if (n == 6)
	{
		printf("1 + 2\n7 + 3\n8 + 4\n5 / 6\n9 / 10\n");
		continue;
	}
	else if (n == 7)
	{
		 printf("1 + 2\n8 + 3\n9 / 4\n5 / 6\n7 + 11\n12 * 10\n");
		 continue;
	}
	else if (n == 15)
	{
		printf(
				"1 / 2\n"
				"3 / 4\n"
				"5 / 6\n"
				"7 / 8\n"
				"9 / 10\n"
				"11 / 12\n"
				"13 / 14\n"
				"16 + 17\n"
				"18 + 23\n"
				"19 + 20\n"
				"25 + 21\n"
				"24 * 26\n"
				"15 + 27\n"
				"28 * 22\n");
		continue;
	}else if (n == 16)
	{
		printf(
				"1 / 2\n"
				"3 / 4\n"
				"5 / 6\n"
				"7 / 8\n"
				"9 / 10\n"
				"11 / 12\n"
				"13 / 14\n"
				"17 + 18\n"
				"19 + 20\n"
				"25 + 21\n"
				"24 * 26\n"
				"15 + 16\n"
				"28 - 27\n"
				"29 - 22\n"
				"30 - 23\n");
		continue;
	}
	beg = 1;
	qn = n;
	int tn = n;
	int lst = n - 1;
	while (tn >= 36)
	{
		if (tn % 2 == 1)
		{
			printf("%d / %d\n" , beg , beg + 1);beg += 2;  // qn + 1
			printf("%d - %d\n" , qn , qn + 1);             // qn + 2
			printf("%d / %d\n" , beg , beg + 1);beg += 2;  // qn + 3
			printf("%d / %d\n" , beg , beg + 1);beg += 2;  // qn + 4
			printf("%d + %d\n" , qn + 3 , qn + 4);         // qn + 5
			printf("%d / %d\n" , qn + 2 , qn + 5);         // qn + 6
			qn += 6;
			lst -= 6;
		}
		else 
		{
			printf("%d / %d\n" , beg , beg + 1);beg += 2; // qn + 1
			printf("%d / %d\n" , beg , beg + 1);beg += 2; // qn + 2
			printf("%d + %d\n" , qn + 1 , qn + 2);        // qn + 3
			printf("%d / %d\n" , qn , qn + 3);            // qn + 4
			qn += 4;
			lst -= 4;
		}
		tn /= 2;
	}
	while (tn < (n == 9 ? 20 : 17))
	{
		printf("%d + %d\n" , beg , qn);beg += 1;
		qn ++;
		tn += n;
		lst --;
	}
	while (tn < 24)
	{
		printf("%d / %d\n" , beg , beg + 1);beg += 2;
		printf("%d + %d\n" , qn , qn + 1);
		qn += 2;
		lst -= 2;
		tn ++;
	}
	while (tn > 24)
	{
		printf("%d / %d\n" , beg , beg + 1);beg += 2;
		printf("%d - %d\n" , qn , qn + 1);
		qn += 2;
		lst -= 2;
		tn --;
	}
	while (lst)
	if (tn == 24)
	{
		if (lst % 2 == 0)
		{
			printf("%d + %d\n" , qn , beg);beg++;
			printf("%d - %d\n" , qn + 1, beg);beg++;
			qn += 2;
			lst -= 2;
		} else
		{
			printf("%d - %d\n" , beg , beg + 1);beg+=2;
			printf("%d * %d\n" , beg , qn + 1);beg++;
			printf("%d + %d\n" , qn , qn + 2);
			qn += 3;
			lst -= 3;
		}
	}
	}
	return 0;
}
