#include <stdlib.h>
#include <stdio.h>
#include "AmosType.hpp"
#include "RPNCalculate.hpp"

#define FILEPATH "input.txt"

int main(void)
{
    FILE* fp;
    char buf[BUFSIZE];
    AM_S32 result;

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

    fclose(fp);

    return 1;
}
