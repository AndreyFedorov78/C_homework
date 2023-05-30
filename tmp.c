//
// Created by Andrei Fedorov on 02.09.2022.
//
#include <stdio.h>

int main(int argc, char **argv)
{ int N, max=0, b, a=1;
    scanf("%d",&N);

    scanf("%d",&max);
    for (int i=2; i<=N; i++) {
        scanf("%d",&b);
        if(max<b) {max=b; a=1;}
        else if (max==b) a++;
    }
    if (N==0) a=0;
    printf("%d\n",a);
    return 0;
}