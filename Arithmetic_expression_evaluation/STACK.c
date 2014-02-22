/*************************************************************************
    * File Name: STACK.c
    * Copyright (C) 2013 waikeung. All rights reserved.
    * Author: waikeung
    * mail: waikeungshen@gmail.com
    * Description :
    * Created Time: Sat 22 Feb 2014 16:10:37 CST
 ************************************************************************/

#include <stdlib.h>
#include "Item.h"
#include "STACK.h"

static Item *s;
static int N;
void STACKinit(int maxN)
{
    s = malloc(maxN*sizeof(Item));
    N = 0;
}
void STACKempty()
{
    return N == 0;
}
void STACKpush(Item item)
{
    s[N++] = item;
}
Item STACKpop()
{
    return s[--N];
}
