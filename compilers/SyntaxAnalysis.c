/*************************************************************************
    * File Name: SyntaxAnalysis.c
    * Copyright (C) 2013 waikeung. All rights reserved.
    * Author: waikeung
    * mail: waikeungshen@gmail.com
    * Description :
    * Created Time: Wed 07 May 2014 18:39:14 CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *keywords[6] = {"begin", "if", "then", "while", "do", "end"};
int syn;    /* syn 种别码 */
int indexs;  /* indexs 索引*/

int isError;

//char *code = {"begin a:=9; x:=2*3; b:=a+x end #"};
//char *code = {"begin a:=9 end #"};
char code[1000];

int isKeywords(char *word);
int isLetter(char ch);   /* 判断是否为letter */
int isDigit(char ch);    /* 判断是否为digit */

void scaner();      //读下一个单词符号
void lrparser();    //LR分析器
void expression();  //表达式分析
void term();        //项分析
void statement();   //语句分析
void factor();      //因子分析
void statementStirng();//语句串分析

int main()
{
    isError = 0;
    indexs = 0;
    //输入
    fgets(code, 1000, stdin);

    scaner();
    lrparser();
    return 0;
}

void lrparser()     // LR分析器
{
    if (syn == 1)  //begin
    {
        scaner();
        statementStirng();
        if (syn == 6)   //end
        {
            scaner();
            if ((syn == 0) && (isError == 0))
                printf("success!\n");
            else
            {
                if (isError ==0)
                    printf("缺少#\n");
            }
        }
        else
        {
            if (!isError)
                printf("缺少end!\n");
            isError = 1;
        }
    }
    else 
    {
        printf("没有begin!\n");
        isError = 1;
    }

}

void statementStirng()  //语句串分析
{
    statement();
    while (syn == 26)   //;
    {
        scaner();
        if (syn != 6)   //end
            statement();
    }
}

void statement()        //语句分析
{
    if (syn == 10)  //标志符
    {
        scaner();
        if (syn == 18) //:=
        {
            scaner();
            expression();
        }
        else
        {
            printf(":= 错误!\n");
            isError = 1;
        }
    }
    else
    {
        if (syn == 6)
            printf("缺少语句串!\n");
        else
            printf("标志符错误！\n");
        isError = 1;
    }
}

void expression()   //表达式分析
{
    term();
    while ((syn == 13) || (syn == 14)) //+ -
    {
        scaner();
        term();
    }
}

void term()     //项分析
{
    factor();
    while((syn == 15) || (syn == 16))   //* /
    {
        scaner();
        factor();
    }
}

void factor()   //因子分析
{
    if ((syn == 10) || (syn == 11)) // ID NUM
    {
        scaner();
    }
    else if (syn ==27) // (
    {
        scaner();
        expression();
        if (syn == 28) // )
        {
            scaner();
        }
        else
        {
            printf("括号错误!\n");
            isError = 1;
        }
    }
    else
    {
        printf("表达式 ERROR!\n");
        isError = 1;
    }
}

/* 词法分析函数 */
void scaner()
{
    char ch;
    char word[100];
    int i, num;

    for (i = 0; i < 100; i++)
        word[100] = '\0';

    ch = code[indexs++];

    while (ch == ' ')
        ch = code[indexs++];
        
    if (isLetter(ch))
    {
        i = 0;
        word[i++] = ch;
        ch = code[indexs++];
        while(isLetter(ch) || isDigit(ch))
        {
            word[i++] = ch;
            ch = code[indexs++];
        }
        word[i] = '\0';
        indexs--;
        if (isKeywords(word) == 0)
        {
            syn = 10;
            //printf("< %d,%s >\n", syn, word);
        }
    }
    else if (isDigit(ch))
    {
        num =  ch - '0';
        ch = code[indexs++];
        while (isDigit(ch))
        {
            num = num*10 + ch - '0';
            ch = code[indexs++];
        }
        if (isLetter(ch))   /*error*/
        {
            printf("ERROR! < -1,%d%c >\n", num, ch);
            isError = 1;
            ch = code[indexs++];
            while (isLetter(ch))
            {
                //printf("%c", ch);
                ch = code[indexs++];
            }
            //printf(" >\n");

        }
        else
        {
            syn = 11;
            //printf("< %d,%d >\n", syn, num);
        }
        indexs--;
    }
    else
    {
        switch(ch)
        {
            case ':':
                ch = code[indexs++];
                if (ch == '=')
                {
                    syn = 18;   /* := 种别符*/
                    if (code[indexs] == '=' || code[indexs] == '<' || code[indexs] == '>')
                    {
                        printf("< -1,:=%c >\n", code[indexs]);
                        isError = 1;
                        syn = -1;   //error
                        indexs++;
                    }
                    //else
                        //printf("< %d,:= >\n", syn);
                }
                else
                {
                    indexs--;
                    syn = 17;   /* : 种别符 */
                    //printf("< %d,: >\n", syn);
                }
                break;
            case '<':
                ch = code[indexs++];
                if (ch == '>')
                {
                    syn = 21;   /* <> 种别符 */
                    //printf("< %d,= <>\n", syn);
                }
                else if (ch == '=')
                {
                    syn = 22;   /* <= 种别符 */
                    //printf("< %d,<= >\n", syn);
                }
                else
                {
                    indexs--;
                    syn = 20;   /* < 种别符 */
                    //printf("< %d,< >\n", syn);
                }
                break;
            case '>':
                ch = code[indexs++];
                if (ch == '=')
                {
                    syn = 24;   /* >= 种别符 */
                    //printf("< %d,>= >\n", syn);
                }
                else
                {
                    indexs--;
                    syn = 23;   /* > 种别符 */
                    //printf("< %d,> >\n", syn);
                }
                break;
            case '+': syn = 13; /*printf("< %d,+ >\n", syn);*/ break;
            case '-': syn = 14; /*printf("< %d,- >\n", syn);*/ break;
            case '*': syn = 15; /*printf("< %d,* >\n", syn);*/ break;
            case '/': syn = 16; /*printf("< %d,/ >\n", syn);*/ break;
            case '=': syn = 25; /*printf("< %d,= >\n", syn);*/ break;
            case ';': syn = 26; /*printf("< %d,; >\n", syn);*/ break;
            case '(': syn = 27; /*printf("< %d,( >\n", syn);*/ break;
            case ')': syn = 28; /*printf("< %d,) >\n", syn);*/ break;
            case '#': syn =  0; /*printf("< %d,# >\n", syn);*/ break;
        }
    }
}

/* 判断是否为关键字,是返回1,否返回0 */
int isKeywords(char *word)
{
    int i;
    for (i = 0; i < 6; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
        {
            syn = i+1;  /* 关键字种别码 */
            //printf("< %d,%s >\n", syn, keywords[i]);
            return 1;
        }
    }
    return 0;
}

int isLetter(char ch)   /* 判断是否为letter */
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'z'))
        return 1;
    return 0;
}

int isDigit(char ch)    /* 判断是否为digit */
{
    if (ch >= '0' && ch <= '9')
        return 1;
    return 0;
}
