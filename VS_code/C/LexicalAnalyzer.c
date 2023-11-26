//lexical analyzer for the C-- compiler
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Global Variables
// These variables are shared between the main driver
// and the lexical analyzer. DO NOT CHANGE THIS PART.
enum yytokentype
{
    num_INT = 258,
    num_FLOAT = 259,
    Y_ID = 260,
    Y_INT = 261,
    Y_VOID = 262,
    Y_CONST = 263,
    Y_IF = 264,
    Y_ELSE = 265,
    Y_WHILE = 266,
    Y_BREAK = 267,
    Y_CONTINUE = 268,
    Y_RETURN = 269,

    Y_ADD = 270,
    Y_SUB = 271,
    Y_MUL = 272,
    Y_DIV = 273,
    Y_MODULO = 274,
    Y_LESS = 275,
    Y_LESSEQ = 276,
    Y_GREAT = 277,
    Y_GREATEQ = 278,
    Y_NOTEQ = 279,
    Y_EQ = 280,
    Y_NOT = 281,
    Y_AND = 282,
    Y_OR = 283,
    Y_ASSIGN = 284,
    Y_LPAR = 285,
    Y_RPAR = 286,
    Y_LBRACKET = 287,
    Y_RBRACKET = 288,
    Y_LSQUARE = 289,
    Y_RSQUARE = 290,
    Y_COMMA = 291,
    Y_SEMICOLON = 292,
    Y_FLOAT = 293
};

char token[1000]; // token string
int tokenType; // token type
int length; // token length
int tokenNum = 0; // token number
int floatFlag = 0;
FILE *in_fp, *fopen();

char* keywords[] = {"int","void","const","if", "else","while" "break","continue","return","float"};
int keynum[] =     {Y_INT,Y_VOID,Y_CONST,Y_IF,Y_ELSE,Y_WHILE,Y_BREAK,Y_CONTINUE,Y_RETURN,Y_FLOAT};

char opera[] = {'+', '-', '*', '/', '%','<', '<=', '>', '>=', '!=', 
                   '==', '!', '&', '|', '='};
int opnum[] = {Y_ADD, Y_SUB, Y_MUL, Y_DIV, Y_MODULO, Y_LESS, Y_LESSEQ, Y_GREAT, Y_GREATEQ, Y_NOTEQ, 
                Y_EQ, Y_NOT, Y_AND, Y_OR, Y_ASSIGN};

char boundarySymble[] = {'(', ')', '[', ']', '{', '}', ',', ';'};
int boundarySymblenum[] = {Y_LPAR, Y_RPAR, Y_LBRACKET, Y_RBRACKET, Y_LSQUARE, Y_RSQUARE, Y_COMMA, Y_SEMICOLON};

bool isNum(char c){
    if (c >= '0' && c <= '9')
    {
        return true;
    }
    return false;
}
bool isLetter(char c){
    if (c >= 'a' && c <= 'z') 
    {
        return true;
    }
    return false;
}
char* isFloat(char c){
    char *num = (char *)malloc(sizeof(char));
    int i = 0;
    while (isNum(token[tokenNum]))
    {
        num[i] = token[tokenNum];
        i++;
        tokenNum++;
        c = token[tokenNum];
    }
    if (c == '.')
    {
        floatFlag = 1;
        num[i] = token[tokenNum];
        i++;
        tokenNum++;
        c = token[tokenNum];
        while (isNum(token[tokenNum]))
        {
            num[i] = token[tokenNum];
            i++;
            c = token[tokenNum++];
        }
        num[i] = '\0';
        return num;
    }
    else
    {
        num[i] = '\0';
        return num;
    }
}


//return the type of charactor
int typeword(char c){
    if(c>='a' && c<='z')   //alpha 
        return 1;
    if(c>='0' && c<='9')   //number 
        return 2;
    if(c=='>'||c=='='||c=='<'||c=='!'||c==','||c==';'||c=='('||c==')'||c=='{'||c=='}'
		||c=='+'||c=='-'||c=='*'||c=='/')   //judge symbol 
        return 3; 
}   

int isKeyWord(char *c){
    for (int i = 0; i < 10; i++)
    {
        if (strcmp(c, keywords[i]) == 0)
        {
            return keynum[i];
        }
		else return 0;
    }
    
}
int isOperator(char c){
    for (int i = 0; i < 15; i++)
    {
        if (c == opera[i])
        {
            return opnum[i];
        }
    }
    return 0;
}
int isBoundarySymbol(char c){
    for (int i = 0; i < 8; i++)
    {
        if (c == boundarySymble[i])
        {
            return i;
        }
    }
    return 0;
}
char* keyWords(char c){
    char *key = (char *)malloc(sizeof(char));
    int i = 0;
    while (isLetter(c))
    {
        key[i] = c;
        i++;
        tokenNum++;
        c = token[tokenNum];
    }
    key[i] = '\0';
    tokenNum--; 
    return key;
}
char* identifier(char c){
    char *id = (char *)malloc(sizeof(char));
    int i = 0;
    while (isNum(c) || isLetter(c))
    {
        id[i] = c;
        i++;
        tokenNum++;
        c = token[tokenNum];
    }
    id[i] = '\0';
    return id;
}
char* number(char c){
    char *num = (char *)malloc(sizeof(char));
    int i = 0;
    while (isNum(c))
    {
        num[i] = c;
        i++;
        tokenNum++;
        c = token[tokenNum];
    }
    num[i] = '\0';
    return num;
}
char 

void print(char *c,int type)    //print the word
{
    printf("<%s,%d>\n",c,type);
}
void printChar(char c,int type)    //print the word
{
    printf("<%c,%d>\n",c,type);
}

void takeword(char c){
    int type = typeword(c);
    switch (type)
    {
    case 1:
    {
    	char* p;
        p = keyWords(c);
        if(isKeyWord(p))
            print(p,isKeyWord(p));
        else
            print(p,Y_ID);
    }
        break;
        
    case 2:
    {
        isFloat(c);
        if (floatFlag)
        {
            print(isFloat(c),Y_FLOAT);
        }
        else
        print(number(c),Y_INT);
    }
        break;
    
    case 3:
    {
        if(isOperator(c)){
           print(c,isOperator(c)); 
        }
        else if(isBoundarySymbol(c)){
            int temp = isBoundarySymbol(c);
            print(boundarySymble[],boundarySymblenum[isBoundarySymbol(c)]);
        }
    }
        break;
    default:
        break;
    }
}

int main(){
    char c;
    length = 0;
    in_fp = fopen("E:\\Documents\\Project\\VisualStudio\\C\\00_main.sy", "r");
    if (in_fp == NULL)
    {
        printf("Can't open file");
        exit(0);
    }
    while ((c = fgetc(in_fp)) != EOF)
    {
        token[length] = c;
        length++;
    }
    length++;
    
    for( tokenNum = 0; tokenNum < length; tokenNum++)
    {
        takeword(token[tokenNum]);
    }
    
    fclose(in_fp);
    return 0;
}