#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *keywords[6] = {"begin", "if", "then", "while", "do", "end"};
int syn;    /* syn 种别码 */
int indexs;  /* indexs 索引*/

int isKeywords(char *word);
int isLetter(char ch);   /* 判断是否为letter */
int isDigit(char ch);    /* 判断是否为digit */

/* 词法分析函数 */
void analyzer(char *code)
{
    char ch;
    char word[100];
    int i, num;
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
            printf("< %d,%s >\n", syn, word);
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
            printf("ERROR! < -1,%d%c", num, ch);
            ch = code[indexs++];
            while (isLetter(ch))
            {
                printf("%c", ch);
                ch = code[indexs++];
            }
            printf(" >\n");

        }
        else
        {
            syn = 11;
            printf("< %d,%d >\n", syn, num);
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
                        indexs++;
                    }
                    else
                        printf("< %d,:= >\n", syn);
                }
                else
                {
                    indexs--;
                    syn = 17;   /* : 种别符 */
                    printf("< %d,: >\n", syn);
                }
                break;
            case '<':
                ch = code[indexs++];
                if (ch == '>')
                {
                    syn = 21;   /* <> 种别符 */
                    printf("< %d,= <>\n", syn);
                }
                else if (ch == '=')
                {
                    syn = 22;   /* <= 种别符 */
                    printf("< %d,<= >\n", syn);
                }
                else
                {
                    indexs--;
                    syn = 20;   /* < 种别符 */
                    printf("< %d,< >\n", syn);
                }
                break;
            case '>':
                ch = code[indexs++];
                if (ch == '=')
                {
                    syn = 24;   /* >= 种别符 */
                    printf("< %d,>= >\n", syn);
                }
                else
                {
                    indexs--;
                    syn = 23;   /* > 种别符 */
                    printf("< %d,> >\n", syn);
                }
                break;
            case '+': syn = 13; printf("< %d,+ >\n", syn); break;
            case '-': syn = 14; printf("< %d,- >\n", syn); break;
            case '*': syn = 15; printf("< %d,* >\n", syn); break;
            case '/': syn = 16; printf("< %d,/ >\n", syn); break;
            case '=': syn = 25; printf("< %d,= >\n", syn); break;
            case ';': syn = 26; printf("< %d,; >\n", syn); break;
            case '(': syn = 27; printf("< %d,( >\n", syn); break;
            case ')': syn = 28; printf("< %d,) >\n", syn); break;
            case '#': syn =  0; printf("< %d,# >\n", syn); break;
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
            printf("< %d,%s >\n", syn, keywords[i]);
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

void scanner(char *code)
{
    char string[100];
    int i, j;
    syn = 0;
    i = 0;

    while (code[i] != '\0')
    {
        j = 0;
        while (code[i] != ' '&& code[i] != '\0')
        {
            string[j++] = code[i++];
        }
        i++;
        indexs = 0;
        string[j] = '\0';
        while (string[indexs] != '\0')
        {
            analyzer(string);     /* 词法分析 */
        }
    }
}

int main()
{
    char code[80]={0};
    gets(code);
    scanner(code);
    return 0;
}

