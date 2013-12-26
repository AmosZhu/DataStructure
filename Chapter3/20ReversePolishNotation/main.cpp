#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "AmosType.hpp"
#include "RPNCalculate.hpp"

#define FILEPATH "input.txt"

int main(void)
{
    FILE* fp;
    char buf[BUFSIZE];
    AM_S32 result;
    struct rpn_t RPNExpr[BUFSIZE];
    struct rpn_t* idx;

    if((fp=fopen(FILEPATH,"rb+"))==NULL)
    {
        printf("Check your file!\n");
        return 0;
    }

    fscanf(fp,"%s",buf);

    printf("expression=%s\n",buf);
    if(RPNCalculate(buf,&result)==RETURN_SUCCESS)
        printf("result=%d\n",result);
    else
        printf("Invalid expression!\n");


    memset(buf,0,BUFSIZE);
    fscanf(fp,"%s",buf);
    if(RPNTranslate(buf,RPNExpr)!=RETURN_SUCCESS)
        printf("Invalid expression!\n");

    for(idx=RPNExpr; idx->type!=TYPE_NULL; idx++)
    {
        if(idx->type==TYPE_NUMBER)
            printf("[%d]",idx->value);
        else if(idx->type==TYPE_OP)
            printf("[%c]",idx->value&0xff);
        else
            break;
    }

    printf("\n");

    fclose(fp);

    return 1;
}
