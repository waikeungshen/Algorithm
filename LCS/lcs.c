/*************************************************************************
    * File Name: lcs.c
    * Copyright (C) 2013 waikeung. All rights reserved.
    * Author: waikeung
    * mail: waikeungshen@gmail.com
    * Description :
    * Created Time: Mon 05 May 2014 23:35:37 CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#define MAXLEN 100

void LCSLength(char *x, char *y, int c[][MAXLEN], int b[][MAXLEN])
{
    int i, j;
    int m, n;
    m = strlen(x);
    n = strlen(y);

    for (i = 0; i <= m; i++)
        c[i][0] = 0;
    for (j = 0; j <= n; j++)
        c[0][j] = 0;
    
    /*              0                            i=0 or j=0
     *  c[i, j] =   c[i-1, j-1]+1                i,j > 0 and xi = yi
     *              max(c[i, j-1], c[i-1, j])    i,j > 0 and xi != yi
     */
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            if (x[i-1] == y[j-1]) {
                c[i][j] = c[i-1][j-1] + 1;
                b[i][j] = 0;
            } else if (c[i-1][j] >= c[i][j-1]) {
                c[i][j] = c[i-1][j];
                b[i][j] = 1;
            } else {
                c[i][j] = c[i][j-1];
                b[i][j] = -1;
            }
        }
    }
}

void PrintLCS(int b[][MAXLEN], char *x, int i, int j)
{
    if (i == 0 || j == 0)
        return;
    if (b[i][j] == 0) {
        PrintLCS(b, x, i-1, j-1);
        printf("%c", x[i-1]);
    }
    else if (b[i][j] == 1)
        PrintLCS(b, x, i-1, j);
    else
        PrintLCS(b, x, i, j-1);
}

int main()
{
    char x[MAXLEN] = {"ABCBDAB"};
    char y[MAXLEN] = {"BDCABA"};

    int b[MAXLEN][MAXLEN];
    int c[MAXLEN][MAXLEN];

    LCSLength(x, y, c, b);

    int m = strlen(x);
    int n = strlen(y);

    printf("x = %s\ny = %s\n", x, y);
    PrintLCS(b, x, m, n);
    printf("\n");
    return 0;
}
