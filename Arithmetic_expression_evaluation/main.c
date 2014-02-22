/*************************************************************************
    * File Name: main.c
    * Copyright (C) 2013 waikeung. All rights reserved.
    * Author: waikeung
    * mail: waikeungshen@gmail.com
    * Description :
    * Created Time: Sat 22 Feb 2014 15:54:47 CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include "Item.h"
#include "STACK.h"

int main(int argc, char *argv[])
{
    char *a = argv[1];      /*后缀表达式*/
    int i, N = strlen(a);   /*后缀表达式长度*/
    STACKinit(N);
    for (i = 0; i < N; i++)
    {
        if (a[i] == '+')
            STACKpush(STACKpop() + STACKpop());
        if (a[i] == '*')
            STACKpush(STACKpop() * STACKpop());
        if ((a[i] >= '0') && (a[i] <= '9'))
            STACKpush(0);
        while ((a[i] >= '0') && (a[i] <= '9'))
            STACKpush(10*STACKpop() + (a[i++] - '0'));
    }
    printf("%d\n", STACKpop());
    return 0;
}

