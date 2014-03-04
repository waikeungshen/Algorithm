/*************************************************************************
    * File Name: selectsort.c
    * Copyright (C) 2013 waikeung. All rights reserved.
    * Author: waikeung
    * mail: waikeungshen@gmail.com
    * Description :
    * Created Time: Sun 02 Mar 2014 21:36:54 CST
 ************************************************************************/

#include <stdio.h>

void swap(int *pa, int *pb)
{
    int tmp;
    tmp = *pa;
    *pa = *pb;
    *pb = tmp;
}

void SelectionSort(int a[], int n)
{
    int i, j;
    int min_index;
    for (i = 0; i < n-1; i++) {
        min_index = i;
        for (j=i+1; j < n; j++) {
            if (a[j] < a[min_index])
                min_index = j;
        }
        swap(a+i, a+min_index);
    }
}

void main()
{
    int a[] = {9, 8, 7, 6, 5, 4};
    int n = 6;
    int i;
    SelectionSort(a, n);
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");

}
