/*************************************************************************
    * File Name: 2.3-7.c
    * Copyright (C) 2013 waikeung. All rights reserved.
    * Author: waikeung
    * mail: waikeungshen@gmail.com
    * Description :
    * Created Time: Sun 02 Mar 2014 22:44:46 CST
 ************************************************************************/

#include <stdio.h>

int function(int array[], int n,  int x)
{
    int i, j;
    int p, q;
    
    for (i = 0; i < n; i++) {
        p = array[i];
        for (j = i+1; j < n; j++) {
            q = array[j];
            if (p+q == x)
                return 1;
         }
    }
    return -1;
}
int main()
{
    int array[] = {1,3,5,7,9};
    int n = 5;
    int x = 10;
    printf("%d\n", function(array, n ,x));
    return 0;
}
