#!/usr/bin/python
l=1**100
r=1
m=input()
n=input()
while (r**m <n):
    r=r*2
while (l**m >n):
    l=l/2
mid=0
while (l<r):
    mid=(l+r)/2
    tmp=mid**m
#    print mid
    if (tmp < n):
        l=mid+1
    elif (tmp > n):
        r=mid-1
    else:
        break
while (r**m > n):
    r=r-1
print(r)
