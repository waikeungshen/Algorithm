/*************************************************************************
    * File Name: binarySearch.c
    * Copyright (C) 2013 waikeung. All rights reserved.
    * Author: waikeung
    * mail: waikeungshen@gmail.com
    * Description :
    * Created Time: Sun 02 Mar 2014 22:06:16 CST
 ************************************************************************/

#include <stdio.h>

int BinarySearch(int array[], int low, int high, int key)
{
    int mid = (high + low) / 2;
    if (low > high)
        return -1;
    else
    {
        if (array[mid] == key)
            return mid;
        else if (array[mid] > key)
            return BinarySearch(array, low, mid-1, key);
        else
            return BinarySearch(array, mid+1, high, key);
    }
}

int main()
{
    int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int key = 6;
    printf("%d\n", BinarySearch(array, 0, 9, key));
    return 0;
}
