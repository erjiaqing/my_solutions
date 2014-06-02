#include <bits/stdc++.h>
using namespace std;
char A[105],B[105],C[105],D[105];
int L[5];
char anC[]=" ABCD";
char ans=0;
int main()
{
	scanf("%s%s%s%s",A,B,C,D);
	L[1]=strlen(A)-2;L[2]=strlen(B)-2;L[3]=strlen(C)-2;L[4]=strlen(D)-2;
	for (int i=1;i<=4;i++)
	{
	    bool flag1=true,flag2=true;
	    for (int j=1;j<=4;j++)
	        if (i!=j && L[i]<2*L[j])
	            flag1=false;
	    for (int j=1;j<=4;j++)
	        if (i!=j && 2*L[i]>L[j])
	            flag2=false;
	    if (flag1 || flag2)
	    {
	        if (!ans)
	        {
	            ans=i;
	        }else
	        {
	            ans=-1;
	        }
	    }
    }
    if (ans==-1 || ans==0)
        printf("%c\n",'C');
    else
        printf("%c\n",anC[ans]);
	return 0;
}
